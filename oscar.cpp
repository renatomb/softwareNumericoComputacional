#include <iostream.h>
#include <stdio.h> //Funcao printf
#include <iomanip.h>
#include <math.h>
#define int_max 38
#define tipo float

tipo funcao(tipo x){
	return 3*exp(x)+5*x-4;
}

tipo assimetrico(tipo x, tipo delta_x) {
	return (funcao(x+delta_x)-funcao(x))/delta_x;
}

tipo simetrico(tipo x, tipo delta_x) {
	return (funcao(x+delta_x)-funcao(x-delta_x))/(2*delta_x);
}

void otimiza_s(int po_s, tipo xzero) {
	int indice=1,cont=0;
	tipo erro[1000],alfa,j;
	erro[0]=0;
	do {
	cont=0;
	alfa=pow(10,-indice);
	for (j=9*alfa;;j=j-alfa) {
		cout << ".";
		cont++;
		printf("\n[%d,%f]=%10.7f (%10.7f) p/alfa=%10.7f",po_s,j,simetrico(xzero,pow(j*10,-po_s)),erro[cont],alfa);
		erro[cont]=fabs(simetrico(xzero,pow(j*10,-po_s))-simetrico(xzero,pow((j+alfa)*10,-po_s)));
		if (cont>1) {
			if (erro[cont] > erro [cont-1]) {
//				printf("%10.7f > %10.7f",erro[cont],erro[cont-1]);
				j=j+(1*alfa);
				cout << "<";
				erro[0]=erro[cont-1];
				alfa=pow(10,-indice);
				break;
//				j=j+alfa;
			}
//			else { printf("%10.7f < %10.7f",erro[cont],erro[cont-1]); }
		}
	}
	indice++;
	}while(indice<6);
	cout << "\nOtimizacao simetrica concluida, melhor delta_x encontrado: " << setprecision(15) << j << "x 10^-" << po_s;
	cout << "\nDerivada simetrica para o delta_x otimizado: " << setprecision(15) << simetrico(xzero,pow(j*10,-po_s));
}

void otimiza_a(int po_a, tipo xzero) {
	int indice=0,cont=0;
	tipo erro[1000],alfa;
	alfa=pow(10,-indice);
	erro[0]=0;
	for (tipo j=2*alfa;;j=j+alfa) {
		cout << ".";
		cont++;
//		printf("\n[%d,%f]=%10.7f (%10.7f) p/alfa=%10.7f",po_a,j,assimetrico(xzero,pow(j*10,-po_a)),erro[cont],alfa);
		erro[cont]=fabs(assimetrico(xzero,pow(j*10,-po_a))-assimetrico(xzero,pow((j-alfa)*10,-po_a)));
		if (cont>1) {
			if (erro[cont] > erro [cont-1]) {
//				printf("%10.7f > %10.7f",erro[cont],erro[cont-1]);
				j=j-(2*alfa);
				cout << "<";
				indice++;
				erro[0]=erro[cont-1];
				cont=0;
				if (indice>6) {
					break;
				}
				alfa=pow(10,-indice);
//				j=j+alfa;
			}
//			else { printf("%10.7f < %10.7f",erro[cont],erro[cont-1]); }
		}
	}
	cout << "\nOtimizacao assimetrica concluida, melhor delta_x encontrado: " << setprecision(15) << j << "x 10^-" << po_a;
	cout << "\nDerivada assimetrica para o delta_x otimizado: " << setprecision(15) << assimetrico(xzero,pow(j*10,-po_a));
}

void main(){
	tipo xzero,erro_s[int_max],erro_a[int_max];
	int po_a=0,po_s=0;
	cout << "UNP - Universidade Potiguar\n-----------------------------------------------\n\n\n";
	cout << "Entre com o valor para x0= ";
	cin >> xzero;
//	erro_s[0]=0;
	for(int i=0; i<=int_max;i++) { // ----- Busca do Ponto Otimo -----
		cout << ".";
		erro_a[i]=fabs(assimetrico(xzero,pow(10,-i))-assimetrico(xzero,pow(10,-(i-1))));
		erro_s[i]=fabs(simetrico(xzero,pow(10,-i))-simetrico(xzero,pow(10,-(i-1))));
//		printf("\nsim(%d)=%10.7f (%10.7f)",i,simetrico(xzero,pow(10,-i)),erro_s[i]);
//		printf("\nass(%d)=%10.7f",i,assimetrico(xzero,pow(10,-i)));
		if (i>1) {
			if((erro_s[i] > erro_s[i-1]) & (po_s == 0)) { po_s=i-1; }
			if((erro_a[i] > erro_a[i-1]) & (po_a == 0)) { po_a=i-1; }
			if (po_a && po_s) { break; }
		}
	}
	cout << "\nDelta_x para o ponto otimo simetrico: 10^-" << po_s;
	cout << "\nDerivada simetrica para o delta_x anterior: " << setprecision(15) << simetrico(xzero,pow(10,-po_s));
	cout << "\nDelta_x para o ponto otimo assimetrico: 10^-" << po_a;
	cout << "\nDerivada assimetrica para o delta_x anterior: " << setprecision(15) << assimetrico(xzero,pow(10,-po_a));
//	po_s=po_s-1;
//	po_a=po_a-1;
	cout << "\n------------------------------------------------------------------\n";
	otimiza_s(po_s,xzero);
	cout << "\n------------------------------------------------------------------\n";
	otimiza_a(po_a,xzero);
/*	float vant;
	vant=simetrico(xzero,pow(10,-po_s));
	for(;;){
		float dx;
		cout << "\nDelta x: ";
		cin >> dx;
		if (dx == 0) { break; }
		printf("\n%10.7f (%10.7f)",simetrico(xzero,dx),fabs(simetrico(xzero,dx)-vant));
		vant=simetrico(xzero,dx);
	}*/
/*	float alfa=0.000001,menorerro,erroat;
	int cont=0;
	for (float j=1+alfa;j<po_s;j=j+alfa) {
		erroat=fabs((9.9461638)-simetrico(xzero,pow(j*10,-po_s)));
		if ((cont == 0) || (menorerro > erroat)) {
			menorerro=erroat;
			cout << "***";
			cont++;
		}
		printf("\n[%d,%f]=%10.7f",po_s,j,simetrico(xzero,pow(j*10,-po_s)));
	}*/
}
