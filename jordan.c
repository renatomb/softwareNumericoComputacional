#include <conio.h>
#include <iostream.h>
#define mtx 3000
#include <matrix.h>

void main() {
	le_matrix();
	if (!testa_matrix()) {
		printf("\nERRO: O sistema fornecido possui uma linha ou coluna zerada!");
		return;
	}
	for(int i=0;i<dim;i++) {
		if (matrix[i][i] != 1) {
			float aux=0;
			for(int j=0;j<=dim;j++) {
				if (aux==0) { aux=matrix[i][i]; }
				matrix[i][j]=matrix[i][j]/aux;
			}
		}
		for (int k=0;k<dim;k++) {
			if (k == i) {
				k=k+1;
				if (k >= dim) { break; }
			}
			float aux2;
			aux2=matrix[k][i];
			for (int j=0;j<=dim;j++) { matrix[k][j]=matrix[k][j]-(aux2*matrix[i][j]); }
		}
	}
	for(int i=0;i<mtx;i++) { solucao[i]=0; }
    printf("Matriz triangular superior do sistema: ");
	imp_matrix();
	back_subst();
	printf("\nConjunto de solucoes:");
	for (int i=0;i<dim;i++){
		printf("\nx[%d]= %10.4f",(i+1),solucao[i]);
	}
}
