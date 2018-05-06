#include"tumor3D.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

int totalCelulas = 0;
int nSim = 0;
char bevac = 0;

Celula*** criarRede(){
	int i,j;
	Celula ***rede = (Celula***)malloc(TAM*sizeof(Celula**));

	for (i = 0;i < TAM;i++) {
		rede[i] = (Celula**) malloc(TAM*sizeof(Celula*));
		for (j = 0;j < TAM;j++) {
			rede[i][j] = (Celula*)malloc(TAM*sizeof(Celula));
		}
	}

	return rede;
}

void inicializarRede(Celula ***rede){
	int i, j, k;

	for(i=0;i<TAM;i++){
		for(j=0;j<TAM;j++){
			for(k=0;k<TAM;k++){
				rede[i][j][k].viz = 26;
				rede[i][j][k].vizS = 0;
				rede[i][j][k].tipo = 'v';
				rede[i][j][k].tDiv = 0;
                rede[i][j][k].c[0] = OO;
                rede[i][j][k].c[1] = GO;
                rede[i][j][k].c[2] = AO;
                rede[i][j][k].c2[0] = 0.0;
                rede[i][j][k].c2[1] = 0.0;
                rede[i][j][k].c2[2] = 0.0;
			}
		}
	}
}

void semearRede(Celula ***rede){
	rede[TAM/2][TAM/2][TAM/2].tipo = 'p';
	//rede[TAM/2][TAM/2][TAM/2].tDiv = TD+1;
	atualizaVizinhos(rede, TAM/2, TAM/2, TAM/2, -1);
}

void executar(Celula ***rede){
    int i=0;

    printf("Difundindo substâncias\n");
    for(i=0;i<PASSOS_INIC;i++){
        printf("%d\r", i);
        reageDifunde(rede);
    }
    printf("\n");

    printf("Simulando tumor\n");
    semearRede(rede);
    for(i=0;i<PASSOS;i++){
        printf("%d\r", i);
        percorrerRede(rede);
        reageDifunde(rede);
        if(i%ISIM == 0){
            salvarRede(rede, i/ISIM + 1);
        }
    }
    salvarRede(rede, i/ISIM + 1);
    printf("\n");
}

void percorrerRede(Celula ***rede){
	int i, j, k;
	//Celula ***aux = NULL;

    //aux = copiarRede(*rede);

	for(i=0;i<TAM;i++){
		for(j=0;j<TAM;j++){
			for(k=0;k<TAM;k++){
				if(rede[i][j][k].tipo=='v'){
                    continue;
				}

				if(rede[i][j][k].tipo=='p'){
					if(rede[i][j][k].c[1]<GT){
                        rede[i][j][k].tipo = 'n';
                        rede[i][j][k].tDiv = 0;
                        rede[i][j][k].c[2]+=AN;
					}
					else if(rede[i][j][k].c[0]<OP){
                        rede[i][j][k].tipo = 'q';
                        rede[i][j][k].tDiv = 0;
					}
					else{
                        if((rede[i][j][k].viz>0) && (rede[i][j][k].tDiv>TD)){
                            proliferar(rede, i, j, k);
                        }
                        else{
                            rede[i][j][k].tDiv++;
                        }
					}
				}
				else if(rede[i][j][k].tipo=='q'){
					if((rede[i][j][k].c[1]<GT) || (rede[i][j][k].c[0]<OQ)){
						rede[i][j][k].tipo = 'n';
						rede[i][j][k].c[2]+=AN;
					}
					else if(rede[i][j][k].c[0]>OP){
						rede[i][j][k].tipo = 'p';
					}
				}
				else if(rede[i][j][k].tipo=='n'){
					if((rede[i][j][k].tDiv>=TN) && (rede[i][j][k].viz>0)){
						rede[i][j][k].tipo = 'v';
						rede[i][j][k].tDiv = 0;
						atualizaVizinhos(rede, i, j, k, 1);
						totalCelulas--;
					}
					else{
						rede[i][j][k].tDiv++;
					}
				}
				else if(rede[i][j][k].tipo=='s'){
					if((rede[i][j][k].viz>0) && (rede[i][j][k].tDiv>AT) && (rede[i][j][k].c[2]>AP) && (rede[i][j][k].vizS<=MAX_VIZS)){
						proliferarVaso(rede, i, j, k);
						//printf("Novo vaso!\n");
					}
					else{
						rede[i][j][k].tDiv++;
					}
				}
			}
		}
	}
	//destruirRede(rede);
	//*rede = aux;
}

