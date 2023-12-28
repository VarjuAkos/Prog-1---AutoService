//
// Created by varju on 2021.11.21..
//
#include <stdio.h>
#include "strukturak.h"
#include <time.h>
#include <string.h>
#include "debugmalloc.h"
#include "fuggvenyek.h"

char *hozzafuz(char *ehhez,char *ezt){
    int hossz1= (int) strlen(ehhez);
    int hossz2= (int) strlen(ezt);
    char *uj=(char*) realloc(ehhez, (hossz1+hossz2+1)*sizeof (char));
    if(uj==NULL)
        return NULL;
    strcat(uj,ezt);
    return uj;
}

void menukiir(){
    printf("(1)Olajcsere.\n");
    printf("(2)Muszaki vizsgaztatas.\n");
    printf("(3)Gumicsere.\n");
    printf("(4)Egyeb javitasok.\n");
    printf("(5)Vissza a fomenube.\n");
}
char *pontosido(){
    time_t mytime = time(NULL);
    char * ido = ctime(&mytime);
    ido[strlen(ido)-1] = '\0';
    for(int i=0;ido[i]!='\0';i++){
    }
    char *formalt=(char*) malloc(12*sizeof (char));
    if(formalt==NULL)
        printf("A helyfoglalas sikertelen volt.\n");
    for(int i=0;i!=4;i++){
        formalt[i]=ido[i+20];
    }
    formalt[4]=':';
    for(int i=5;i!=8;i++){
        formalt[i]=ido[i-1];
    }
    formalt[8]=':';
    for(int i=9;i!=11;i++){
        formalt[i]=ido[i-1];
    }
    formalt[11]='\0';
    return formalt;
}
void olaj_csere(Ugyfelek *strazsa){
    printf("Rendszam:\n");
    char *rendszam=olvas();
    char *olajcsere="Olajcsere datum:";
    Autok *mod= auto_keres(rendszam, strazsa);
    char* ido = pontosido();
    if(mod!=NULL){//tovabb, talalt
        mod->javitasok=hozzafuz(mod->javitasok,olajcsere);
        mod->javitasok=hozzafuz(mod->javitasok,ido);
        free(ido);
        mod->javitasok=hozzafuz(mod->javitasok,"\t");
        printf("Olajcsere hozzaadva.\n");
        mod->ar=mod->ar+25000;
    }
    else{
        printf("Nincs ilyen rendszamu auto.\n");
        free(ido);
    }
    free(rendszam);
}
void muszaki_vizsgaztatas(Ugyfelek *strazsa){
    printf("Rendszam:\n");
    char *rendszam=olvas();
    Autok *mod= auto_keres(rendszam, strazsa);
    char *ido = pontosido();
    if(mod!=NULL){//tovabb
        char *atvaltott = atvalt(ido);
        free(mod->vizsga);
        mod->vizsga= muszakivalt(atvaltott);
        free(atvaltott);
        mod->ar+=30000;
        mod->javitasok=hozzafuz(mod->javitasok,"Muszaki vizsgaztatas datum:");
        mod->javitasok=hozzafuz(mod->javitasok,ido);
        mod->javitasok=hozzafuz(mod->javitasok,"\t");
        free(ido);
        mod->datum= datumszam(mod->vizsga);
        printf("Ervenyes:%s\n", mod->vizsga);
    }
    else{
        printf("Nincs ilyen rendszamu auto.\n");
        free(ido);
    }
    free(rendszam);
}
void gumicsere(Ugyfelek *strazsa){
    printf("Rendszam:\n");
    char *rendszam=olvas();
    Autok *mod= auto_keres(rendszam, strazsa);
    char *ido = pontosido();
    if(mod!=NULL){
        mod->ar+=10000;
        mod->javitasok=hozzafuz(mod->javitasok,"Gumicsere datum:");
        mod->javitasok=hozzafuz(mod->javitasok,ido);
        mod->javitasok=hozzafuz(mod->javitasok,"\t");
        free(ido);
        printf("Gumicsere elvegezve.\n");
    }
    else{
        printf("Nincs ilyen rendszamu auto.\n");
        free(ido);
    }
    free(rendszam);
}
void egyebjavitas(Ugyfelek *strazsa){
    printf("Rendszam:\n");
    char *rendszam=olvas();
    Autok *mod= auto_keres(rendszam, strazsa);
    char *ido  =pontosido();
    if(mod!=NULL){
        printf("Elvegzett javitasok:\n");
        char*javitasok=olvas();
        mod->javitasok= hozzafuz(mod->javitasok,javitasok);
        mod->javitasok= hozzafuz(mod->javitasok," datum:");
        mod->javitasok= hozzafuz(mod->javitasok, ido);
        mod->javitasok= hozzafuz(mod->javitasok,"\t");
        free(ido);
        free(javitasok);
        printf("Koltseg:\n");
        int ar=0;
        scanf("%d",&ar);
        mod->ar=mod->ar+ar;
        printf("Javitas hozzaadva.\n");
    }
    else{
        printf("Nincs ilyen rendszamu auto.\n");
        free(ido);
    }
    free(rendszam);
}

void menu3(Ugyfelek *strazsa){
    int utasitas;
    do{
        menukiir();
        scanf("%d", &utasitas);
        switch (utasitas){
            case 1:
                olaj_csere(strazsa);
                break;
            case 2://
                muszaki_vizsgaztatas(strazsa);
                break;
            case 3:
                gumicsere(strazsa);
                break;
            case 4:
                egyebjavitas(strazsa);
                break;
            default:
                putchar('\n');
                utasitas=5;
                break;
        }
    } while(utasitas!=5);
}
void szerviz_menu(){
    printf("(1)Szerviztortenet\n");
    printf("(2)Befizetes\n");
    printf("(3)Vissza a fomenube\n");
}
void szerviztortenet(Ugyfelek *strazsa){
    printf("Rendszam:\n");
    char *rendszam=olvas();
    Autok *kiir= auto_keres(rendszam,strazsa);
    if(kiir!=NULL){
        printf("Szerviztortenet:\n");
        for(int i=0;kiir->javitasok[i]!='\0';i++){
            if(kiir->javitasok[i]=='\t')
                printf("\n");
            else
                printf("%c",kiir->javitasok[i]);
        }
        printf("Fizetendo osszeg:%dFt\n",kiir->ar);
    } else
        printf("Nincs ilyen rendszamu auto.\n");
    free(rendszam);
}
void befizet(Ugyfelek *null){
    printf("Rendszam:\n");
    char *rendszam=olvas();
    Autok *befizet= auto_keres(rendszam,null);
    if(befizet!=NULL){
        printf("Tartozas:%dFt\n",befizet->ar);
        printf("Befizet:\n");
        int ar=0;
        scanf("%d",&ar);
        if(ar>befizet->ar){
            printf("Hiba: Ennyivel nem tartozik.\n");
        }
        else {
            befizet->ar = befizet->ar - ar;
            printf("Maradek tartozas:%dFt\n", befizet->ar);
        }
    }
    else
        printf("Nincs ilyen rendszamu auto.\n");
    free(rendszam);
}
void menu4(Ugyfelek *null){
    int utasitas;
    do{
        szerviz_menu();
        scanf("%d", &utasitas);
        switch (utasitas){
            case 1:
                szerviztortenet(null);
                break;
            case 2:
                befizet(null);
                break;
            case 3://visszavisz a főmenube
                break;
            default:
                putchar('\n');
                utasitas=3;
                break;
        }
    } while(utasitas!=3);
}
