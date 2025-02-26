#include<stdio.h>
#include<stdlib.h>

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
	m.kilometriiParcursi = kilometriiParcursi;
	m.initialaProducator = initialaProducator;
	m.sofer = (char*)malloc(strlen(sofer) + 1);
	strcpy_s(m.sofer, strlen(sofer) + 1, sofer);

	return m;
}

void afisare(struct Masina m) {
	printf("\nId: %d\n", m.id);
	printf("An fabricatie: %d\n", m.anFabricatie);
	printf("Sofer: %s\n", m.sofer);
	printf("Kilometrii Parcursi: %.2f\n", m.kilometriiParcursi);
	printf("Initiala Producatorului: %c\n", m.initialaProducator);
}

void modificaSofer(struct Masina* m, const char* soferNou) {
	if (strlen(soferNou) > 2)
	{
		if (m->sofer != NULL)
		{
			free(m->sofer);
		}
		m->sofer = (char*)malloc(strlen(soferNou) + 1);
		strcpy_s(m->sofer, strlen(soferNou) + 1, soferNou);
	}

}

void dezalocare(struct Masina* m) {
	if (m->sofer != NULL)
	{
		free(m->sofer);
		m->sofer = NULL;
		//printf("Dezalocare reusita");
	}
}

int main() {
	struct Masina masina;
	masina = initializare(1, 2004, "Robert", 2000, 'P'); //"P" -> 2 octeti
	afisare(masina);
	modificaSofer(&masina, "Andrei");
	afisare(masina);
	dezalocare(&masina);
	return 0;
}