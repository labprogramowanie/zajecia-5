#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>

struct Student
{
	char* imie;
	char* nazwisko;
	int wiek;
	int nrIndeksu;
};

//struct Tablica tablica;
struct Tablica
{
	int aktualny;
	struct Student studenci[20];

}tablica;



void DodajStudenta(char* i, char* n, int w, int nr) {
	if (tablica.aktualny<20) {
		tablica.studenci[tablica.aktualny].imie = malloc(strlen(i) + 1);
		strcpy(tablica.studenci[tablica.aktualny].imie, i);

		tablica.studenci[tablica.aktualny].nazwisko = malloc(strlen(n) + 1);
		strcpy(tablica.studenci[tablica.aktualny].nazwisko, n);

		tablica.studenci[tablica.aktualny].wiek = w;

		tablica.studenci[tablica.aktualny].nrIndeksu = nr;

		tablica.aktualny++;
	}

}


void WypiszDane() {

	printf("Imie: \t Nazwisko: \t Wiek: \t nrIndeksu: \t\n");

	for (int q = 0; q < tablica.aktualny; q++) {
		printf("%s \t", tablica.studenci[q].imie);
		printf("%s \t", tablica.studenci[q].nazwisko);
		printf("%d \t", tablica.studenci[q].wiek);
		printf("%d \t", tablica.studenci[q].nrIndeksu);
		printf("\n");
	}
	if (tablica.aktualny == 0) { printf("Tablica jest pusta!\n"); }

}

int UsunPoNazwisku(char* naz) {
	int q = 0;

	while (q<tablica.aktualny) {

		if (strcmp(tablica.studenci[q].nazwisko, naz) == 0) {
			//strcmp 0 gdy s1==s2
			free(tablica.studenci[q].imie);
			free(tablica.studenci[q].nazwisko);
			int c = q;
			for (q; q < tablica.aktualny; q++) {
				tablica.studenci[q].imie = tablica.studenci[q + 1].imie;
				tablica.studenci[q].nazwisko = tablica.studenci[q + 1].nazwisko;
				tablica.studenci[q].wiek = tablica.studenci[q + 1].wiek;
				tablica.studenci[q].nrIndeksu = tablica.studenci[q + 1].nrIndeksu;

			}
			free(tablica.studenci[tablica.aktualny].imie);
			free(tablica.studenci[tablica.aktualny].nazwisko);
			tablica.aktualny--;

			return c;

		}
		q++;
	}
	return -1;
}

void UsunWszystko() {
	int q = 0;
	for (q; q < tablica.aktualny; q++) {
		free(tablica.studenci[q].imie);
		free(tablica.studenci[q].nazwisko);
		tablica.studenci[q].wiek = 0;
		tablica.studenci[q].nrIndeksu = 0;
	}
	tablica.aktualny = 0;
}

int WyszukajPoNrInd(int nr) {

	for (int q = 0; q < tablica.aktualny; q++) {
		if (tablica.studenci[q].nrIndeksu == nr) {
			return q;
		}
	}
	return -1;
}

void ZapiszDoPliku() {
	FILE* plik;

	plik = fopen("lista.txt", "w");
	int i = 0;

	while (i < tablica.aktualny)

	{

		fprintf(plik, "%s %s %i %i\n",tablica.studenci[i].imie, tablica.studenci[i].nazwisko,
			tablica.studenci[i].wiek, tablica.studenci[i].nrIndeksu);
		i++;
	}
	fclose(plik);
}


void OdczytajZPliku() {

		FILE* plik = fopen("lista.txt", "r");

		char i[20];
		char n[20];
		int w, nr;
		int g = 0;
		char separator;
		int koniec;

		while (1)
		{

			koniec = fscanf(plik, "%20s", i);

			if (koniec == EOF)

			{
				printf("\n");
				printf("*************** END ****************\n");
				printf("\n");
				break;

			}

			//fscanf(plik, "%s",  i);
			fscanf(plik, "%c", &separator);
			fscanf(plik, "%s", n);
			fscanf(plik, "%c", &separator);
			fscanf(plik, "%i", &w);
			fscanf(plik, "%c", &separator);
			fscanf(plik, "%i", &nr);
			fscanf(plik, "%c", &separator);

			printf("%i.\t%20s\t %20s\t %i\t %i\t \n", g+1, i, n, w, nr);
			DodajStudenta(i,n,w,nr);


			g++;
		}
		fclose(plik);
	}




void main() {
	char i[20];
	char n[20];
	char nazwisko[20];
	int w, nr;
	char c;
	tablica.aktualny = 0;


	while (5) {


		printf("1. Dodaj do listy w programie \n2. Wypisz dane tablicy programu \n3. Usun z listy programu po nazwisku \n4. Usun cala liste programu\n");
		printf("5. Wyszukiwanie ucznia po numerze indexu w tablicy programu \n6. Zapisz tablice programu do pliku \n7. Odczytaj z pliku tablice i wprowadz jako tablice programu\n");
		scanf("%s", &c);




		switch (c) {

		case '1':


			printf("Dodaj imie:\n");
			scanf("%s", &i);
			printf("Dodaj nazwisko:\n");
			scanf("%s", &n);
			printf("Dodaj wiek:\n");
			scanf("%i", &w);
			printf("Dodaj numer:\n");
			scanf("%i", &nr);

			DodajStudenta(i, n, w, nr);

			break;

		case '2':
			WypiszDane();
			break;

		case '3':
			printf("Podaj nazwisko:\n");
			scanf("%s", &nazwisko);
			UsunPoNazwisku(nazwisko);
			break;

		case '4':
			UsunWszystko();
			break;

		case '5':
			printf("Podaj numer indexu:\n");
			scanf("%d", &nr);
			printf("Numer elementu tablicy:\t %d \n", WyszukajPoNrInd(nr));
			break;

		case '6':
			ZapiszDoPliku();
			break;

			case '7':
				OdczytajZPliku();
			break;

		}
	}


	UsunWszystko();
}
