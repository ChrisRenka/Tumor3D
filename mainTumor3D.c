#include"tumor3D.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

	Celula ***rede = NULL;

	srand(time(NULL));
	rand();

	setup();

	rede = criarRede();
	inicializarRede(rede);

	criaVasos(rede);


	//semearRede(rede);
	executar(rede);
	//imprimirRede(rede);
	//imprimirConcO(rede);
	//imprimirConcG(rede);
	//imprimirConcA(rede);
	//salvarRede(rede);

	destruirRede(&rede);
	return 0;

}
