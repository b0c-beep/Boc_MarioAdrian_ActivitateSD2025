#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Moneda {
	char* taraEmitenta;
	int valoareNominala;
	float greutate;
	int anEmitere;
};
typedef struct Moneda Moneda;

Moneda initializare_moneda(const char* tara, int valoare, float greutate, int an)
{
	Moneda m;
	m.taraEmitenta = (char*)malloc(strlen(tara) + 1);
	strcpy_s(m.taraEmitenta, strlen(tara) + 1, tara);
	m.valoareNominala = valoare;
	m.greutate = greutate;
	m.anEmitere = an;
	return m;
}

struct Nod {
	Moneda info;
	struct Nod* next;
};
typedef struct Nod Nod;

void inserareMonedaInLista(Nod** lista, Moneda m)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = m;
	nou->info.taraEmitenta = (char*)malloc(strlen(m.taraEmitenta) + 1);
	strcpy_s(nou->info.taraEmitenta, strlen(m.taraEmitenta) + 1, m.taraEmitenta);
	nou->next = NULL;

	if (*lista != NULL)
	{
		Nod* p = *lista;
		while (p->next != NULL)
		{
			p = p->next;
		}
		p->next = nou;
		
	}
	else
	{
		(*lista) = nou;
	}
}

void afisareMoneda(Moneda m)
{
	printf("Tara Emitenta: %s\n", m.taraEmitenta);
	printf("Valoare Nominala: %d\n", m.valoareNominala);
	printf("Greutate: %.2f\n", m.greutate);
	printf("An Emitere: %d\n\n", m.anEmitere);
}

void afisareLista(Nod* lista)
{
	while (lista)
	{
		afisareMoneda(lista->info);
		lista = lista->next;
	}
}

Moneda getMonedaGreutateMaxima(Nod* lista)
{
	float greutateMaxima = 0;
	Nod* p = lista;
	while (p)
	{
		if (p->info.greutate > greutateMaxima)
			greutateMaxima = p->info.greutate;
		p = p->next;
	}

	p = lista;
	while (p && p->info.greutate != greutateMaxima)
	{
		p = p->next;
	}
	
	Moneda m = p->info;
	//deepcopy
	m.taraEmitenta = (char*)malloc(strlen(p->info.taraEmitenta) + 1);
	strcpy_s(m.taraEmitenta, strlen(p->info.taraEmitenta) + 1, p->info.taraEmitenta);
	return m;
}

void stergeMonedaDinLista(Nod** lista, float greutate)
{
	if (*lista)
	{
		Nod* p = *lista;
		int i = 0;
		int dim = 0;
		while (p)
		{
			if (p->info.greutate == greutate)
				i = dim;
			p = p->next;
			dim++;
		}
		if (i == 0) //nodul de sters este primul
		{
			Nod* aux = (*lista);
			(*lista) = aux->next;
			free(aux->info.taraEmitenta);
			free(aux);
		}
		else if (i == dim) //nodul de sters este ultimul
		{
			p = (*lista);
			while (p->next->next)
			{
				p = p->next;
			}
			Nod* aux = p->next;
			p->next = NULL;
			free(aux->info.taraEmitenta);
			free(aux->next);
		}
		else
		{
			p = (*lista);
			while (p->next && p->next->info.greutate != greutate)
			{
				p = p->next;
			}
			Nod* aux = p->next;
			p->next = p->next->next;
			free(aux->info.taraEmitenta);
			free(aux);
		}
	}
}

void dezalocareLista(Nod** lista)
{
	while ((*lista))
	{
		Nod* aux = (*lista);
		free(aux->info.taraEmitenta);
		(*lista) = (*lista)->next;
		free(aux);
	}
}

Moneda citireMonedaDinFisier(FILE* f)
{
	Moneda m;
	char buffer[100] = "";
	char sep[3] = ",\n";
	fgets(buffer, 100, f);
	char* aux = strtok(buffer, sep);
	m.taraEmitenta = (char*)malloc(strlen(aux) + 1);
	strcpy_s(m.taraEmitenta, strlen(aux) + 1, aux);

	m.valoareNominala = atoi(strtok(NULL, sep));
	m.greutate = atof(strtok(NULL, sep));
	m.anEmitere = atoi(strtok(NULL, sep));
	return m;
}

Nod* cititreListaDinFisier(const char* numeFisier)
{
	FILE* f = fopen(numeFisier, "r");
	Nod* lista = NULL;

	while (!feof(f))
	{
		inserareMonedaInLista(&lista, citireMonedaDinFisier(f));
	}

	fclose(f);
	return lista;
}

int main()
{
	Moneda m1 = initializare_moneda("Romania", 2, 25.7, 1998);
	Moneda m2 = initializare_moneda("Franta", 5, 18.9, 1879);
	Moneda m3 = initializare_moneda("Germania", 4, 22.3, 1956);
	Moneda m4 = initializare_moneda("Danemarca", 3, 45, 2001);
	Moneda m5 = initializare_moneda("Slovenia", 1, 24.8, 2005);
	Moneda m6 = initializare_moneda("Afganistan", 1, 35.9, 1990);

	Nod* lista = NULL;
	/*inserareMonedaInLista(&lista, m1);
	inserareMonedaInLista(&lista, m2);
	inserareMonedaInLista(&lista, m3);
	inserareMonedaInLista(&lista, m4);
	inserareMonedaInLista(&lista, m5);
	inserareMonedaInLista(&lista, m6);*/


	lista = cititreListaDinFisier("monezi.txt");

	afisareLista(lista);

	//Moneda monedaMax = getMonedaGreutateMaxima(lista);

	//printf("\n\nMoneda cu greutate maxima:\n");
	//afisareMoneda(monedaMax);

	//printf("\n\n");

	//stergeMonedaDinLista(&lista, 45);

	//afisareLista(lista);

	//free(monedaMax.taraEmitenta);
	dezalocareLista(&lista);
	return 0;
}