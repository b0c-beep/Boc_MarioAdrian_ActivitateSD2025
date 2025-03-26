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

struct Nod
{
	Masina info;
	struct Nod* next;
	struct Nod* prev;
};
typedef struct Nod Nod;

struct ListaDubla
{
	Nod* inceput;
	Nod* final;
};
typedef struct ListaDubla Lista;

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

void afisareListaMasiniDeLaInceput(Lista list) {
	Nod* nod = list.inceput;
	while (nod)
	{
		afisareMasina(nod->info);
		nod = nod->next;
	}
}

void afisareListaMasiniDeLaFinal(Lista list) {
	Nod* nod = list.final;
	while (nod)
	{
		afisareMasina(nod->info);
		nod = nod->prev;
	}
}

void adaugaMasinaInLista(Lista* list, Masina masinaNoua) {
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod->info = masinaNoua;
	nod->next = NULL;
	nod->prev = list->final;

	if (list->final != NULL)
	{
		list->final->next = nod;
	}
	else {
		list->inceput = nod;
	}
	list->final = nod;
}

void adaugaLaInceputInLista(Lista* list, Masina masinaNoua) {
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod->info = masinaNoua;
	nod->next = list->inceput;
	nod->prev = NULL;
	
	if (list->inceput)
	{
		list->inceput->prev = nod;
	}
	else {
		list->final = nod;
	}
	list->inceput = nod;

}

Lista citireLDMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Lista ld;
	ld.inceput = NULL;
	ld.final = NULL;

	while (!feof(f))
	{
		Masina masina = citireMasinaDinFisier(f);
		adaugaMasinaInLista(&ld, masina);
	}

	fclose(f);
	return ld;
}

void dezalocareLDMasini(Lista* ld){
	while (ld->inceput)
	{
		if (ld->inceput->info.numeSofer)
		{
			free(ld->inceput->info.numeSofer);
		}
		if (ld->inceput->info.model)
		{
			free(ld->inceput->info.model);
		}
		Nod* p = ld->inceput;
		ld->inceput = p->next;
		free(p);
	}
	ld->final = NULL;
}

float calculeazaPretMediu(Lista ld) {
	float suma = 0;
	int k = 0;
	Nod* nod = ld.inceput;
	while (nod)
	{
		suma += nod->info.pret;
		k++;
		nod = nod->next;
	}
	return k > 0 ? suma / k : 0;
}

void stergeMasinaDupaID(Lista* ld, int id) {
	Nod* nod = ld->inceput;
	while (nod && nod->info.id != id)
	{
		nod = nod->next;
	}
	if (nod)
	{
		if (nod->prev)
		{
			nod->prev->next = nod->next;
			if (nod->next)
			{
				nod->next->prev = nod->prev;
			}
			else
			{
				ld->final = nod->prev;
			}
		}
		else
		{
			ld->inceput = nod->next;
			if (nod->next)
			{
				nod->next->prev = NULL;
			}
			else
			{
				ld->final = NULL;
			}
		}
		free(nod->info.model);
		free(nod->info.numeSofer);
		free(nod);
	}
}

char* getNumeSoferMasinaScumpa(Lista ld) {
	Nod* nod = ld.inceput;
	Nod* maxPretMasina = nod;
	if (ld.inceput) {
		while (nod)
		{
			if (nod->info.pret > maxPretMasina->info.pret)
			{
				maxPretMasina = nod;
			}
			nod = nod->next;
		}

		char* nume = (char*)malloc(strlen(maxPretMasina->info.numeSofer) + 1);
		strcpy_s(nume, strlen(maxPretMasina->info.numeSofer) + 1, maxPretMasina->info.numeSofer);
		return nume;
	}
	return NULL;
}

int main() {
	Lista ld;
	ld = citireLDMasiniDinFisier("masini.txt");
	afisareListaMasiniDeLaInceput(ld);
	printf("\n\n");
	afisareListaMasiniDeLaFinal(ld);
	printf("\n\n");

	float pretMediu = calculeazaPretMediu(ld);
	printf("%.2f\n", pretMediu);

	stergeMasinaDupaID(&ld, 5);
	afisareListaMasiniDeLaInceput(ld);

	char* nume = getNumeSoferMasinaScumpa(ld);
	printf("%s\n\n", nume);
	free(nume);

	dezalocareLDMasini(&ld);
	return 0;
}