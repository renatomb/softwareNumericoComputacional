#include <string.h>
#include <iostream.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

void dec2bin();
void bin2dec();

void main() {
	for(;;) {
		int opcao;
		printf("\n\nConversao de bases\n---------------------------------------------\n\n1 - Decimal para binario\n2 - Binario para decimal\n3 - Sair do sistema\n\nSelecione a opcao desejada: ");
		opcao=getche();
		switch(opcao){
			case '1':dec2bin();break;
			case '2':bin2dec();break;
			case '3':return;
		}
		printf("\nPressione qualquer recla para voltar ao menu inicial.");
		getch();
	}
}

void dec2bin() {
	float num,p_fra;
	int p_int;
	printf("\nEntre com o numero o qual vc deseja converter para binario: ");
	scanf("%f",&num);
	if (num < 0) { printf("-"); num=num*(-1); }
	p_int=abs(num);
	p_fra=num-p_int;
	{ // Inicio do processamento da parte inteira.
		int cont=-1,q;
		char v[20];
		for (int i=0;i<20;i++) { v[i]='\0'; }
		do {
			q=p_int/2;
			if (p_int != 0) {
				cont++;
				switch(p_int%2){
					case 0:v[cont]='0';break;
					case 1:v[cont]='1';break;
				}
			}
			p_int=q;
		} while(q!=0 && cont<20);
		cont++;
		strrev(v);
		for (int i=cont;i<20;i++) { v[i]='\0'; }
		if (strlen(v) == 0) { printf("0"); }
		for (int i=0;i<cont;i++) { printf("%c",v[i]); }
		printf(".");
	} // Fim do processamento da parte inteira.
	{ // Inicio do processamento da parte fracionaria
		int v[20];
		for (int i=0;i<20;i++) { v[i]='\0'; }
		int cont=0;
		do {
			p_fra=p_fra*2;
			if (p_fra >= 1) {
				v[cont]=1;
				p_fra=p_fra-1;
			}
			else {
				v[cont]=0;
			}
			cont++;
		} while (p_fra !=0 && cont<20);
		for (int i=0;i<cont;i++) { printf("%d",v[i]); }
	} // Fim do processamento da parte fracionaria.
}

void bin2dec() {
	int numero[40],virgula=1,posv=41,cont;
	for (int i=0; i<40; i++) { numero[i]='\0'; }
	int testebyte(int acv,char chr);
	printf("\nEntre com o numero binario (max: 40 caracteres):");
	for (int i=0;i<40;i++) {
		char byte;
		int valida;
		do {
			byte=getch();
			valida=testebyte(virgula,byte);
		} while (!valida);
		if (valida == 2) { virgula = 0; }
		if (valida == 3) {
			if (posv == 41) { posv=i; }
		    break;
		}
		switch (byte) {
			case '1':numero[i]=1;break;
			case '0':numero[i]=0;break;
			case ',':numero[i]=2;posv=i;break;
			case '.':numero[i]=2;posv=i;break;
		}
		printf("%c",byte);
	}
	float decimal=0;
	cont=posv;
	for (int i=0; i<posv; i++){
		cont=cont-1;
		decimal=decimal+(numero[i]*(pow(2,cont)));
	}
	posv++;
	cont=0;
	for (int i=posv; i<40; i++) {
		cont=cont-1;
		decimal=decimal+(numero[i]*(pow(2,cont)));
	}
	printf("\nO numero fornecido, em notacao decimal, eh: %f",decimal);
}

int testebyte(int acv,char chr) {
	if (chr == '1' || chr == '0') { return 1; }
	else {
		if ((chr == ',' || chr == '.') && acv == 1) { return 2; }
		else {
			if (chr == 13) { return 3; }
			else { return 0; }
		}
	}
}
