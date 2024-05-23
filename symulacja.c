#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "struktura.h"

#define PI 3.14159

//funkcja DlugoscPolaczen po wywolaniu zwraca randomowo wygenerowana dlugosc polaczenia zgodnie z rozkladem normalnym
double DlugoscPolaczen() {

    double u1;
    double u2;
    double p;

    do {

        u1 = (double)rand() / RAND_MAX;
        u2 = (double)rand() / RAND_MAX;
        p = sqrt(-2 * log(u1)) * cos(2 * PI * u2) * 100;

    } while (p <= 0 || p > 120);

    return p;
}


//funkcja PrzychodzacePolaczenia po wywolaniu zwraca randomowo wygenerowana ilosc polaczen zgodnie z rozkladem Poissona
int PrzychodzacePolaczenia() {

    int lambda = 2;
    double limit = exp(-lambda);
    double p = 1;
    int i = 0;

    do {
        i++;
        p *= (double)rand() / RAND_MAX;

    } while (p > limit);

    return i;

}

//funkcja DodajDoKolejki jest odpowiedzialna za dodawanie polaczen do kolejki, jesli zaden pracownik nie jest dostepny


void DodajDoKolejki(Kolejka** head, int number) {
    if (*head == NULL) {
        *head = (Kolejka*)malloc(sizeof(Kolejka));
        if (*head == NULL) {
            printf("Blad alokacji pamieci");
            exit(EXIT_FAILURE);
        }
        (*head)->data = number;
        (*head)->nastepny = NULL;
    }
    else {
        Kolejka* element = *head;
        while (element->nastepny != NULL) {
            element = element->nastepny;
        }
        element->nastepny = (Kolejka*)malloc(sizeof(Kolejka));
        if (element->nastepny == NULL) {
            printf("Blad alokacji pamieci");
            exit(EXIT_FAILURE);
        }
        element->nastepny->data = number;
        element->nastepny->nastepny = NULL;
    }
}

void UsunElementZPoczatkuKolejki(Kolejka** head) {
    Kolejka* temp = NULL;
    if (*head != NULL) {
        temp = (*head)->nastepny;
        free(*head);
        *head = temp;
    }
}

void WypiszKolejke(Kolejka* head) {
    if (head == NULL) {
        printf("Kolejka jest pusta\n");
    }
    else {
        Kolejka* element = head;
        while (element != NULL) {
            printf("%d ", element->data);
            element = element->nastepny;
        }
        printf("\n");
    }
}

int DlugoscKolejki(Kolejka* head) {
    int counter = 0;
    while (head != NULL) {
        counter++;
        head = head->nastepny;
    }
    return counter;
}


int ObslugaPolaczen(Pracownik* pracownicy, int LiczbaPracownikow, Kolejka** kolejka, int idKlientaCounter) {

    int liczbaPolaczen = PrzychodzacePolaczenia();

    for (int i = 0; i < liczbaPolaczen; i++) {

        Klient nowyKlient;
        nowyKlient.IdKlienta = idKlientaCounter++;

        int pracownikZnaleziony = 0;

        for (int j = 0; j < LiczbaPracownikow; j++) {

            if (pracownicy[j].Dostepnosc == wolny) {

                nowyKlient.IdPracownika = pracownicy[j].Identyfikator;

                pracownicy[j].Dostepnosc = zajety;
                pracownicy[j].CzasRozmowy = DlugoscPolaczen();

                pracownikZnaleziony = 1;
                break;

            }
        }
        if (!pracownikZnaleziony) {
            DodajDoKolejki(kolejka, nowyKlient.IdKlienta);
        }


    }

    return idKlientaCounter;

}

void SprawdzPracownikow(Pracownik* pracownicy, int LiczbaPracownikow, Kolejka** kolejka) {

    for (int i = 0; i < LiczbaPracownikow; i++) {

        if (pracownicy[i].Dostepnosc = zajety && pracownicy[i].CzasRozmowy <= 0) {
            pracownicy[i].Dostepnosc = wolny;
            pracownicy[i].CzasRozmowy = 0;
        }

        if (*kolejka != NULL) {

            int IdKlienta = (*kolejka)->data;

            UsunElementZPoczatkuKolejki(kolejka);

            pracownicy[i].Dostepnosc = zajety;
           
            pracownicy[i].CzasRozmowy = DlugoscPolaczen();

            printf("Pracownik %d przejal klienta %d z kolejki, pozostaly czas rozmowy to %.00f min\n", pracownicy[i].Identyfikator, IdKlienta, pracownicy[i].CzasRozmowy);
            
        }


    }


}


int symulacja(Pracownik* pracownicy, int liczbaPracownikow) {

    Kolejka* kolejka = NULL;
    int IdKlientaCounter = 0;

    for (int t = 0; t < 480; t += 15) {

        printf("Kolejka po %d min: ", t);

        IdKlientaCounter = ObslugaPolaczen(pracownicy, liczbaPracownikow, &kolejka, IdKlientaCounter);

        WypiszKolejke(kolejka);

        printf("\n");

        for (int i = 0; i < liczbaPracownikow; i++) {
            if (pracownicy[i].Dostepnosc = zajety) {
                pracownicy[i].CzasRozmowy -= 15;
            }
        }

        SprawdzPracownikow(pracownicy, liczbaPracownikow, &kolejka);

    }

    return 0;


}

