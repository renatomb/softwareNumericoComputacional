#include <iostream.h>
#include <math.h>
#include <conio.h>
#define t_max 300

void le_dados();
void resolve_sel();
void print_sistema();
float base(int indice,float x);
float px(float x);

int m, grau;
float x[t_max],fx[t_max],a[t_max][t_max+1],c[t_max],pmax,pmin;

void main(){
	printf("Interpolacao de Lagrange");
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
			a[r][grau]=a[r][grau]+fx[i]*base(r,x[i]);
		}
	}
	resolve_sel();
	printf("\nPolinomio interpolador:\n\nfaj(x)=");
	for (int i=0; i<grau; i++) {
		printf("%f pow(x,%d)",c[i],i);
		if (i<grau-1 && c[i+1]>0) { printf("+"); }
	}
	printf("\n\nInforme os ponto para os quais voce deseja calcular os valores aproximados:");
	for(;;){
		float z;
		printf("\nx=");
		scanf("%f",&z);
		if (z>pmax || z<pmin) { printf("Nao eh possivel calcular esse ponto pois eh um caso de EXTRAPOLACAO!"); }
		else { printf("\np(%f)=%f",z,px(z)); }
		char tcl;
		printf("\n\nTecle 'S' caso voce deseje calcular outro ponto usando a mesma funcao: ");
		tcl=getche();
		if (tcl != 'S' && tcl != 's') { return; }
	}
}

void resolve_sel() {// Implementacao de Jordan para resolucao do SEL:
	for(int i=0;i<grau;i++) {
		if (a[i][i] != 1) {
			float aux=0;
			for(int j=0;j<=grau;j++) {
				if (aux==0) { aux=a[i][i]; }
				a[i][j]=a[i][j]/aux;
			}
		}
		for (int k=0;k<grau;k++) {
				if (k == i) {
				k=k+1;
				if (k >= grau) { break; }
			}
			float aux2;
			aux2=a[k][i];
			for (int j=0;j<=grau;j++) { a[k][j]=a[k][j]-(aux2*a[i][j]); }
		}
	}
	for (int i=0;i<grau;i++) { c[i]=a[i][grau]; }
}

void le_dados() {
	printf("\nDe quantos pontos voce dispoe para realizar a interpolacao? ");
	scanf("%d",&m);
	grau=m;
	printf("\nPor favor forneça os valores para os pares ordenados: ");
	for (int i=0;i<m;i++) {
		printf("\nx[%d]=",(i+1));
		scanf("%f",&x[i]);
		printf("f(x[%d])=",(i+1));
		scanf("%f",&fx[i]);
		if (i==0) { pmax=x[i]; pmin=x[i]; }
		if (x[i] > pmax) { pmax=x[i]; }
		if (x[i] < pmin) { pmin=x[i]; }
	}
}

float base(int indice,float x) {
	return pow(x,indice);
}

float px(float x) {
	float y=0;
    for (int i=0; i<grau; i++) {
		y=y+c[i]*pow(x,i);
	}
	return y;
}
