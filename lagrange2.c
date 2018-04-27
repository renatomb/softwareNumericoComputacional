#include <iostream.h>
#include <conio.h>
#define nmax 3000

float x[nmax],fx[nmax];
int n;

void main() {
	printf("\n\nInterpolacao de lagrange\n-------------------------------------------");
	int dados=0;
	float pmax,pmin;
	for(;;){
		if(!dados) {
			printf("\nQuantos pontos voce possui para realizar a interpolacao? ");
			dados=1;
			scanf("%d",&n);
			printf("\nInforme os valores para os pares [x,f(x)]");
			for (int i=0;i<n;i++){
				printf("\nx[%d]=",i+1);
				scanf("%f",&x[i]);
				printf("f(%d)=",i+1);
				scanf("%f",&fx[i]);
				if (i == 0) { pmax=x[i]; pmin=x[i]; }
				if (x[i] < pmin) { pmin=x[i]; }
				if (x[i] > pmax) { pmax=x[i]; }
			}
		}
		float z;
		printf("\nInforme o ponto para o qual voce deseja calcular o f(x) para x=");
		scanf("%f",&z);
		if (z > pmax || z < pmin) { printf("\nNao e' possivel interpolar f(%f) pois se trata de umca so de EXTRAPOLACAO!",z); }
		else {
			float px=0;
			for (int i=0;i<n;i++) {
				float produtorio=1;
				for (int j=0;j<n;j++) {
					if (j != i) { produtorio=produtorio*((z-x[j])/(x[i]-x[j])); }
				}
				px=px+(fx[i]*produtorio);
			}
			printf("\nO valor de f(%f)=%f",z,px);
		}
		char tcl;
		printf("\nTecle 'S' caso deseje reiniciar o programa: ");
		tcl=getche();
		if (tcl != 's' && tcl != 'S') { return; }
		printf("\nTecle 'S' caso deseje utilizar os mesmos pontos anteriores: ");
		tcl=getche();
		if (tcl != 's' && tcl != 'S') { dados=0; }
	}
}
