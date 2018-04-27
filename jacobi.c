#include <conio.h>
#include <iostream.h>
#include <stdlib.h>
#include <math.h>
#define mtx 3000
#include <matrix.h>
#define imax 900

int maior_diagonal();
int testa_cond();
int testa_erro(int iteracao, float tol);
float x[imax+1][mtx];

void main() {
	float tole;
	int erro, i_max;
	printf("Entre com a tolerancia: ");
	scanf("%f",&tole);
	printf("Numero maximo de iteracoes: ");
	scanf("%d",&i_max);
	le_matrix();
	if (!testa_cond()) {
		if (maior_diagonal() && testa_cond()) {
			printf("\nO sistema estava mal-condicionado.\nO condicionamento foi realizado com sucesso! :)\nNovo sistema:");
			imp_matrix();
		}
		else {
			printf("\nAVISO: O sistema esta mal-condicionado!\nNao foi possivel realizar o condicionamento. :(");
		}
	}
	else {
		printf("\nO sistema fornecido esta bem condicionado! :]");
	}
	printf("\nArbitre os valores das incognitas:\n");
	for (int i=0; i<dim;i++) {
		printf("x[%d]=",(i+1));
		scanf("%f",&x[0][i]);
	}
	int k=0;
	do {
		for (int i=0; i<dim; i++) {
			x[k+1][i]=matrix[i][dim];
			for (int j=0; j<dim; j++) {
				if (i != j) {
					x[k+1][i]=x[k+1][i]-(matrix[i][j]*x[k][j]);
				}
			}
			x[k+1][i]=x[k+1][i]/matrix[i][i];
		}
		erro=testa_erro(k,tole);
		k++;
	} while (erro && k<i_max);
	printf("\nForam realizadas %d iteracoes.",(k-1));
	if (k >= i_max) { printf("ERRO: O sistema nao convergiu! :~("); }
	else {
		printf("\nConjunto de solucoes:");
		for (int i=0;i<dim;i++){
			printf("\nx[%d]= %10.4f",(i+1),x[k][i]);
		}
	}
}


int maior_diagonal() {
	int pos_maior[mtx], checagem[mtx];
	float maior;
	for (int i=0; i<dim; i++) {
		maior=matrix[i][0];
		pos_maior[i]=0;
		for(int j=0; j<dim; j++) {
			if (fabs(matrix[i][j]) > fabs(maior)) {
				maior=matrix[i][j];
				pos_maior[i]=j;
			}
		}
	}
	for(int i=0;i<dim;i++){ checagem[i]=0; }
	for(int i=0;i<dim;i++){ checagem[pos_maior[i]]=1; }
	for(int i=0;i<dim;i++){ if (checagem[i] == 0) return 0; }
	for(int i=0;i<dim;i++) {
		if (i != pos_maior[i]) { troca_linha(i,pos_maior[i]); }
		int auxiliar;
		auxiliar=pos_maior[i];
		pos_maior[auxiliar]=auxiliar;
		pos_maior[i]=i;
	}
	return 1;
}

int testa_cond() {
	  for (int i=0; i<dim; i++) {
			float soma=0;
			for (int j=0; j<dim; j++) {
				if (i != j) soma=soma+fabs(matrix[i][j]);
			}
			if (fabs(matrix[i][i]) < soma) return 0;
	  }
	  return 1;
}

int testa_erro(int iteracao, float tol){
	for(int i=0; i<dim; i++) {
		if (fabs(x[iteracao][i] - x[iteracao-1][i]) > tol) {
			return 1;
		}
	}
	return 0;
}




