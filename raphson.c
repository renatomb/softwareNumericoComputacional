#include <iostream.h>
#include <conio.h>
#include <math.h>
#define funcao x-cos(x)
#define derivada 1+sin(x)
#define f_string "x-cos(x)"
#define d_string "1+sen(x)"
#define xmax 3000

float f(float x);
float fl(float x);
void zero_maquina();
float zero;

void main() {
	for(;;){
	printf("\n\nCalculo de raiz - Metodo de Newton-Raphson\n\nEquacao inicial:\nf(x)=%s\nf'(x)=%s\n\n",f_string,d_string);
	float tole,x[xmax], erro;
	int i_max, i=0;
	printf("Entre com um dos pontos:");
	scanf("%f",&x[0]);
	printf("Entre com a tolerancia desejada: ");
	scanf("%f",&tole);
	printf("Entre com o numero maximo de iteracoes: ");
	scanf("%d",&i_max);
	do {
		x[i+1]=x[i]-(f(x[i])/fl(x[i]));
		erro=fabs(x[i+1]-x[i]);
		i++;

	} while (i < i_max && erro > tole);
	if (i == i_max) { printf("O sistema atingiu o limite de iterações! :~("); }
	else {
		printf("\n\n\nIteracoes realizadas: %d\nSolucao encontrada: %10.3f",i,x[i]);
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

float fl(float x) {
	return derivada;
}

void zero_maquina() {
	float zero_da_maquina=1, teste;
	do {
		zero_da_maquina=zero_da_maquina/2;
		teste=1+zero_da_maquina;
	} while (teste > 1);
	zero=zero_da_maquina;
}