void proliferar(Celula ***aux, int x, int y, int z){
    char total;
    int **viz = NULL;
    int novo;
    int pos[3];

    /*
    if((rand()%100)>=P_PROL){
        return;
    }
    */
    viz = vizinhosVazios(aux, x, y, z);
    total = aux[x][y][z].viz;

    if(total==0){
        return;
    }

    novo = rand()%(int)total;
    pos[0] = viz[novo][0];
    pos[1] = viz[novo][1];
    pos[2] = viz[novo][2];

    aux[pos[0]][pos[1]][pos[2]].tipo = 'p';
    atualizaVizinhos(aux, pos[0], pos[1], pos[2], -1);
    aux[x][y][z].tDiv = 0;
    totalCelulas++;

}

void proliferarVaso(Celula ***aux, int x, int y, int z){
	char total;
    int **viz = NULL;
    int novo;
    int pos[3];

    viz = vizinhosVazios(aux, x, y, z);
    total = aux[x][y][z].viz;

    if(total==0){
        return;
    }

    novo = maiorConcentracao(aux, viz, total);
    pos[0] = viz[novo][0];
    pos[1] = viz[novo][1];
    pos[2] = viz[novo][2];

    aux[pos[0]][pos[1]][pos[2]].tipo = 's';
    atualizaVizinhos(aux, pos[0], pos[1], pos[2], -1);
    atualizaVizinhosS(aux, pos[0], pos[1], pos[2], 1);
    aux[x][y][z].tDiv = 0;
}

int** vizinhosVazios(Celula ***rede, int x, int y, int z){
    int i, j, k, cont = 0;
    int **viz = NULL;
    char vazios = rede[x][y][z].viz;

    viz = (int**) malloc(vazios*sizeof(int*));
    for(i=0;i<vazios;i++){
        viz[i] = (int*)malloc(3*sizeof(int));
    }
    for(i=0;i<vazios;i++){
        for(j=0;j<3;j++){
            viz[i][j] = 255;
        }
    }

    for(k=-1;k<2;k++){
        for(i=-1;i<2;i++){
            for(j=-1;j<2;j++){
                if(rede[x+i][y+j][z+k].tipo=='v'){
                    viz[cont][0] = x+i;
                    viz[cont][1] = y+j;
                    viz[cont][2] = z+k;
                    cont++;
                }
            }
        }
    }

    return viz;
}

int maiorConcentracao(Celula ***rede, int **vazios, int num){
	int i;
	double maior = 0.0;
	int maiorCord;

	for(i=0;i<num;i++){
		if(rede[vazios[i][0]][vazios[i][1]][vazios[i][2]].c[2]>maior){
			maior = rede[vazios[i][0]][vazios[i][1]][vazios[i][2]].c[2];
			maiorCord = i;
		}
	}

	return maiorCord;
}

void atualizaVizinhos(Celula ***rede, int x, int y, int z, int inc){
    int i, j, k;

    for(k=-1;k<2;k++){
        for(i=-1;i<2;i++){
            for(j=-1;j<2;j++){
                if((i!=0)||(j!=0)||(k!=0)){
                    rede[x+i][y+j][z+k].viz+=inc;
                }
            }
        }
    }
}

void atualizaVizinhosS(Celula ***rede, int x, int y, int z, int inc){
    int i, j, k;

    for(k=-1;k<2;k++){
        for(i=-1;i<2;i++){
            for(j=-1;j<2;j++){
                if((i!=0)||(j!=0)||(k!=0)){
                    rede[x+i][y+j][z+k].vizS+=inc;
                }
            }
        }
    }
}

void criaVasos(Celula ***rede){
    int c1, c2, eixo;
    int i, k;

    for(i=0;i<VASOS;i++){
		eixo = rand()%3;
		c1 = 1+rand()%(TAM-2);
		c2 = 1+rand()%(TAM-2);
		switch (eixo){
			case 0:
				for(k=1;k<(TAM-1);k++){
					if(rede[k][c1][c2].tipo == 'v'){
						rede[k][c1][c2].tipo = 's';
						atualizaVizinhos(rede, k, c1, c2, -1);
						atualizaVizinhosS(rede, k, c1, c2, 1);
					}
				}
				break;
			case 1:
				for(k=1;k<(TAM-1);k++){
					if(rede[c1][k][c2].tipo == 'v'){
						rede[c1][k][c2].tipo = 's';
						atualizaVizinhos(rede, c1, k, c2, -1);
						atualizaVizinhosS(rede, k, c1, c2, 1);
					}
				}
				break;
			case 2:
				for(k=1;k<(TAM-1);k++){
					if(rede[c1][c2][k].tipo == 'v'){
						rede[c1][c2][k].tipo = 's';
						atualizaVizinhos(rede, c1, c2, k, -1);
						atualizaVizinhosS(rede, k, c1, c2, 1);
					}
				}
				break;
		}
    }

}

