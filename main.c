//
// Created by varju on 2021.11.21..
//
#include <stdio.h>
#include "strukturak.h"
#include "debugmalloc.h"
#include "fuggvenyek.h"

int main (void) {
    Ugyfelek *strazsa;
    strazsa = (Ugyfelek *) malloc(sizeof(Ugyfelek));
    if(strazsa==NULL)
        printf("Hiba: strazsa foglalása sikertelen.\n");
    strazsa->kov = NULL;
    strazsa->nev = NULL;
    strazsa->elsoauto = NULL;
    int utasitas=0;
    fesufeltolt(strazsa);
    setbuf(stdout, 0);
    int kilep=0;
    do {
        if(kilep!=2)
            fomenukiir();
        scanf("%d", &utasitas);
        switch (utasitas) {
            case 1:
                modosit_menu(strazsa);
                break;
            case 2:
                keres(strazsa);
                break;
            case 3:
                menu3(strazsa);
                break;
            case 4:
                menu4(strazsa);
                break;
            case 5:
                listazas(strazsa);
                break;
            case 6:
                fesulement(strazsa, ugyfelszamol(strazsa));
                felszabadit(strazsa);
                free(strazsa);
                kilep=1;
                break;
            default:
                printf("Adj meg normalis erteket.\n");
                utasitas=6;
                kilep=2;
                break;
        }
    } while (kilep !=1);
    return 0;
}
