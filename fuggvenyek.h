//
// Created by varju on 2021.11.28..
//
#include "strukturak.h"
#ifndef MAIN_C_FUGGVENYEK_H
#define MAIN_C_FUGGVENYEK_H
//modosit.c
char *olvas();
char *fajlbololvas(FILE *fp);
Ugyfelek * tulaj_keres(char *tulajneve,Ugyfelek *strazsa);
Autok * auto_keres(char *rendszam,Ugyfelek *strazsa);
void auto_befuz(Autok *ezt,Ugyfelek *tulaj);
void ugyfel_beszur(Ugyfelek *befuzendo,Ugyfelek *strazsa);
void modosit_menu(Ugyfelek *strazsa);


//kereses.c
void keres(Ugyfelek *strazsa);
void fomenukiir();


//javitas_szerviz.c
char *pontosido();
void menu3(Ugyfelek *strazsa);
void menu4(Ugyfelek *null);


//listazas.c
char* muszakivalt (char*datum);
int dbauto(Ugyfelek *null);
void listazas (Ugyfelek *null);
int datumszam(char *datum);
char *atvalt(char *datum);


//fajlkezeles.c
int fesufeltolt(Ugyfelek *strazsa);
void felszabadit(Ugyfelek *strazsa);
int fesulement(Ugyfelek *strazsa, int dbugyfel);
void autofelszabadit (Autok *ptr);
int ugyfelszamol(Ugyfelek* strazsa);

#endif //MAIN_C_FUGGVENYEK_H
