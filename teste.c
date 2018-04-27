#include <iostream.h>
#define mtx 30
#include <matrix.h>

void main() {
	int x, y;
	le_matrix();
	printf("\nDigite a primeira coluna: ");
	scanf("%d",&x);
	printf("\nDigite a segunda coluna: ");
	scanf("%d",&y);
	troca_coluna(x,y);
	imp_matrix();
}
