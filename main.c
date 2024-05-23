#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>
#include "struktura.h"

void tekst_startowy(Pracownik* pracownicy, int liczbaPracownikow);
void utworzPracownikow(Pracownik* pracownicy, int rozmiar) {
	char* imiona[10] = { "Alicja", "Agata", "Marek", "Janusz", "Piotr", "Ewelina", "Tomasz", "Maria", "Magda", "Grzegorz" };

	for (int i = 0; i < rozmiar; i++) {
		snprintf(pracownicy[i].Imie, sizeof(pracownicy[i].Imie), "%s", imiona[i]);
		pracownicy[i].Identyfikator = i + 1;
		pracownicy[i].Dostepnosc = wolny;
		pracownicy[i].CzasRozmowy = 0.0;
	}
}





void main()
{
	srand((unsigned int)time(0));

	Pracownik pracownicy[10];
	utworzPracownikow(pracownicy, 10);

	tekst_startowy(pracownicy, 10);

}


void tekst_startowy(Pracownik* pracownicy, int liczbaPracownikow) {
	while (1) {
		printf("Witamy w centrali telefonicznej\n\n\n   Jak mozemy ci pomoc? \n\n");
		printf(" 1. Uruchomienie symulacji\n 2. Lista pracownikow \n 3. Wyjscie\n\n");

		while (1) {
			char przycisk = _getch();

			if (isalpha(przycisk)) {
				printf("Wpisano litere, wpisz liczbe i sproboj ponownie.\n\n");
				continue;
			}
			
			switch (przycisk) {
				
			case '1':
				system("cls");
				printf("Wybrano: \n * Uruchomienie symulacji *\n\n");


				symulacja(pracownicy, liczbaPracownikow);

				printf("---------------\n\n\n");
				printf("Powrot do menu.\n\n");
				printf("---------------\n\n\n");
				break;
			case '2':
				system("cls");
				printf("Wybrano: \n * Lista pracownikow *\n\n");

			

				while (1) {
					printf("Czy chcesz wyswietlic liste pracownikow? \n\n");
					printf("1. Tak\n2. Nie\n\n");

					char wybor = _getch();

					if (isalpha(wybor)) {
						printf("Wpisano litere, wpisz liczbe i sproboj ponownie.\n\n");
						continue;
					}

					switch (wybor) {
					case '1':
						system("cls");
						for (int i = 0; i < liczbaPracownikow; i++) {
							printf("%s\n", pracownicy[i].Imie);
						}
						printf("---------------\n\n\n");
						printf("\nPowrot do menu.\n\n\n");
						printf("---------------\n\n\n");
						break;
					case '2':
						system("cls");
						printf("Powrot do menu.\n\n\n");
						printf("---------------\n\n\n");
						system("cls");
						break;
					default:
						printf("Wprowadzono bledna liczbe. Sproboj ponownie.\n\n");
						continue;
					}
					break;
				}
				break;
			case '3':
				system("cls");
				while (1) {
					printf("Czy na pewno chcesz opuscic program?\n\n");
					printf("1. Tak\n2. Nie\n\n");
					
					char odp = _getch();
					if (isalpha(odp)) {
						printf("Wpisano litere, wpisz liczbe i sproboj ponownie.\n\n");
						continue;
					}
					switch (odp) {
					case '1':
						printf("Wyjscie z programu\n\n");
						return;
					case '2':
						printf("Powrot do menu.\n\n\n");
						printf("---------------\n\n\n");
						break;
					default:
						printf("Wprowadzono bledna liczbe. Sproboj ponownie.\n");
						continue;
					}
					system("cls");
					break;
				}
				break;
			case '4':

				printf("123");
				system("cls");
				break;

			default:
				printf("Wprowadzono bledna liczbe. Sproboj ponownie.\n\n");
				continue;
			}
			break;
		}
		
	}
}
