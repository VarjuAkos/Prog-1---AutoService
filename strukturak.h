//
// Created by varju on 2021.11.21..
//

#ifndef MAIN_C_STRUKTURAK_H
#define MAIN_C_STRUKTURAK_H
typedef struct Autok{
    char* tulaj;
    char *rendszam;
    char *tipus;
    char *vizsga;
    char *javitasok;
    int datum;
    int ar;
    struct Autok *kov;
}Autok;
typedef struct Ugyfelek{
    char *nev;
    char *email;
    char *telefonszam;
    int dbauto;
    struct Ugyfelek *kov;
    struct Autok *elsoauto;
}Ugyfelek;
#endif //MAIN_C_STRUKTURAK_H
