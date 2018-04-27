#include <iostream.h>
#include <math.h>
#include <conio.h>
#define t_max 300

void correlacao();
void le_dados();
void resolve_sel();
void print_sistema(char c1);
float base(int indice,float x, int metodo);
float faj(float x, int metodo);

int m,inf_w=0,grau=1;
float x[t_max],fx[t_max],w[t_max],a[t_max][t_max+1],c[t_max];

void linear();
void expone();
void logari();
void potenc();

void main() {
	int dados=0;
	for(;;) {
		printf("\n\nAjuste de Curvas\n---------------------------------\n\n1 - Ajuste linear\n2 - Ajuste exponencial\n3 - Ajuste Logaritmico\n4 - Ajuste de Potencia\n5 - Sair\n\nSelecione o metodo a ser usado: ");
		char opcao;
		opcao=getche();
		if (!dados && opcao != '5') { le_dados(); dados=1; }
		switch(opcao) {
			case '1':
				linear();
				break;
			case '2':
				expone();
				break;
			case '3':
				logari();
				break;
			case '4':
				potenc();
				break;
			case '5':
				return;
			default:
				printf("\nOpcao invalida! Selecione o metodo desejado: ");
		}
		printf("\n\nTecle 'S' caso deseje utilizar os mesmos dados para resolver por outro metodo.");
		opcao=getche();
		if (opcao != 's' && opcao != 'S') { dados=0; }
	}
}


void linear() {
	printf("\n\nAjuste de curvas - Metodo de ajuste linear\n\n");
	printf("Entre com o grau da funcao que voce deseja ajustar? ");
	scanf("%d",&grau);
	grau++;
	for (int r=0; r<grau; r++) {
		for (int s=0; s<grau; s++) {
			a[r][s]=0;
			if (r == s) {
				for (int i=0;i<m;i++) {
					a[r][r]=a[r][r]+base(r,x[i],1)*base(r,x[i],1);
				}
			}
			else {
				for (int i=0;i<m;i++) {
					a[r][s]=a[r][s]+base(r,x[i],1)*base(s,x[i],1);
				}
			}
		}
		a[r][grau]=0;
		for (int i=0;i<m;i++) {
			a[r][grau]=a[r][grau]+w[i]*fx[i]*base(r,x[i],1);
		}
	}
	print_sistema('c');
	resolve_sel();
	printf("\nFuncao de ajuste:\n\nfaj(x)=");
	for (int i=0; i<grau; i++) {
		printf("%f pow(x,%d)",c[i],i);
		if (i<grau-1 && c[i+1]>0) { printf("+"); }
	}
	correlacao(1);
}

void expone() {
	printf("\n\nAjuste de curvas - Metodo de ajuste exponencial\n\n");
	grau=2;
	for (int r=0; r<grau; r++) {
		for (int s=0; s<grau; s++) {
			a[r][s]=0;
			if (r == s) {
				for (int i=0;i<m;i++) {
					a[r][r]=a[r][r]+base(r,x[i],1)*base(r,x[i],1);
				}
			}
			else {
				for (int i=0;i<m;i++) {
					a[r][s]=a[r][s]+base(r,x[i],1)*base(s,x[i],1);
				}
			}
		}
		a[r][grau]=0;
		for (int i=0;i<m;i++) {
			a[r][grau]=a[r][grau]+w[i]*log(fx[i])*base(r,x[i],1);
		}
	}
	print_sistema('k');
	resolve_sel();
	c[0]=exp(c[0]);
	printf("\nFuncao de ajuste:\n\nfaj(x)=%6.4f*exp(%6.4fx)",c[0],c[1]);
	correlacao(2);
}

void logari() {
	printf("Ajuste de curvas - Metodo de ajuste logaritmico\n\n");
	grau=2;
	for (int r=0; r<grau; r++) {
		for (int s=0; s<grau; s++) {
			a[r][s]=0;
			if (r == s) {
				for (int i=0;i<m;i++) {
					a[r][r]=a[r][r]+base(r,x[i],2)*base(r,x[i],2);
				}
			}
			else {
				for (int i=0;i<m;i++) {
					a[r][s]=a[r][s]+base(r,x[i],2)*base(s,x[i],2);
				}
			}
		}
		a[r][grau]=0;
		for (int i=0;i<m;i++) {
			a[r][grau]=a[r][grau]+w[i]*fx[i]*base(r,x[i],2);
		}
	}
	print_sistema('c');
	resolve_sel();
	printf("\nFuncao de ajuste:\n\nfaj(x)=%6.4f+%6.4fln(x)",c[0],c[1]);
	correlacao(3);
}

