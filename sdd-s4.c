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

void afisareListaMasini(Nod* nod) {
	while (nod)
	{
		afisareMasina(nod->info);
		nod = nod->next;
	}
}

void adaugaMasinaInLista(Nod** nod, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = NULL;

	if (*nod != NULL)
	{
		Nod* aux = (*nod);
		while (aux->next != NULL)
		{
			aux = aux->next;
		}
		aux->next = nou;
	}
	else 
	{
		(*nod) = nou;
	}
}

void adaugaLaInceputInLista(/*lista de masini*/ Masina masinaNoua) {
	//adauga la inceputul listei o noua masina pe care o primim ca parametru
}

Nod* citireListaMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* lista = NULL;

	while (!feof(f))
	{
		Masina m = citireMasinaDinFisier(f);
		adaugaMasinaInLista(&lista, m);
	}

	fclose(f);

	return lista;
}

void dezalocareListaMasini(Nod** lista) {
	while ((*lista))
	{
		Nod* aux = (*lista);
		free(aux->info.model);
		free(aux->info.numeSofer);
		(*lista) = (*lista)->next;
		free(aux);
	}
}

float calculeazaPretMediu(Nod* lista) {
	int k = 0;
	float suma = 0;

	while (lista)
	{
		k++;
		suma += lista->info.pret;
		lista = lista->next;
	}

	return k == 0 ? 0 : (suma / k);
}

void stergeMasiniDinSeria(/*lista masini*/ char serieCautata) {
	//sterge toate masinile din lista care au seria primita ca parametru.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
}

float calculeazaPretulMasinilorUnuiSofer(/*lista masini*/ const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	return 0;
}

int main() {
	Nod* nod;
	nod = citireListaMasiniDinFisier("masini.txt");
	afisareListaMasini(nod);
	float medie = calculeazaPretMediu(nod);
	printf("Medie: %.2f\n", medie);



	dezalocareListaMasini(&nod);
	return 0;
}