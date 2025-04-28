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
	m1.pret= atof(strtok(NULL, sep));
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


void adaugaMasinaInArbore(Nod** arbore, Masina masinaNoua) {
	if (!(*arbore)) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = masinaNoua;
		nou->st = NULL;
		nou->dr = NULL;
		*arbore = nou;
	}
	else {
		if ((*arbore)->info.id > masinaNoua.id)
		{
			adaugaMasinaInArbore(&((*arbore)->st), masinaNoua);
		}
		else if ((*arbore)->info.id < masinaNoua.id)
		{
			adaugaMasinaInArbore(&((*arbore)->dr), masinaNoua);
		}
	}
}

Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* radacina = NULL;

	while (!feof(f))
	{
		adaugaMasinaInArbore(&radacina, citireMasinaDinFisier(f));
	}

	fclose(f);
	return radacina;
}

void afisareMasiniDinArbore(/*arbore de masini*/) {
	//afiseaza toate elemente de tip masina din arborele creat
	//prin apelarea functiei afisareMasina()
	//parcurgerea arborelui poate fi realizata in TREI moduri
	//folositi toate cele TREI moduri de parcurgere
}

void afisareMasiniDinArboreInOrdineSRD(Nod* arbore) {
	if (arbore)
	{
		afisareMasiniDinArboreInOrdineSRD(arbore->st);
		afisareMasina(arbore->info);
		afisareMasiniDinArboreInOrdineSRD(arbore->dr);
	}
}

void afisareMasiniDinArborePreOrdineRSD(Nod* arbore) {
	if (arbore)
	{
		afisareMasina(arbore->info);
		afisareMasiniDinArborePreOrdineRSD(arbore->st);
		afisareMasiniDinArborePreOrdineRSD(arbore->dr);
	}
}

void afisareMasiniDinArborePostOrdineSDR(Nod* arbore) {
	if (arbore)
	{
		afisareMasiniDinArborePostOrdineSDR(arbore->st);
		afisareMasiniDinArborePostOrdineSDR(arbore->dr);
		afisareMasina(arbore->info);
	}
}

//folosim postordine SDR
void dezalocareArboreDeMasini(Nod** arbore) {
	if (*arbore)
	{
		dezalocareArboreDeMasini(&((*arbore)->st));
		dezalocareArboreDeMasini(&((*arbore)->dr));
		free((*arbore)->info.numeSofer);
		free((*arbore)->info.model);
		free((*arbore));
		(*arbore) = NULL;
	}

}

Masina getMasinaByID(Nod* arbore, int id) {
	Masina m;
	m.id = -1;
	if (arbore)
	{
		if (arbore->info.id < id)
		{
			return getMasinaByID(arbore->dr, id);
		}
		else if (arbore->info.id > id)
		{
			return getMasinaByID(arbore->st, id);
		}
		else
		{
			m = arbore->info;
			return m;
		}
	}
	return m;
}

int determinaNumarNoduri(/*arborele de masini*/) {
	//calculeaza numarul total de noduri din arborele binar de cautare
	return 0;
}

int calculeazaInaltimeArbore(/*arbore de masini*/) {
	//calculeaza inaltimea arborelui care este data de 
	//lungimea maxima de la radacina pana la cel mai indepartat nod frunza
	return 0;
}

float calculeazaPretTotal(Nod* arbore) {
	if (arbore == NULL)
		return 0;

	float totalStanga = calculeazaPretTotal(arbore->st);
	float totalDreapta = calculeazaPretTotal(arbore->dr);
	return arbore->info.pret + totalStanga + totalDreapta;
}

float calculeazaPretulMasinilorUnuiSofer(/*arbore de masini*/ const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	return 0;
}

int main() {
	Nod* radacina = NULL;
	radacina = citireArboreDeMasiniDinFisier("masini-arbore.txt");
	printf("Afisare in ordine:\n");
	afisareMasiniDinArboreInOrdineSRD(radacina);
	printf("\n\nAfisare in pre ordine:\n");
	afisareMasiniDinArborePreOrdineRSD(radacina);
	printf("\n\nAfisare in post ordine:\n");
	afisareMasiniDinArborePostOrdineSDR(radacina);
	printf("\n\n");
	Masina m = getMasinaByID(radacina, 6);
	printf("Masina cautata:\n");
	afisareMasina(m);
	printf("\n\n");
	float pretTotal = calculeazaPretTotal(radacina);
	printf("Pret Total: %.2f\n\n", pretTotal);
	dezalocareArboreDeMasini(&radacina);
	return 0;
}