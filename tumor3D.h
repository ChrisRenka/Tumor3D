#ifndef TUMOR3D_H
#define TUMOR3D_H

#define TAM 100
#define PASSOS 500
#define PASSOS_INIC 30
#define VASOS 55
#define ISIM 100

#define H 1

#define OP 1.25e-5
#define OQ 8.2e-6
#define GT 1.4e-3
#define TD 16
#define TN 240

#define DO 1.82e-5
#define OKV 8.2e-3
#define OPC 0.2
#define OQC 0.1
#define OO 2.8e-3
#define DG 1.82e-5
#define GKV 5e-6
#define GPC 1e-3
#define GQC 1e-3
#define GO 2.8e-3

#define AO 0.0
#define DA 1.82e-4
#define AKV -8.2e-3
#define APC 0.0
#define AQC 0.0
#define AN 5.0e-1
#define AP 1.25e-5
#define AT 20
#define MAX_VIZS 6

typedef struct{
	char viz;
	char vizS;
	char tipo;
	unsigned int tDiv;
    double c[3];
    double c2[3];
} Celula;

/*
viz: 0-26 vizinhos vazios
tipo: 'v' vazio
	 'p' proliferativa
	 'q' quiescente
	 'n' necrótica
	 's' vaso sanguíneo
concentrações:  c[0] = oxigênio
                c[1] = glicose
                c[2] = subst. angiogênese
*/

Celula*** criarRede();
void inicializarRede(Celula ***rede);
void semearRede(Celula ***rede);
void percorrerRede(Celula ***rede);
void proliferar(Celula ***aux, int x, int y, int z);
void proliferarVaso(Celula ***rede, int x, int y, int z);
int** vizinhosVazios(Celula ***rede, int x, int y, int z);
int maiorConcentracao(Celula ***rede, int **vazios, int num);
void executar(Celula ***rede);
void atualizaVizinhos(Celula ***rede, int x, int y, int z, int inc);
void atualizaVizinhosS(Celula ***rede, int x, int y, int z, int inc);
void criaVasos(Celula ***rede);

double laplaceNum(Celula ***rede, int x, int y, int z, int tipo);
void reacDiff(Celula ***rede, int x, int y, int z, int tipo);
void reageDifunde(Celula ***rede);
void atualizaCons(Celula ***rede, int tipo);

Celula*** copiarRede(Celula ***rede);
void imprimirRede(Celula ***rede);
void imprimirConcO(Celula ***rede);
void imprimirConcG(Celula ***rede);
void imprimirConcA(Celula ***rede);
void destruirRede(Celula ****rede);
void salvarRede(Celula ***rede, int n);

void setup();
void salvaDados();

#endif