void potenc() {
	printf("Ajuste de curvas - Metodo de ajuste de potencia\n\n");
	grau=2;
	for (int r=0; r<grau; r++) {
		for (int s=0; s<grau; s++) {
			a[r][s]=0;
			if (r == s) {
				for (int i=0;i<m;i++) {
					a[r][r]=a[r][r]+base(r,x[i],2)*base(r,x[i],2);
				}
			}
			else {
				for (int i=0;i<m;i++) {
					a[r][s]=a[r][s]+base(r,x[i],2)*base(s,x[i],2);
				}
			}
		}
		a[r][grau]=0;
		for (int i=0;i<m;i++) {
			a[r][grau]=a[r][grau]+w[i]*log(fx[i])*base(r,x[i],2);
		}
	}
	print_sistema('k');
	resolve_sel();
	c[0]=exp(c[0]);
	printf("\nFuncao de ajuste:\n\nfaj(x)=%6.4f*pow(x,%6.4f)",c[0],c[1]);
	correlacao(4);
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
	printf("\n\nDe quantos pontos [x, f(x)] voce dispoe para realizar o ajuste? ");
	scanf("%d",&m);
	printf("Tecle 'S' caso deseje fornecer os pesos. Qualquer outra tecla para pesos = 1: ");
	char tcl;
	tcl=getche();
	if (tcl == 'S' || tcl == 's') { inf_w=1; }
	else { printf("\nAssumindo todos os pesos = 1.\n"); }
	printf("\nPor favor forneça os valores para os pares ordenados: ");
	for (int i=0;i<m;i++) {
		printf("\nx[%d]=",(i+1));
		scanf("%f",&x[i]);
		printf("f(x[%d])=",(i+1));
		scanf("%f",&fx[i]);
		if (inf_w) {
			printf("w[%d])=",(i+1));
			scanf("%f",&w[i]);
		}
		else {
			w[i]=1;
		}
	}
	grau++;
}

void correlacao(int metodo) {
	float rsup=0,sfxi=0,sfxi2=0,r=0;
	if (metodo == 1 || metodo == 3) {
		for (int i=0;i<m;i++) {
			rsup=rsup+pow((fx[i]-faj(x[i],metodo)),2);
			sfxi=sfxi+fx[i];
			sfxi2=sfxi2+pow(fx[i],2);
		}
	}
	else {
		for (int i=0;i<m;i++) {
			rsup=rsup+pow((log(fx[i])-log(faj(x[i],metodo))),2);
			sfxi=sfxi+log(fx[i]);
			sfxi2=sfxi2+pow(log(fx[i]),2);
		}
	}
	r=sqrt(1-(rsup/(sfxi2-(pow(sfxi,2)/m))));
	printf("\n\n\nCoeficiente de correlacao r=%10.4f",r);
}

void print_sistema(char c1) {
	printf("\nSistema de equacoes: \n\n");
	for (int i=0;i<grau;i++){
		for(int j=0;j<=grau;j++) {
			if (j < grau) {
				printf("%10.4f ",a[i][j]);
				if (j == 0) { printf("%c1",c1); }
				else { printf("c%d",j+1); }
				if (j < grau-1) { printf("+"); }
			}
			else { printf("= %10.4f\n",a[i][j]); }
		}
	}
}

float base(int indice,float x, int metodo) {
	if (metodo == 1) { return pow(x,indice); }
	else { return pow(log(x),indice); }
}

float faj(float x, int metodo) {
	float y=0;
	switch(metodo){
		case 1:
		    for (int i=0; i<grau; i++) y=y+c[i]*pow(x,i);
			break;
		case 2:
			y=c[0]*exp(c[1]*x);
			break;
		case 3:
			y=c[0]+c[1]*log(x);
			break;
		case 4:
			y=c[0]*pow(x,c[1]);
			break;
	}
	return y;
}

