#include <iostream.h>
#include <conio.h>
#include <string.h>
#include <math.h>

char equa[100];
float numeric[100];
int mypos=0;

void leparam(char *nome);
void adde(char t);
void addn();
void processa(char t);
void le_equa();
float calcula();

void main(){
	char valid[12];
	for (int i=0; i<100;i++) { equa[i]='\0'; numeric[i]=0; }
	strcpy(valid,"-+*/lesct234vxf");
	for (;;) {
		if (mypos>95) { break; }
		printf("\n\nMontagem de equacoes:\n(C) 2002 - Renato MB\n");
		le_equa();
		printf("\n- = Subtracao         + = Adicao");
		printf("\n* = Multiplicacao     / = Divisao");
		printf("\nl = Ln                e = Exp");
		printf("\ns = Sen               c = Cos");
		printf("\nt = Tan               2 = Quadrado");
		printf("\n3 = Cubo              4 = Quarta potencia");
		printf("\nv = Valor numerico	x = Variavel x");
		printf("\nf = Finaliza edicao");
		printf("\nEscolha a operacao desejada para adicionar a equacao: ");
		char t;
		do {
			t=getch();
		} while (!strchr(valid,t));
		if (t == 'f') { break; }
		printf("%c",t);
		processa(t);
	}
	printf("\nEntre com valor de x para realizar o calculo: ");
	float x;
	scanf("%f",&x);
	calcula();
}

void processa(char t){
	switch(t){
		case '-':adde(t);break;
		case '+':adde(t);break;
		case '*':adde(t);break;
		case '/':adde(t);break;
		case 'x':adde(t);break;
		case 'l':adde(t);leparam("Logaritimo Natural");break;
		case 'e':adde(t);leparam("Exponencial");break;
		case 's':adde(t);leparam("Seno");break;
		case 'c':adde(t);leparam("Cosseno");break;
		case 't':adde(t);leparam("Tangente");break;
		case '2':adde(t);leparam("Quadrado");break;
		case '3':adde(t);leparam("Quadrado");break;
		case '4':adde(t);leparam("Elevado a quarta");break;
		case 'v':addn();break;
	}
}

void adde(char t) {
	equa[mypos]=t;
	mypos++;
}

void addn(){
	float val;
	printf("\nEntre com o valor numerico: ");
	scanf("%f",&val);
	numeric[mypos]=val;
	adde('v');
}

void leparam(char *nome){
	printf("\n%s adicionado, ",nome);
	char tclp;
	do{
		printf("\nn = Valor numerico      x = Variavel x\nSelecione o tipo de parametro: ");
		tclp=getch();
	}while (tclp != 'n' && tclp != 'x');
	printf("%c",tclp);
	switch(tclp) {
		case 'n':
			addn();
			break;
		case 'x':
			adde('x');
			break;
	}
}

void le_equa(){
	printf("\nSua equacao atual:");
	for (int i=0; i<mypos; i++) {
		if (strchr("+-/*x",equa[i])) { printf("%c",equa[i]); }
		else {
			switch(equa[i]) {
				case 'l':
					i++;
					printf("ln(%c)",equa[i]);
					break;
				case 's':
					i++;
					printf("sin(%c)",equa[i]);
					break;
				case 'c':
					i++;
					printf("cos(%c)",equa[i]);
					break;
				case 't':
					i++;
					printf("tan(%c)",equa[i]);
					break;
				case 'e':
					i++;
					printf("exp(%c)",equa[i]);
					break;
				case '2':
					i++;
					printf("quad(%c)",equa[i]);
					break;
				case '3':
					i++;
					printf("cubo(%c)",equa[i]);
					break;
				case '4':
					i++;
					printf("quar(%c)",equa[i]);
					break;
				case 'v':
					printf("%f",numeric[i]);
					break;
			}
		}
	}
}

float calcula() {
	float y;
	for (int i=0; i<mypos; i++) {
		if (strchr("+-/*x",equa[i])) { printf("%c",equa[i]); }
		else {
			switch(equa[i]) {
				case 'l':
					i++;
					printf("ln(%c)",equa[i]);
					break;
				case 's':
					i++;
					printf("sin(%c)",equa[i]);
					break;
				case 'c':
					i++;
					printf("cos(%c)",equa[i]);
					break;
				case 't':
					i++;
					printf("tan(%c)",equa[i]);
					break;
				case 'e':
					i++;
					printf("exp(%c)",equa[i]);
					break;
				case '2':
					i++;
					printf("quad(%c)",equa[i]);
					break;
				case '3':
					i++;
					printf("cubo(%c)",equa[i]);
					break;
				case '4':
					i++;
					printf("quar(%c)",equa[i]);
					break;
				case 'v':
					printf("%f",numeric[i]);
					break;
			}
		}
	}
	return y;
}
