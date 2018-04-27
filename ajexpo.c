void executa() {
	printf("Ajuste de curvas - Metodo de ajuste exponencial\n\n");
	le_dados();
	for (int r=0; r<grau; r++) {
		for (int s=0; s<grau; s++) {
			a[r][s]=0;
			if (r == s) {
				for (int i=0;i<m;i++) {
					a[r][r]=a[r][r]+base(r,x[i])*base(r,x[i]);
				}
			}
			else {
				for (int i=0;i<m;i++) {
					a[r][s]=a[r][s]+base(r,x[i])*base(s,x[i]);
				}
			}
		}
		a[r][grau]=0;
		for (int i=0;i<m;i++) {
			a[r][grau]=a[r][grau]+w[i]*log(fx[i])*base(r,x[i]);
		}
	}
	print_sistema('k');
	resolve_sel();
	c[0]=exp(c[0]);
	print_faj();
	correlacao_exp();
}

float base(int indice,float x) {
	return pow(x,indice);
}

void print_faj() {
	printf("\nFuncao de ajuste:\n\nfaj(x)=%6.4f*exp(%6.4fx)",c[0],c[1]);
}

float faj(float x) {
	return c[0]*exp(c[1]*x);
}

