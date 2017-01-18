#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Intervalo dos números a serem gerados
// [0,RANDMAX)
#define RANDMAX 10000

// OPCOES PARA ORDENACAO
#define MERGE_SORT 2
#define SELECTION_SORT 3

// Nós / Bloco
// Bloco (estrutura/registro) com os Dados (numero e frequencia) e um ponteiro para o bloco seguinte
typedef struct bloco {
	int num;
	int freq;
	struct bloco * prox;
} Bloco;

// Lista
struct {
	Bloco* prim;
	Bloco* ult;
} typedef Lista;

/////////////////////////////////////////////////

// A lista só é passada como ponteiro (Lista *)
// quando a função alterar os valores de prim e ult

// Inicializa a lista
void inicializa(Lista* lista);

// Verifica se a lista está vazia
int listaVazia(Lista lista);

// Insere um novo ponteiro do tipo Bloco
// contendo o numero dado à lista
void inserirNumero(Lista* lista, int num);

// Insere um novo ponteiro do tipo Bloco à lista
void inserirBloco(Lista* lista, Bloco* novo);

// Gerar valores aleatórios e inseri-los à lista
void gerarValores(Lista* lista, int tam);

// Exibir todos os elementos da lista com sua respectiva
// frequencia e endereço de memória
void mostrarLista(Lista lista);

// Função para encontrarmos o ponteiro do tipo Bloco
// que está na metade a lista
Bloco* buscarMeio (Lista lista);

// Intercalar duas listas ordenadas
Lista merge(Lista lista1, Lista lista2);

// Repartir a lista em duas partes recursivamente ate que ambas esteja
// ordenadas e intervalá-las por meio da funcao merge
void mergeSort(Lista* lista);

// Dada uma lista, será retornado o ponteiro anterior ao menor elemento da lista
// Caso o menor seja o primeiro, será retornado NULL
Bloco* buscarAnteriorMenor( Lista * lista );

// Buscar o menor elemento da lista e o recortar da mesma
Bloco* buscarRemoverMenor( Lista * lista);

// Ordenar utilizando o método Selection Sort
void selectionSort(Lista* lista);

// Funcao para remover os elementos sequencias repetidos da lista
// e acrescentar a frequencia em um deles
void removerRepetidos(Lista* lista);

// Função com operações a se fazer quando for solicitado
// para gerar e inserir valores na lista
void opcaoGerarInserir(Lista * lista);

// Função com operações a se fazer quando for solicitado
// para ordenar utilizando uma determinado metodo
void opcaoOrdenar(Lista * lista, int metodo);

// Função para gerar um menu de opções para acesso das funções
void menu();

