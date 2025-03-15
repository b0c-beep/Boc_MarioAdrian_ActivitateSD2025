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

void afisare_obiect(Baterie b)
{
	printf("\nmAh = %d\n", b.mAh);
	printf("pret = %.2f\n", b.pret);
	printf("producator = %s\n", b.producator);
	printf("initialaCuloare = %c\n", b.initalaCuloare);
}

float calculPretMAH(Baterie b)
{
	return (float)(b.pret / b.mAh);
}

void modificare_producator(Baterie* b, const char* producator)
{
	if (producator != NULL)
	{
		(*b).producator = (char*)malloc(strlen(producator) + 1);
		strcpy_s((*b).producator, strlen(producator) + 1, producator);
	}
	else
	{
		printf("Parametru invalid");
	}
}

int main()
{
	Baterie b1;
	b1 = initializare_tastatura();
	afisare_obiect(b1);
	float pretPerMAH = calculPretMAH(b1);
	printf("\n%.5f\n", pretPerMAH);
	modificare_producator(&b1, "Anker2");
	afisare_obiect(b1);
	return 0;
}