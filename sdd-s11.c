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

struct Nod {
	Masina info;
	struct Nod* next;
};
typedef struct Nod Nod;

void pushStack(Nod** stiva, Masina masina) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masina; //shallow copy
	nou->next = (*stiva);
	(*stiva) = nou;
}

Masina popStack(Nod** stiva) {
	if ((*stiva) != NULL)
	{
		Masina m = (*stiva)->info;
		//strcpy_s(m.model, strlen((*stiva)->info.model) + 1, (*stiva)->info.model);
		//strcpy_s(m.numeSofer, strlen((*stiva)->info.numeSofer) + 1, (*stiva)->info.numeSofer);
		Nod* temp = *stiva;
		(*stiva) = temp->next;
		free(temp);
		return m;
	}
	return (Masina) { -1, 0, 0, NULL, NULL, '-' };
}

int emptyStack(/*stiva*/) {

}

Nod* citireStackMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* stiva = NULL;

	while (!feof(f))
	{
		pushStack(&stiva, citireMasinaDinFisier(f));
	}

	fclose(f);
	return stiva;
}

void afisareStack(Nod* stiva)
{
	Nod* p = stiva;
	while (p != NULL)
	{
		afisareMasina(p->info);
		p = p->next;
	}
}

void dezalocareStivaDeMasini(/*stiva*/) {
	//sunt dezalocate toate masinile si stiva de elemente
}

int size(/*stiva*/) {
	//returneaza numarul de elemente din stiva
}

//QUEUE
//Alegeti prin ce veti reprezenta coada si creati structura necesara acestei cozi
//putem reprezenta o coada prin LSI, LDI sau vector
void enqueue(/*coada*/ Masina masina) {
	//adauga o masina in coada
}

Masina dequeue(/*coada*/) {
	//extrage o masina din coada
}

void* citireCoadaDeMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
}

void dezalocareCoadaDeMasini(/*coada*/) {
	//sunt dezalocate toate masinile si coada de elemente
}


//metode de procesare
Masina getMasinaByID(/*stiva sau coada de masini*/int id);

float calculeazaPretTotal(/*stiva sau coada de masini*/);

int main() {
	Nod* stiva = citireStackMasiniDinFisier("masini.txt");
	afisareStack(stiva);
	popStack(&stiva);
	printf("\n\n\n");
	afisareStack(stiva);
	return 0;
}