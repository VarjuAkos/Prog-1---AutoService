#include <stdio.h>
#include <string.h>
#include "strukturak.h"
#include "debugmalloc.h"
#include "fuggvenyek.h"


void modosit_menu_kiir(){
    printf("(1)Auto hozzaadasa\n(2)Ugyfel hozzaad\n(3)Auto torol\n(4)vissza a fomenube\n");
}
char *olvas() {
    int db = 0;
    char *sor = (char*) malloc(sizeof(char) * 1);
    sor[0] = '\0';
    char ujkar;
    if (scanf(" %c", &ujkar) == 1){
        do {
            /* itt a tömb nyújtása */
            char *ujtomb = (char*) malloc(sizeof(char) * (db+1+1));
            for (int i = 0; i < db; ++i)
                ujtomb[i] = sor[i];
            free(sor);
            sor = ujtomb;
            ujtomb[db] = ujkar;
            ujtomb[db+1] = '\0';
            ++db;
        }  while (scanf("%c", &ujkar) == 1 && ujkar != '\n');
        return sor;
    }   printf("minimum egy karakter kene");
    return NULL;
}
//InfoC olvas() atalakitasa
char *fajlbololvas(FILE *fp) {
    int db = 0;
    char *sor = (char*) malloc(sizeof(char) * 1);
    sor[0] = '\0';
    char ujkar;
    while (fscanf(fp,"%c", &ujkar) == 1 && ujkar != '\n') {
        /* itt a tömb nyújtása */
        char *ujtomb = (char*) malloc(sizeof(char) * (db+1+1));
        for (int i = 0; i < db; ++i)
            ujtomb[i] = sor[i];
        free(sor);
        sor = ujtomb;
        ujtomb[db] = ujkar;
        ujtomb[db+1] = '\0';
        ++db;
    }
    return sor;
}
//sztringet olvas be
Ugyfelek * tulaj_keres(char *tulajneve,Ugyfelek *strazsa){//név alapján keres, visszaadja az uygfel * vagy NULL-t
    Ugyfelek *mozgo =strazsa->kov;
    //akkor ha ez az elso ugyfel
    while (mozgo!=NULL) {
        if (strcmp(tulajneve, mozgo->nev) == 0)
            return mozgo;
        mozgo = mozgo->kov;
    }
    return NULL;
}

Autok * auto_keres(char *rendszam,Ugyfelek *strazsa){//rendszam alapjan keres, visszaadja az auto * vagy NULL-t
    Ugyfelek *mozgo;
    Autok *mozgoauto;
    for(mozgo=strazsa->kov;mozgo!=NULL;mozgo=mozgo->kov) {
        for (mozgoauto = mozgo->elsoauto; mozgoauto!= NULL; mozgoauto = mozgoauto->kov){
            if(strcmp(rendszam,mozgoauto->rendszam)==0){
                return mozgoauto;

            }
        }
    }
    return NULL;
}

Autok * auto_beolvas(char *rendszam,char *tulaj){//mindent beolvas
    Autok *uj=(Autok*) malloc(sizeof (Autok));
    if(uj==NULL)
        printf("Helyfoglalás sikertelen volt.\n");
    uj->rendszam=rendszam;
    printf("Tipus:\n");
    uj->tipus=olvas();
    printf("Forgalmi vizsga ervenyessege:EEEE:HH:NN\n");
    uj->vizsga=olvas();
    uj->tulaj=tulaj;
    printf("Javitas:\n");
    uj->javitasok = olvas();
    uj->ar=0;
    uj->datum= datumszam(uj->vizsga);
    return uj;
}

void auto_befuz(Autok *ezt,Ugyfelek *tulaj){//befuzi a listába
    ezt->kov=tulaj->elsoauto;
    tulaj->elsoauto=ezt;
}
Ugyfelek *ugyfel_beolvas(char *ugyfelneve){//uygfel adatok beolvas
    Ugyfelek *uj= (Ugyfelek *)malloc(sizeof (Ugyfelek));
    if(uj==NULL)
        printf("Helyfoglalás sikertelen volt.\n");
    uj->nev=ugyfelneve;
    printf("Telefonszam:\n");
    uj->telefonszam=olvas();
    printf("Email:\n");
    uj->email=olvas();
    uj->elsoauto=NULL;
    uj->dbauto=0;
    return uj;
}
void ugyfel_beszur(Ugyfelek *befuzendo,Ugyfelek *strazsa){//ugyfelet beszur
    befuzendo->kov=strazsa->kov;
    strazsa->kov=befuzendo;
}

