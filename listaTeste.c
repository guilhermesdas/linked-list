// Arquivo principal para utilização das funções da biblioteca
// lista.h

#include "lista.h"

#define MAX 100

int main(){
	
	Lista lista;
	inicializa(&lista);
	menu(&lista);
	
	return 0;
}
