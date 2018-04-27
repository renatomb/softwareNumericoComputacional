#include <iostream.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#define mtx 3000
#define imax 900

int maior_diagonal();
int testa_cond();
int testa_erro(int iteracao, float tol);

float matrix[mtx][mtx+1],solucao[mtx],backup[mtx][mtx+1],x[imax+1][mtx],zero,tole;
int dim,ordem[mtx],erro, i_max;
void troca_linha(int l1, int l2);
void imp_matrix();
void le_matrix();
void back_subst();
void zero_maquina();
int testa_matrix();

int maior_elemento(int i);
void ordena_solucoes();
void troca_coluna(int c1, int c2);


void gauss();
void pivota();
void jordan();
void seidel();
void jacobi();

void main() {
	zero_maquina();
	int dados=0;
	for(;;) {
		printf("\n\nSistemas de Equacoes Lineares\n---------------------------------\n\n1 - Eliminacao de gauss\n2 - Pivotacao completa\n3 - Metodo de jordan\n4 - Metodo de Jacobi\n5 - Metodo de Gauss-Seidel\n6 - Sair\n\nSelecione o metodo a ser usado: ");
		char opcao;
		opcao=getche();
		if (!dados && opcao != '6') {
			le_matrix(); dados=1;
			for (int i=0;i<dim;i++) {
				for (int j=0; j<=dim;j++) {
					backup[i][j]=matrix[i][j];
				}
			}
		}
		if (!testa_matrix()) {
			printf("\nERRO: O sistema fornecido possui uma linha ou coluna zerada!");
			dados=0;
		}
		else {
			switch(opcao) {
				case '1':
					gauss();
					break;
				case '2':
					pivota();
					break;
				case '3':
					jordan();
					break;
				case '4':
					jacobi();
					break;
				case '5':
					seidel();
					break;
				case '6':
					return;
				default:
					printf("\nOpcao invalida! Selecione o metodo desejado: ");
			}
			printf("\n\nTecle 'S' caso deseje utilizar os mesmos dados para resolver por outro metodo.");
			opcao=getche();
			if (opcao == 's' || opcao == 'S') {
				dados=1;
				for (int i=0;i<dim;i++) {
					for (int j=0; j<=dim;j++) {
						matrix[i][j]=backup[i][j];
					}
				}
			}
			else { dados=0; }
		}
	}
}

void gauss() {
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
    printf("\n\nMatriz triangular superior do sistema: ");
	imp_matrix();
	back_subst();
	printf("\nConjunto de solucoes:");
	for (int i=0;i<dim;i++){
		printf("\nx[%d]= %10.4f",(i+1),solucao[i]);
	}
}

void pivota() {
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
    printf("\n\nMatriz triangular superior do sistema: ");
	imp_matrix();
	back_subst();
	printf("\nConjunto de solucoes:");
	ordena_solucoes();
	for (int i=0;i<dim;i++){
		printf("\nx[%d]= %10.4f",(i+1),solucao[i]);
	}
}

void jordan() {
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
    printf("\n\nMatriz diagonal do sistema: ");
	imp_matrix();
	back_subst();
	printf("\nConjunto de solucoes:");
	for (int i=0;i<dim;i++){
		printf("\nx[%d]= %10.4f",(i+1),solucao[i]);
	}
}

void seidel() {
	printf("\n\nEntre com a tolerancia: ");
	scanf("%f",&tole);
	printf("Numero maximo de iteracoes: ");
	scanf("%d",&i_max);
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
				if (i<j) {
					x[k+1][i]=x[k+1][i]-(matrix[i][j]*x[k][j]);
				}
				else {
					if (i != j) {
						x[k+1][i]=x[k+1][i]-(matrix[i][j]*x[k+1][j]);
					}
				}
			}
			x[k+1][i]=x[k+1][i]/matrix[i][i];
		}
		erro=testa_erro(k,tole);
		k++;
	} while (erro && k<i_max);
	printf("\nForam realizadas %d iteracoes.",(k-1));
	if (k >= i_max) { printf("\n\nERRO: O sistema nao convergiu! :~("); }
	else {
		printf("\nConjunto de solucoes:");
		for (int i=0;i<dim;i++){
			printf("\nx[%d]= %10.4f",(i+1),x[k][i]);
		}
	}
}

void troca_linha(int l1, int l2){
	float aux[mtx+1];
	for (int i=0;i<mtx+1;i++) {
		aux[i]=matrix[l1][i];
		matrix[l1][i]=matrix[l2][i];
		matrix[l2][i]=aux[i];
	}
}

void jacobi() {
	printf("\n\nEntre com a tolerancia: ");
	scanf("%f",&tole);
	printf("Numero maximo de iteracoes: ");
	scanf("%d",&i_max);
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
	if (k >= i_max) { printf("\n\nERRO: O sistema nao convergiu! :~("); }
	else {
		printf("\nConjunto de solucoes:");
		for (int i=0;i<dim;i++){
			printf("\nx[%d]= %10.4f",(i+1),x[k][i]);
		}
	}
}


void imp_matrix() {
	printf("\n");
	for (int i=0;i<dim;i++){
		for(int j=0;j<=dim;j++) {
			printf("%10.4f",matrix[i][j]);
		}
		printf("\n");
	}
}

void le_matrix() {
	printf("\nEntre com a dimensao do sistema:");
	scanf("%i",&dim);
	for(int i=0;i<dim;i++){
		for(int j=0;j<=dim;j++){
			if (j==dim) { printf("Entre com o termo independente da %ia equacao: ",(i+1)); }
			else { printf("Entre com a %ia variavel da %ia equacao: ",(j+1),(i+1)); }
			scanf("%f",&matrix[i][j]);
		}
	}
	printf("\nSistema fornecido:");
	imp_matrix();
}

int testa_matrix(){
	int ldz,cdz;
	for (int i=0;i<dim;i++) {
		ldz=0;
		for (int j=0;j<=dim;j++) {
			if (matrix[i][j] != 0) { ldz=1; }
		}
		if (ldz == 0) { break; }
	}
	for (int i=0;i<dim;i++) {
		cdz=0;
		for (int j=0;j<dim;j++) {
			if (matrix[j][i] != 0) { cdz=1; }
		}
		if (cdz == 0) { break; }
	}
	return (cdz && ldz);
}

void back_subst() {
	for(int i=dim-1;i>=0;i=i-1) {
		solucao[i]=matrix[i][dim];
		for (int j=i+1;j<dim;j++) {
			solucao[i]=solucao[i]-(matrix[i][j]*solucao[j]);
		}
		solucao[i]=solucao[i]/matrix[i][i];
	}
}

void zero_maquina() {
	float zero_da_maquina=1, teste;
	do {
		zero_da_maquina=zero_da_maquina/2;
		teste=1+zero_da_maquina;
	} while (teste > 1);
	zero=zero_da_maquina;
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

