#include <conio.h>
#include <iostream.h>
#include <math.h>
#define mtx 3000
#include <matrix.h>

int ordem[mtx];
int maior_elemento(int i);
void ordena_solucoes();
void troca_coluna(int c1, int c2);

void main() {
	le_matrix();
	if (!testa_matrix()) {
		printf("\nERRO: O sistema fornecido possui uma linha ou coluna zerada!");
		return;
	}
	for(int i=0;i<dim;i++) { ordem[i]=i; }
	for(int r=0;r<dim;r++) {
		int colm;
		colm=maior_elemento(r);
		if (colm != r) {
			troca_coluna(r,colm);
		}
		float aux, pivo;
		pivo=matrix[r][r];
		for (int i=r+1;i<dim;i++) {
			aux=matrix[i][r]*(-1);
			for (int j=0;j<=dim;j++) {
				matrix[i][j]=matrix[i][j]+(aux/pivo)*matrix[r][j];
			}
		}
	}
	for(int i=0;i<mtx;i++) { solucao[i]=0; }
    printf("Matriz triangular superior do sistema: ");
	imp_matrix();
	back_subst();
	printf("\nConjunto de solucoes:");
	ordena_solucoes();
	for (int i=0;i<dim;i++){
		printf("\nx[%d]= %10.4f",(i+1),solucao[i]);
	}
}

int maior_elemento(int inicio) {
	int lin_maior, col_maior, i;
	float maior;
	i=inicio;
	maior=matrix[i][i];
	col_maior=i;
	lin_maior=i;
	do {
		for(int j=i; j<dim; j++) {
			if (fabs(matrix[i][j]) > fabs(maior)) {
				lin_maior=i;
				col_maior=j;
				maior=matrix[i][j];
		 	}
		}
		i++;
	} while (i<dim);
	if (lin_maior != inicio) {
		troca_linha(inicio,lin_maior);
	}
    return col_maior;
}

void ordena_solucoes() {
	float nato[mtx];
	for (int i=0;i<dim;i++){ nato[i]=solucao[i]; }
	for (int i=0;i<dim;i++) {
		solucao[ordem[i]]=nato[i];
	}
}

void troca_coluna(int c1, int c2){
	float aux[mtx];
	for (int i=0;i<mtx;i++) {
		aux[i]=matrix[i][c1];
		matrix[i][c1]=matrix[i][c2];
		matrix[i][c2]=aux[i];
	}
	int auxtc;
	auxtc=ordem[c1];
	ordem[c1]=ordem[c2];
	ordem[c2]=auxtc;
}

