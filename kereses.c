//
// Created by varju on 2021.11.21..
//
#include "debugmalloc.h"
#include <stdio.h>
#include "strukturak.h"
#include "fuggvenyek.h"

void fomenukiir(){
    printf("(1)Modositasok\n(2)Kereses\n(3)Javitasok\n(4)Szerviztortenet/befizetes\n(5)Listazas\n(6)Mentes es kilepes\n");
}
void autokiir(Autok *ezt){
    printf("Tulaj:%s\n",ezt->tulaj);
    printf("Rendszam:%s\n",ezt->rendszam);
    printf("Tipus:%s\n",ezt->tipus);
    printf("Forgalmi:%s\n\n\n",ezt->vizsga);
}
void keres_auto_kiir(Ugyfelek *strazsa){
    printf("Rendszam:\n");
    char *rendszam=olvas();
    Autok *keresett;
    keresett=auto_keres(rendszam, strazsa);
    if(keresett!=NULL){
        //van ilyen rendszamu auto
        autokiir(keresett);
    }
    else {
        printf("Nincs ilyen rendszamu auto.\n");
    }
    free(rendszam);
}
void ugyfel_kiir(Ugyfelek *ezt){
    printf("Nev:%s\n",ezt->nev);
    printf("Email:%s\n",ezt->email);
    printf("Telefonszam:%s\n",ezt->telefonszam);
    printf("db jarmu:%d\n\n\n",ezt->dbauto);
}
void keres_ugyfel_kiir(Ugyfelek *strazsa){
    printf("Ugyfel neve:\n");
    char *nev=olvas();
    Ugyfelek *keresett=tulaj_keres(nev, strazsa);
    if(keresett!=NULL){
        //talalt kiir mindent
        ugyfel_kiir(keresett);
        Autok *mozgo;
        for(mozgo=keresett->elsoauto;mozgo!=NULL;mozgo=mozgo->kov){
            printf("%s\n",mozgo->rendszam);
        }
    }
    else{
        printf("Ilyen nevu ugyfel nincs.\n");
    }
    free(nev);
}
void keresesmenukiir(){
    printf("(1)Auto keres.\n");
    printf("(2)Ugyfel keres.\n");
    printf("(3)Vissza a fomenube.\n");
}
void keres(Ugyfelek *strazsa){
    int utasitas=0;
    int kilep=0;
    do{
        if(kilep!=2)
             keresesmenukiir();
        scanf("%d",&utasitas);
        switch (utasitas) {
            case 1://(1) rendszám alapján lehet keresni majd megjelenik minden adatot
                keres_auto_kiir(strazsa);
                break;
            case 2://(2) ügyfél neve alapján keresés, majd megjelenik az ügyfél adatai és a hozzá tartozó autók rendszámai
                keres_ugyfel_kiir(strazsa);
                break;
            case 3://(3) Vissza a főmenübe.
                kilep=1;
                break;
            default:
                kilep=2;
                utasitas=3;
        }
    } while(kilep!=1);
}