#include<stdio.h>
#include<malloc.h>

struct Masina {
	int id;
	int anFabricatie;
	char* sofer;
	float kilometriiParcursi;
	char initialaProducator;
};

struct Masina initializare(int id, int anFabricatie, const char* sofer, float kilometriiParcursi, char initialaProducator) {
	struct Masina m;
	m.id = id;
	m.anFabricatie = anFabricatie;
	m.sofer = (char*)malloc(strlen(sofer) + 1);
	strcpy_s(m.sofer, strlen(sofer) + 1, sofer);
	m.kilometriiParcursi = kilometriiParcursi;
	m.initialaProducator = initialaProducator;
	return m;
}

void afisare(struct Masina m) {
	printf("ID: %d \n", m.id);
	printf("An fabricatie: %d \n", m.anFabricatie);
	printf("Sofer: %s \n", m.sofer);
	printf("Kilometrii Parcursi : %f \n", m.kilometriiParcursi);
	printf("Initiala producator: %c \n\n", m.initialaProducator);
}

void afisareVector(struct Masina* vector, int nrElemente) {
	if (nrElemente > 0 && vector != NULL)
	{
		for (int i = 0; i < nrElemente; i++)
		{
			afisare(vector[i]);
		}
	}	
}

struct Masina* copiazaPrimeleNElemente(struct Masina* vector, int nrElemente, int nrElementeCopiate) {
	struct Masina* vectorNou = NULL;
	if (vector != NULL && nrElemente > 0 && nrElemente >= nrElementeCopiate && nrElementeCopiate > 0)
	{
		vectorNou = malloc(sizeof(struct Masina) * nrElementeCopiate);

		for (int i = 0; i < nrElementeCopiate; i++)
		{
			vectorNou[i] = initializare(vector[i].id, vector[i].anFabricatie, vector[i].sofer, vector[i].kilometriiParcursi, 
				vector[i].initialaProducator);
		}

		return vectorNou;
	}	
}

void dezalocare(struct Masina** vector, int* nrElemente) {
	if ((*vector) != NULL && (*nrElemente) > 0)
	{
		for (int i = 0; i < (*nrElemente); i++)
		{
			free((*vector)[i].sofer);
		}
		free(*vector);
		(*vector) = NULL;
		(*nrElemente) = 0;
	}
}

void copiazaAnumiteElemente(struct Masina* vector, char nrElemente, float prag, struct Masina** vectorNou, int* dimensiune) {
	//parametrul prag poate fi modificat in functie de 
	// tipul atributului ales pentru a indeplini o conditie
	//este creat un nou vector cu elementele care indeplinesc acea conditie
}

struct Masina getPrimulElementConditionat(struct Masina* vector, int nrElemente, const char* conditie) {
	//trebuie cautat elementul care indeplineste o conditie
	//dupa atributul de tip char*. Acesta este returnat.
	struct Masina s;
	s.id = 1;

	return s;
}
	


int main() {

	int nrElemente = 3;
	struct Masina* vector = malloc(sizeof(struct Masina) * nrElemente);
	vector[0] = initializare(1, 2010, "Marian", 2100, 'F');
	vector[1] = initializare(2, 2008, "Cristi", 3500.6, 'A');
	vector[2] = initializare(3, 2017, "Stefan", 750, 'M');

	/*for (int i = 0; i < nrElemente; i++)
	{
		afisare(vector[i]);
	}*/

	afisareVector(vector, nrElemente);

	printf("\nMasini copiate:\n");
	struct Masina* vectorNou = copiazaPrimeleNElemente(vector, nrElemente, nrElemente - 1);
	int nrElementeCopiate = nrElemente - 1;
	afisareVector(vectorNou, nrElementeCopiate);

	dezalocare(&vectorNou, &nrElementeCopiate);

	return 0;
}