double laplaceNum(Celula ***rede, int x, int y, int z, int tipo){
	return (rede[x+H][y][z].c[tipo]+rede[x-H][y][z].c[tipo]
			+rede[x][y+H][z].c[tipo]+rede[x][y-H][z].c[tipo]
			+rede[x][y][z+H].c[tipo]+rede[x][y][z-H].c[tipo]
			-6*rede[x][y][z].c[tipo])/(H*H);
}

void reacDiff(Celula ***rede, int x, int y, int z, int tipo){
	double d, cv, cc;
	if(tipo==0){
		d = DO;
		if(rede[x][y][z].tipo=='s'){
			cv = OKV;
		}
		else{
			cv = 0.0;
		}
		if(rede[x][y][z].tipo=='p'){
			cc = OPC;
		}
		else if(rede[x][y][z].tipo=='q'){
			cc = OQC;
		}
		else{
			cc = 0.0;
		}
	}
	else if(tipo==1){
		d = DG;
		if(rede[x][y][z].tipo=='s'){
			cv = GKV;
		}
		else{
			cv = 0.0;
		}
		if(rede[x][y][z].tipo=='p'){
			cc = GPC;
		}
		else if(rede[x][y][z].tipo=='q'){
			cc = GQC;
		}
		else{
			cc = 0.0;
		}
	}
	else if(tipo==2){
		d = DA;
		if(rede[x][y][z].tipo=='s'){
			cv = AKV;
		}
		else{
			cv = 0.0;
		}
		if(rede[x][y][z].tipo=='p'){
			cc = APC;
		}
		else if(rede[x][y][z].tipo=='q'){
			cc = AQC;
		}
		else{
			cc = 0.0;
		}
	}
	/*
	else{
		d = DB;
		if(rede[x][y][z].tipo=='s'){
			cv = BKV;
		}
		else{
			cv = 0.0;
		}
		if(rede[x][y][z].tipo=='p'){
			cc = BPC;
		}
		else if(rede[x][y][z].tipo=='q'){
			cc = BQC;
		}
		else{
			cc = 0.0;
		}
	}
	*/

    rede[x][y][z].c2[tipo] = rede[x][y][z].c[tipo]
                            + (d*laplaceNum(rede, x, y, z, tipo))
                            + rede[x][y][z].c[tipo]*(cv-cc);
	//return (d*laplaceNum(rede, x, y, z, tipo))
	//		+rede[x][y][z].c[tipo]*(cv-cc);
}

void reageDifunde(Celula ***rede){
    int t, i, j, k;

    for(t=0;t<3;t++){
        for(i=1;i<(TAM-1);i++){
            for(j=1;j<(TAM-1);j++){
                for(k=1;k<(TAM-1);k++){
                    reacDiff(rede, i, j, k, t);
                }
            }
        }
        atualizaCons(rede, t);
    }

    //Descomentar o trecho a seguir para adicionar a difusão/reação do bevacizumabe

    /*
    t = 3;
    if((totalCelulas>50)||(bevac==1)){
        bevac = 1;
        for(i=1;i<(TAM-1);i++){
            for(j=1;j<(TAM-1);j++){
                for(k=1;k<(TAM-1);k++){
                    reacDiff(rede, i, j, k, t);
                }
            }
        }
        atualizaCons(rede, t);
    }
    */
}

void atualizaCons(Celula ***rede, int tipo){
    int i, j, k;

    for(i=1;i<(TAM-1);i++){
		for(j=1;j<(TAM-1);j++){
			for(k=1;k<(TAM-1);k++){
				rede[i][j][k].c[tipo] = rede[i][j][k].c2[tipo];
				//rede[i][j][k].c2[tipo] = 0.0;
			}
		}
	}
}



/*Auxiliar*/
Celula*** copiarRede(Celula ***rede){
	Celula ***aux = NULL;
	int i, j, k;

	aux = criarRede();
	for(i=0;i<TAM;i++){
		for(j=0;j<TAM;j++){
			for(k=0;k<TAM;k++){
				aux[i][j][k].viz = rede[i][j][k].viz;
				aux[i][j][k].vizS = rede[i][j][k].vizS;
				aux[i][j][k].tipo = rede[i][j][k].tipo;
				aux[i][j][k].tDiv = rede[i][j][k].tDiv;
				aux[i][j][k].c[0] = rede[i][j][k].c[0];
				aux[i][j][k].c[1] = rede[i][j][k].c[1];
				aux[i][j][k].c[2] = rede[i][j][k].c[2];
				aux[i][j][k].c2[0] = rede[i][j][k].c2[0];
				aux[i][j][k].c2[1] = rede[i][j][k].c2[1];
				aux[i][j][k].c2[2] = rede[i][j][k].c2[2];
			}
		}
	}
	return aux;
}

