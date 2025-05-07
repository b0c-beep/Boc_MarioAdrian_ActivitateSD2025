#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

struct Nod {
	Masina info;
	struct Nod* st;
	struct Nod* dr;
	int gradEchilibru;
};
typedef struct Nod Nod;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

//ALTE FUNCTII NECESARE:
// - aici veti adauga noile functii de care aveti nevoie.

void rotireStanga(Nod** arbore)
{
	Nod* aux = (*arbore)->dr;
	(*arbore)->dr = aux->st;
	aux->st = (*arbore);
	(*arbore) = aux;

	(*arbore)->gradEchilibru--;
}

void rotireDreapta(Nod** arbore)
{
	Nod* aux = (*arbore)->st;
	(*arbore)->st = aux->dr;
	aux->dr = (*arbore);
	(*arbore) = aux;

	(*arbore)->gradEchilibru++;
}

void adaugaMasinaInArboreEchilibrat(Nod** radacina, Masina masinaNoua) {
	if (*radacina != NULL)
	{
		if ((*radacina)->info.id > masinaNoua.id)
		{
			adaugaMasinaInArboreEchilibrat(&((*radacina)->st), masinaNoua);
			(*radacina)->gradEchilibru++;
		}
		else 
		{
			adaugaMasinaInArboreEchilibrat(&((*radacina)->dr), masinaNoua);
			(*radacina)->gradEchilibru--;
		}
		
		if ((*radacina)->gradEchilibru == 2)
		{
			//dezechilibru in stanga
			if ((*radacina)->st->gradEchilibru == 1)
			{
				//situatie simpla - rotire la dreapta
				rotireDreapta(radacina);
			}
			else
			{
				//situatia complexa 
				rotireStanga(&((*radacina)->st));
				rotireDreapta(radacina);
			}
		}
		if ((*radacina)->gradEchilibru == -2)
		{
			//dezechilibru in dreapta
			if ((*radacina)->dr->gradEchilibru == 1)
			{
				//situatie complexa
				rotireDreapta(&((*radacina)->dr));
			}
			rotireStanga(radacina);
		}
	}
	else
	{
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = masinaNoua;
		nou->dr = NULL;
		nou->st = NULL;
		nou->gradEchilibru = 0;
		*radacina = nou;
	}
}

Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* radacina = NULL;

	while (!feof(f))
	{
		adaugaMasinaInArboreEchilibrat(&radacina, citireMasinaDinFisier(f));
	}

	fclose(f);
	return radacina;
}

void afisareMasiniDinArborePreOrdineRSD(Nod* arbore) {
	if (arbore)
	{
		afisareMasina(arbore->info);
		afisareMasiniDinArborePreOrdineRSD(arbore->st);
		afisareMasiniDinArborePreOrdineRSD(arbore->dr);
	}
}

void dezalocareArboreDeMasini(/*arbore de masini*/) {
	//sunt dezalocate toate masinile si arborele de elemente
}

//Preluati urmatoarele functii din laboratorul precedent.
//Acestea ar trebuie sa functioneze pe noul arbore echilibrat.

Masina getMasinaByID(/*arborele de masini*/int id);

int determinaNumarNoduri(/*arborele de masini*/);

float calculeazaPretTotal(/*arbore de masini*/);

float calculeazaPretulMasinilorUnuiSofer(/*arbore de masini*/ const char* numeSofer);

int main() {
	Nod* radacina = citireArboreDeMasiniDinFisier("masini.txt");
	afisareMasiniDinArborePreOrdineRSD(radacina);
	return 0;
}