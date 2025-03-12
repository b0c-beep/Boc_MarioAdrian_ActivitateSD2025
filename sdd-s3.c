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

void afisareMasina(Masina masina) {
	printf("ID = %d\n", masina.id);
	printf("Numar usi = %d\n", masina.nrUsi);
	printf("Pret = %.2f\n", masina.pret);
	printf("Model = %s\n", masina.model);
	printf("Nume Sofer = %s\n", masina.numeSofer);
	printf("Serie = %c\n\n", masina.serie);
}

void afisareVectorMasini(Masina* masini, int nrMasini) {
	for (int i = 0; i < nrMasini; i++) {
		afisareMasina(masini[i]);
	}
}

void adaugaMasinaInVector(Masina** masini, int* nrMasini, Masina masinaNoua) {
	Masina* aux = (Masina*)malloc(sizeof(Masina) * ((*nrMasini) + 1));
	for (int i = 0; i < (*nrMasini); i++)
	{
		aux[i] = (*masini)[i];
	}
	aux[(*nrMasini)] = masinaNoua;
	free(*masini);
	(*masini) = aux;
	(*nrMasini) += 1;
}

Masina citireMasinaFisier(FILE* file) {
	Masina m;
	char buffer[100];
	char delim[4] = ",;\n";
	fgets(buffer, 100, file);
	char * aux = strtok(buffer, delim);
	m.id = atoi(aux);
	m.nrUsi = atoi(strtok(NULL, delim));
	m.pret = atof(strtok(NULL, delim));
	aux = strtok(NULL, delim);
	m.model = malloc(strlen(aux) + 1);
	strcpy_s(m.model, strlen(aux) + 1, aux);
	aux = strtok(NULL, delim);
	m.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m.numeSofer, strlen(aux) + 1, aux);
	aux = strtok(NULL, delim);
	m.serie = aux[0];

	return m;
}

Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
	FILE* f = fopen(numeFisier, "r");
	Masina* masini = NULL;
	while (!feof(f))
	{
		Masina m = citireMasinaFisier(f);
		adaugaMasinaInVector(&masini, nrMasiniCitite, m);
	}
	fclose(f);
	return masini;
}

void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
	
}

int main() {
	Masina* masini = NULL;
	int nrMasini = 0;
	masini = citireVectorMasiniFisier("masini.txt", &nrMasini);
	afisareVectorMasini(masini, nrMasini);

	return 0;
}