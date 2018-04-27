#include <iostream.h>
#include <conio.h>
#include <math.h>
#define funcao x-cos(x)
#define f_string "x-cos(x)"

float f(float x);
float zero;

void main() {
	for(;;){
	printf("\n\nCalculo de raizes - Metodo da Bissecao\n\nEquacao inicial:\nf(x)=%s\n\n",f_string);
	float a,b,tole,xm, erro;
	int i_max, i=0;
	printf("Entre com o intervalo a-b:\nPonto a: ");
	scanf("%f",&a);
	printf("Ponto b: ");
	scanf("%f",&b);
	printf("Entre com a tolerancia desejada: ");
	scanf("%f",&tole);
	printf("Entre com o numero maximo de iteracoes: ");
	scanf("%d",&i_max);
	if (f(a) * f(b) > 0) { printf("A raiz nao esta no intervalo especificado, favor isolar as raizes!"); getch(); }
	else {
	do {
		xm=(a+b)/2;
		if (f(a)*f(xm) < zero) {
			b=xm;
		}
		else {
			a=xm;
		}
		erro=fabs(a-b);
		i++;
	} while(erro > tole && i < i_max);
	if (i == i_max) { printf("O sistema atingiu o limite de iterações! :~("); }
	else {
		printf("\n\n\nIteracoes realizadas: %d\nSolucao encontrada: %10.3f",i,xm);
	}
	}
	char tcl;
	printf("\nTecle 'S' caso deseje reiniciar o programa: ");
	tcl=getche();
	if (tcl != 's' && tcl != 'S') { return; }
	}
}

float f(float x) {
	return funcao;
}

void zero_maquina() {
	float zero_da_maquina=1, teste;
	do {
		zero_da_maquina=zero_da_maquina/2;
		teste=1+zero_da_maquina;
	} while (teste > 1);
	zero=zero_da_maquina;
}

