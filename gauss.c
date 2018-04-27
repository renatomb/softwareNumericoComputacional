#include <conio.h>
#include <iostream.h>
#define mtx 3000
#include <matrix.h>

void main() {
	zero_maquina();
	le_matrix();
	if (!testa_matrix()) {
		printf("\nERRO: O sistema fornecido possui uma linha ou coluna zerada!");
		return;
	}
	for(int r=0;r<dim;r++) {
		int lin_pivo=r-1;
		for(int i=r;i<dim;i++) {
			if(matrix[i][r] != zero) {
				lin_pivo=i;
				break;
			}
		}
		if (lin_pivo<r) {
			printf("\nERRO: Nenhum elemento da coluna pode ser usado como pivo para a %d a equacao!",(r+1));
			return;
		}
		if (lin_pivo>r) {
			troca_linha(lin_pivo,r);
			lin_pivo=r;
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
	for (int i=0;i<dim;i++){
		printf("\nx[%d]= %10.4f",(i+1),solucao[i]);
	}
}
