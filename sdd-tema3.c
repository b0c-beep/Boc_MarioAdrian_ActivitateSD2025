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
	if (vb != NULL)
	{
		printf("\nAfisare vector:");
		for (int i = 0; i < numarObiecte; i++)
		{
			afisare_obiect(vb[i]);
		}
	}
	else {
		printf("vector null\n");
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

Baterie* getVectorBateriiNegre(Baterie* vector, int nrObiecte, int* nrObiectVectorNou)
{
	*nrObiectVectorNou = 0;
	for (int i = 0; i < nrObiecte; i++)
	{
		if (vector[i].initalaCuloare == 'N' || vector[i].initalaCuloare == 'n')
		{
			(*nrObiectVectorNou)++;
		}
	}
	Baterie* nou = malloc(sizeof(Baterie) * (*nrObiectVectorNou));

	int k = 0;
	for (int i = 0; i < nrObiecte; i++)
	{
		if (vector[i].initalaCuloare == 'N' || vector[i].initalaCuloare == 'n')
		{
			nou[k].mAh = vector[i].mAh;
			nou[k].pret = vector[i].pret;
			nou[k].initalaCuloare = vector[i].initalaCuloare;
			if (vector[i].producator != NULL)
			{
				nou[k].producator = (char*)malloc(strlen(vector[i].producator) + 1);
				strcpy_s(nou[k].producator, strlen(vector[i].producator) + 1, vector[i].producator);
				k++;
			}
			else {
				nou[k].producator = NULL;
			}
		}
	}

	return nou;
}

void mutaBateriiCapacitateMare(Baterie** v1, int* nrObiecte1, Baterie** v2, int* nrObiecte2)
{
	int k = 0;
	for (int i = 0; i < (*nrObiecte1); i++)
	{
		if ((*v1)[i].mAh >= 10000)
		{
			k++;
		}
	}
	(*nrObiecte2) = k;
	*v2 = malloc(sizeof(Baterie) * (*nrObiecte2));
	Baterie* copie = malloc(sizeof(Baterie) * ((*nrObiecte1) - (*nrObiecte2)));

	k = 0;
	int j = 0;
	for (int i = 0; i < (*nrObiecte1); i++)
	{
		if ((*v1)[i].mAh >= 10000)
		{
			(*v2)[k].mAh = (*v1)[i].mAh;
			(*v2)[k].pret = (*v1)[i].pret;
			(*v2)[k].initalaCuloare = (*v1)[i].initalaCuloare;
			if ((*v1)[i].producator != NULL)
			{
				(*v2)[k].producator = (char*)malloc(strlen((*v1)[i].producator) + 1);
				strcpy_s((*v2)[k].producator, strlen((*v1)[i].producator) + 1, (*v1)[i].producator);
			}
			else
			{
				(*v2)[k].producator = NULL;
			}
			k++;
		}
		else
		{
			copie[j].mAh = (*v1)[i].mAh;
			copie[j].pret = (*v1)[i].pret;
			copie[j].initalaCuloare = (*v1)[i].initalaCuloare;
			if ((*v1)[i].producator != NULL)
			{
				copie[j].producator = (char*)malloc(strlen((*v1)[i].producator) + 1);
				strcpy_s(copie[j].producator, strlen((*v1)[i].producator) + 1, (*v1)[i].producator);
			}
			else {
				copie[j].producator = NULL;
			}
			j++;
		}
	}

	(*nrObiecte1) = j;
	*v1 = malloc(sizeof(Baterie) * (*nrObiecte1));

	for (int i = 0; i < (*nrObiecte1); i++)
	{
		(*v1)[i].mAh = copie[i].mAh;
		(*v1)[i].pret = copie[i].pret;
		(*v1)[i].initalaCuloare = copie[i].initalaCuloare;
		if (copie[i].producator != NULL)
		{
			(*v1)[i].producator = (char*)malloc(strlen(copie[i].producator) + 1);
			strcpy_s((*v1)[i].producator, strlen(copie[i].producator) + 1, copie[i].producator);
		}
		else
		{
			(*v1)[i].producator = NULL;
		}
	}

	free(copie);

}

Baterie* concatenare(Baterie* b1, int nrOb1, Baterie* b2, int nrOb2)
{
	Baterie* concat = malloc(sizeof(Baterie) * (nrOb1 + nrOb2));
	int k = 0;
	for (int i = 0; i < nrOb1; i++) {
		concat[k].mAh = b1[i].mAh;
		concat[k].pret = b1[i].pret;
		concat[k].initalaCuloare = b1[i].initalaCuloare;
		if (b1[i].producator != NULL)
		{
			concat[k].producator = (char*)malloc(strlen(b1[i].producator) + 1);
			strcpy_s(concat[k].producator, strlen(b1[i].producator) + 1, b1[i].producator);
		}
		else {
			concat[k].producator = NULL;
		}

		k++;
	}

	for (int i = 0; i < nrOb2; i++) {
		concat[k].mAh = b2[i].mAh;
		concat[k].pret = b2[i].pret;
		concat[k].initalaCuloare = b2[i].initalaCuloare;
		if (b2[i].producator != NULL)
		{
			concat[k].producator = (char*)malloc(strlen(b2[i].producator) + 1);
			strcpy_s(concat[k].producator, strlen(b2[i].producator) + 1, b2[i].producator);
		}
		else {
			concat[k].producator = NULL;
		}

		k++;
	}

	return concat;
}

void citireVectorDinFisier(const char* numeFisier, Baterie** baterii, int* nrObiecte)
{
	FILE* f = fopen(numeFisier, "r");
	int k = 0;
	while (!feof(f))
	{
		char buff[100];
		fgets(buff, 100, f);
		k++;
	}

	(*baterii) = malloc(sizeof(Baterie) * k);
	(*nrObiecte) = k;
	fseek(f, 0, SEEK_SET);

	k = 0;
	while (!feof(f))
	{
		char buffer[100];
		fgets(buffer, 100, f);
		char delim[4] = ",.\n";
		char* p = strtok(buffer, delim);
		(*baterii)[k].mAh = atoi(p);
		p = strtok(NULL, delim);
		(*baterii)[k].pret = atof(p);
		p = strtok(NULL, delim);
		(*baterii)[k].producator = (char*)malloc(strlen(p) + 1);
		strcpy_s((*baterii)[k].producator, strlen(p) + 1, p);
		p = strtok(NULL, delim);
		(*baterii)[k].initalaCuloare = p[0];
		free(p);
		p = NULL;
		k++;
	}

	fclose(f);
}

int main()
{
	Baterie* vector = NULL;
	int nr = 0;
	citireVectorDinFisier("baterii.txt", &vector, &nr);
	afisare_vector(vector, nr);
	return 0;
}