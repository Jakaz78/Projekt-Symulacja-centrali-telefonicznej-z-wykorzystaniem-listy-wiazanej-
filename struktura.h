#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#define PI 3.14159

typedef enum {
    zajety, wolny
} av;

typedef struct {
    char Imie[20];
    int Identyfikator;
    av Dostepnosc;
    double CzasRozmowy;
} Pracownik;

typedef struct {
    int IdKlienta;
    int IdPracownika;
} Klient;

typedef struct Kolejka {
    int data;
    struct Kolejka* nastepny;
} Kolejka;
