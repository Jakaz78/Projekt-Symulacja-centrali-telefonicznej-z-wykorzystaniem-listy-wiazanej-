#include <stdio.h>
#include <stdlib.h>


typedef enum {
	zajety, wolny
}av;


typedef struct {

	int Identyfikator;
	av Dostepnosc;
	double CzasRozmowy;
	char Imie[20];

}Pracownik;

typedef struct {

	int IdKlienta;
	int IdPracownika;

}Klient;

typedef struct Kolejka {

	int data;
	struct Kolejka* nastepny;

} Kolejka;


