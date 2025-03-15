//Boc Mario-Adrian -> folosim B si A -> Baterie
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct StructuraBaterie {
	int mAh;
	float pret;
	char* producator;
	char initalaCuloare;
};
typedef struct StructuraBaterie Baterie;

Baterie initializare_tastatura()
{
	Baterie nou;
	printf("mAh = ");
	scanf("%d", &nou.mAh);
	printf("pret = ");
	scanf("%f", &nou.pret);
	char buffer[100];
	printf("producator = ");
	scanf("%s", &buffer);
	nou.producator = (char*)malloc(strlen(buffer) + 1);
	strcpy_s(nou.producator, strlen(buffer) + 1, buffer);
	getchar();
	printf("initialaCuloare = ");
	scanf("%c", &nou.initalaCuloare);

	return nou;
}



int main()
{
	Baterie b1;
	b1 = initializare_tastatura();
	return 0;
}