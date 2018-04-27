void executa() {
	printf("Ajuste de curvas - Metodo de ajuste logaritmico\n\n");
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
			a[r][grau]=a[r][grau]+w[i]*fx[i]*base(r,x[i]);
		}
	}
	print_sistema('c');
	resolve_sel();
	printf("\nFuncao de ajuste:\n\nfaj(x)=%6.4f+%6.4fln(x)",c[0],c[1]);
	correlacao();
}

float base(int indice,float x) {
	return pow(log(x),indice);
}