void imprimirRede(Celula ***rede){
	int i, j, k;

	for(k=0;k<TAM;k++){
		for(j=0;j<TAM;j++){
			for(i=0;i<TAM;i++){
				printf("%c", rede[i][j][k].tipo);
			}
			printf("\n");
		}
		printf("\n");
	}
}

void imprimirConcO(Celula ***rede){
    int i, j, k;

	for(k=0;k<TAM;k++){
		for(j=0;j<TAM;j++){
			for(i=0;i<TAM;i++){
				printf("%6.5f ", rede[i][j][k].c[0]);
			}
			printf("\n");
		}
		printf("\n");
	}
}

void imprimirConcG(Celula ***rede){
    int i, j, k;

	for(k=0;k<TAM;k++){
		for(j=0;j<TAM;j++){
			for(i=0;i<TAM;i++){
				printf("%9.8f ", rede[i][j][k].c[1]);
			}
			printf("\n");
		}
		printf("\n");
	}
}

void imprimirConcA(Celula ***rede){
    int i, j, k;

	for(k=0;k<TAM;k++){
		for(j=0;j<TAM;j++){
			for(i=0;i<TAM;i++){
				printf("%6.5f ", rede[i][j][k].c[2]);
			}
			printf("\n");
		}
		printf("\n");
	}
}

void destruirRede(Celula ****rede){
	int i, j;

	for(i=0;i<TAM;i++){
		for(j=0;j<TAM;j++){
			free((*rede)[i][j]);
		}
		free((*rede)[i]);
	}
	free(*rede);
	(*rede)=NULL;
}

void salvarRede(Celula ***rede, int n){
    FILE *proli = NULL;
    FILE *vasos = NULL;
    FILE *quie = NULL;
    FILE *necro = NULL;
    int i, j, k;
    char aSim[50];

    sprintf(aSim, "Resultados\\%d\\proli%d.txt", nSim, n);
    proli = fopen(aSim, "w");
    sprintf(aSim, "Resultados\\%d\\vasos%d.txt", nSim, n);
    vasos = fopen(aSim, "w");
    sprintf(aSim, "Resultados\\%d\\quie%d.txt", nSim, n);
    quie = fopen(aSim, "w");
    sprintf(aSim, "Resultados\\%d\\necro%d.txt", nSim, n);
    necro = fopen(aSim, "w");

    for(i=0;i<TAM;i++){
        for(j=0;j<TAM;j++){
            for(k=0;k<TAM;k++){
                if(rede[i][j][k].tipo=='p'){
                    fprintf(proli, "%d,%d,%d\n", i, j, k);
                }
                else if(rede[i][j][k].tipo=='s'){
                    fprintf(vasos, "%d,%d,%d\n", i, j, k);
                }
                else if(rede[i][j][k].tipo=='q'){
                    fprintf(quie, "%d,%d,%d\n", i, j, k);
                }
                else if(rede[i][j][k].tipo=='n'){
                    fprintf(necro, "%d,%d,%d\n", i, j, k);
                }
            }
        }
    }

    fclose(proli);
    fclose(quie);
    fclose(necro);
    fclose(vasos);
}

void setup(){
    DIR *d = NULL;
    char dSim[20];

    d = opendir("Resultados");
    if(!d){
        mkdir("Resultados");
        mkdir("Resultados\\1");
        nSim = 1;
        salvaDados();
        return;
    }
    closedir(d);
    d = NULL;
    do{
        nSim++;
        sprintf(dSim, "Resultados\\%d", nSim);
        d = opendir(dSim);
    }while(d!=NULL);
    closedir(d);
    mkdir(dSim);
    salvaDados();
}

void salvaDados(){
    FILE *dados = NULL;
    char dDados[20];

    sprintf(dDados, "Resultados\\%d\\dados.txt", nSim);
    dados = fopen(dDados, "w");
    fprintf(dados, "Tamanho: %d\n", TAM);
    fprintf(dados, "Passos difusão: %d\n", PASSOS_INIC);
    fprintf(dados, "Passos simulação: %d\n", PASSOS);
    fprintf(dados, "Vasos: %d\n", VASOS);

    fprintf(dados, "DA: %f\n", DA);
    fprintf(dados, "AKV: %f\n", AKV);
    fprintf(dados, "APC: %f\n", APC);
    fprintf(dados, "AQC: %f\n", AQC);
    fprintf(dados, "AN: %f\n", AN);
    fprintf(dados, "AP: %f\n", AP);
    fprintf(dados, "AT: %d\n", AT);
    fprintf(dados, "MAX_VIZS: %d\n", MAX_VIZS);

    fclose(dados);
}
















