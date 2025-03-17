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
	printf("\n");
	return nou;
}

void afisare_obiect(Baterie b)
{
	printf("\nmAh = %d\n", b.mAh);
	printf("pret = %.2f\n", b.pret);
	printf("producator = %s\n", b.producator);
	printf("initialaCuloare = %c\n\n", b.initalaCuloare);
}

void afisare_vector(Baterie* vb, int numarObiecte)
{
	printf("\nAfisare vector:\n");
	for (int i = 0; i < numarObiecte; i++)
	{
		afisare_obiect(vb[i]);
	}
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
	Baterie b1, b2, b3, b4, b5;
	b1 = initializare_tastatura();
	b2 = initializare_tastatura();
	b3 = initializare_tastatura();
	b4 = initializare_tastatura();
	b5 = initializare_tastatura();

	int nrObiecte = 5;
	Baterie* vb = malloc(sizeof(Baterie) * nrObiecte);
	vb[0] = b1;
	vb[1] = b2;
	vb[2] = b3;
	vb[3] = b4;
	vb[4] = b5;
	afisare_vector(vb, nrObiecte);

	return 0;
}