//keresi azt a strukturának a cimét ahol auto.kov=a torlendo címe
//torlendo cimét bekéri
Autok * torlendo_elotti(Ugyfelek *strazsa, Autok *torlendo){
    Ugyfelek *mozgo;
    Autok *mozgoauto;
    for(mozgo=strazsa->kov; mozgo != NULL; mozgo=mozgo->kov) {
        for (mozgoauto = mozgo->elsoauto; mozgoauto!= NULL; mozgoauto = mozgoauto->kov){
            if(mozgoauto->kov==torlendo)
                return mozgoauto;
        }
    }
    return NULL;
}
void auto_hozzaad(Ugyfelek *strazsa){//teljes hozzad fv
    printf("Tulaj:\n");
    char *tulaj=olvas();
    Ugyfelek *tulajdonos=tulaj_keres(tulaj,strazsa);
    if(tulajdonos!=NULL){
        printf("Rendszam:\n");
        char *rendszam=olvas();
        if(auto_keres(rendszam,strazsa)!=NULL){
            printf("Hiba: mar van ilyen rendszamu auto.\n");
            free(tulaj);
            free(rendszam);
        }
        else {
            auto_befuz(auto_beolvas(rendszam,tulaj), tulajdonos);
            printf("Auto hozzaadva\n");
            tulajdonos->dbauto+=1;
        }
    }
    else {
        printf("Hiba: nincs ilyen nevu tulaj.\n");
        free(tulaj);
    }
}
void ugyfel_hozzaad(Ugyfelek *strazsa){//teljes uygfel hozzaad fv.
    printf("Ugyfel neve:\n");
    char *nev=olvas();
    if(tulaj_keres(nev,strazsa)==NULL){
        //meg nincs-->tovabb
        ugyfel_beszur(ugyfel_beolvas(nev),strazsa);
        printf("Ugyfel sikeresen hozzadva.\n");
    }
    else {
        printf("Hiba: mar van ilyen nevu ugyfel.\n");
        free(nev);
    }

}
void auto_torol(Ugyfelek *strazsa){
    printf("Rendszam:\n");
    char *rendszam;
    rendszam=olvas();
    Autok *torlendo;
    torlendo=auto_keres(rendszam, strazsa); //keresi h letezik e az adott auto
    if(torlendo!=NULL){
        //létezik a torlendő auto-->tovabb
        printf("Biztosan torli:(1) IGEN (BARMI) NEM\n");
        int utasitas=0;
        scanf("%d",&utasitas);
        Ugyfelek *tulaj=tulaj_keres(torlendo->tulaj, strazsa);
        if(utasitas==1) {
            if (tulaj->elsoauto == torlendo) {
                tulaj->elsoauto = torlendo->kov;
                autofelszabadit(torlendo);
                free(torlendo);
            } else {
                Autok *torlendoremutat = torlendo_elotti(strazsa, torlendo);
                torlendoremutat->kov = torlendo->kov;
                autofelszabadit(torlendo);
                free(torlendo);
            }
            printf("Auto torolve.\n");
            tulaj->dbauto=tulaj->dbauto-1;
        }
        else{
            printf("Az auto megsem lett torolve.\n");
        }
    }
    else {
        printf("Nincs ilyen rendszamu auto.\n");
    }
    free(rendszam);
}
void modosit_menu(Ugyfelek *strazsa) {
    int utasitas;
    do{
        modosit_menu_kiir();
        scanf("%d", &utasitas);
        switch (utasitas){
            case 1://(1) autó hozzáadása: rendszám + adatok, majd visszalép a főmenübe
                auto_hozzaad(strazsa);
                break;
            case 2://
                ugyfel_hozzaad(strazsa);
                break;
            case 3:
                auto_torol(strazsa);//(3) autó törlése , rendszám alapján. Biztosan törli (1) igen, (2) mégsem. Ez utan vissza a főmenübe
                break;
            case 4://visszavisz a főmenube
                break;
            default:
                printf("Hiba: adjon meg normalis erteket.\n");
                putchar('\n');
                utasitas=4;
        }
    } while(utasitas!=4);
}
