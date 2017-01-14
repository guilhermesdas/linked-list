#include "lista.h"

/////////////////////////////////////////////////

void inicializa(Lista* lista){

	lista->prim = NULL;
	lista->ult = NULL;

}

int listaVazia(Lista lista){

	return lista.ult == NULL && lista.prim == NULL;

}

void inserirNumero(Lista* lista, int num){

	Bloco* novo = (Bloco*)malloc(sizeof(Bloco));
	novo->num = num;
	novo->freq = 1;
	novo->prox = NULL;
	
	inserirBloco(lista,novo);

}

void inserirBloco(Lista* lista, Bloco* novo){

	// Caso a lista esteja vazia, novo será
	// o único elemento na lista
	if ( listaVazia(*lista) ) {
		lista->prim = novo;
		lista->ult = novo;
		return;
	}

	lista->ult->prox = novo; // Encadeia o ultimo elemento ao novo
	lista->ult = novo;

}

void gerarValores(Lista* lista, int tam){

	srand( (unsigned)time(NULL) );
	int ind = 0;

	while ( ind < tam ) {

		int num = rand() % RANDMAX;
		inserirNumero(lista,num);

		ind++;
	}

}

void mostrarLista(Lista lista){

	if ( listaVazia(lista) ) {
		printf("\t\t\tLista vazia\n");
		return;
	}

	printf("\n\t\t\tLista:\n");
	Bloco* ind = lista.prim;
	while ( ind != lista.ult->prox ) {
		printf("\t\t\t%d\tfreq %d\tend %p\n",ind->num,ind->freq,ind);
		ind = ind->prox;
	}
	printf("\n");

}

Bloco* buscarMeio (Lista lista){

	Bloco* pontDevagar = lista.prim;
	Bloco* pontRapido = lista.prim;

	// Quando pontRapido chegar ao final, pontDevagar estará no meio da lista
	while ( pontRapido != lista.ult && pontRapido->prox != lista.ult ) {

		pontDevagar = pontDevagar->prox;
		pontRapido = pontRapido->prox->prox;

	}

	return pontDevagar;

}

Lista merge(Lista lista1, Lista lista2){

	// Verifica se uma das listas está vazia
	if ( listaVazia(lista1) )
		return lista1;
	if ( listaVazia(lista2) )
		return lista2;

	// Lista auxiliar para armazenar os valores de forma ordenada
	Lista listaAux;
	inicializa(&listaAux);

	// Blocos para percorrer as duas partes das listas
	Bloco* atual1 = lista1.prim;
	Bloco* atual2 = lista2.prim;

	// Enquanto nenhuma das listas estiver concluída
	while ( atual1 != lista1.ult->prox && atual2 != lista2.ult->prox ) {

		// Insere o ponteiro com menor elemento em listaAux
		if ( atual1->num < atual2->num ) {
			inserirBloco(&listaAux,atual1);
			atual1 = atual1->prox;
		}

		else {

			inserirBloco(&listaAux,atual2);
			atual2 = atual2->prox;

		}

	}

	// Encadeia o restante da lista
	if ( atual1 == lista1.ult->prox ) {
		inserirBloco(&listaAux,atual2);
		listaAux.ult = lista2.ult;

	}
	else { // atual2 = lista2.ult->prox
		inserirBloco(&listaAux,atual1);
		listaAux.ult = lista1.ult;
		// Encadeamos o final de listaAux com a continuação de lista2 (lista2.ult->prox)
		listaAux.ult->prox = atual2;
	}

	return listaAux;

}

void mergeSort(Lista* lista)

	/* Se houver apenas um elemento na lista, nenhuma
	 * operação será feita */
	if ( lista->prim != lista->ult ) {

		Bloco* meio = buscarMeio(*lista);

		// Cria as duas listas
		Lista lista1;
		lista1.prim = lista->prim;
		lista1.ult = meio;

		Lista lista2;
		lista2.prim = meio->prox;
		lista2.ult = lista->ult;

		// Ordena ambas as partes
		mergeSort(&lista1);
		mergeSort(&lista2);
			
		// Intercala as listas
		*lista = merge(lista1,lista2);
	}

}

void removerRepetidos(Lista* lista){
		
	if ( listaVazia(*lista) ){
		printf("\t\t\tLista vazia\n");
		return;
	}

	Bloco* atual = lista->prim;
	
	while ( atual != lista->ult ) {

		// Caso seja encontrado um numero igual ao atual
		if ( atual->num == atual->prox->num ) {

			Bloco* aux = atual->prox;
			
			// Se o último elemento for removido,
			// atualiza lista->ult
			if ( aux == lista->ult )
				lista->ult = atual;
				
			atual->freq++;
			atual->prox = aux->prox; // encadeia atual com o ponteiro duas posições a frente
			free(aux);
	
		// Continua procurando para os demais elementos da lista
		} else {

			atual = atual->prox;

		}

	}

}

void opcaoGerarInserir(Lista * lista){
	
	printf("\t\t\tEntre com a quantidade de valores: ");
	int tam;
	scanf("%d",&tam);
	while( tam <= 0 ){
		printf("\t\t\tEntre com uma quantidade válida: ");
		scanf("%d",&tam);
	}
	printf("\t\t\tGerando e inserindo valores...");
	gerarValores(lista,tam);
	
}

void opcaoOrdenar(Lista * lista){
	
	printf("\t\t\tOrdenando lista...");
	clock_t inicio = clock();
	mergeSort(lista);
	clock_t fim = clock();
	printf("\t\t\tTempo de ordenacao: %.10f s\n",(double)(fim-inicio)/(CLOCKS_PER_SEC));
	
}

void menu(Lista* lista){
	
	int opcao;
	
	do {

		printf("\n");
		printf("\t\t\t1 - Inserir e Gerar valores\n");
		printf("\t\t\t2 - Ordenar lista\n");
		printf("\t\t\t3 - Remover elementos repetidos\n");
		printf("\t\t\t4 - Mostrar lista\n");
		printf("\t\t\t0 - Sair\n\n");
		printf("\t\t\tEntre com uma opcao: ");
		scanf("%d",&opcao);
		
		switch(opcao){
			case 1:
				opcaoGerarInserir(lista);
				break;
			case 2:
				opcaoOrdenar(lista);
				break;
			case 3:
				printf("\t\t\tRemovendo valores repetidos...");
				removerRepetidos(lista);
				break;
			case 4:
				mostrarLista(*lista);
				break;
			case 0:
				break;
			default:
				printf("\t\t\tInforme uma opcao valida...");
				break;
		}
		
		printf("\n\t\t\tPressione uma tecla para continuar...");
		getchar(); getchar(); // Aguarda uma tecla ser pressionada
		printf("\e[H\e[2J"); // Limpar tela
		
	} while (opcao != 0);
	
}
