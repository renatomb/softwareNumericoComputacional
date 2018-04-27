float matrix[mtx][mtx+1],solucao[mtx], zero;
int dim;
void troca_linha(int l1, int l2);
void imp_matrix();
void le_matrix();
void back_subst();
void zero_maquina();
int testa_matrix();

void troca_linha(int l1, int l2){
	float aux[mtx+1];
	for (int i=0;i<mtx+1;i++) {
		aux[i]=matrix[l1][i];
		matrix[l1][i]=matrix[l2][i];
		matrix[l2][i]=aux[i];
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
