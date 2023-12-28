//
// Created by varju on 2021.11.23..
//
#include "debugmalloc.h"
#include "strukturak.h"
#include <stdio.h>
#include "fuggvenyek.h"

int fesufeltolt(Ugyfelek *strazsa){
    FILE *fp;
    fp= fopen("adatok.txt","r");
    int dbugyfel=0;
    fscanf(fp,"%d\n",&dbugyfel);
    Ugyfelek *uj;
    while (dbugyfel!=0){
        uj= (Ugyfelek *)malloc(sizeof (Ugyfelek));
        uj->nev= fajlbololvas(fp);          //string
        uj->telefonszam= fajlbololvas(fp);  //string
        uj->email=fajlbololvas(fp);         //string
        fscanf(fp,"%d\n",&uj->dbauto);
        Autok *ujauto;
        uj->elsoauto=NULL;
        uj->kov=NULL;
            for (int i = 0; i != uj->dbauto; i++) {
                ujauto = (Autok *) malloc(sizeof(Autok));
                ujauto->tulaj = fajlbololvas(fp);
                ujauto->rendszam = fajlbololvas(fp);
                ujauto->tipus = fajlbololvas(fp);
                fscanf(fp, "%d\n", &ujauto->datum);
                ujauto->javitasok= fajlbololvas(fp);
                ujauto->vizsga = fajlbololvas(fp);
                fscanf(fp, "%d\n", &ujauto->ar);
                ujauto->kov=NULL;
                auto_befuz(ujauto, uj);
            }
        ugyfel_beszur(uj, strazsa);
        dbugyfel--;
    }
    fclose(fp);
    return dbugyfel;
}
int ugyfelszamol(Ugyfelek* strazsa){
    Ugyfelek *mozgo=strazsa->kov;
    int db=0;
    while(mozgo!=NULL){
        db+=1;
        mozgo=mozgo->kov;
    }
    return db;
}
int fesulement(Ugyfelek *strazsa, int dbugyfel){
    FILE *fp;
    fp= fopen("adatok.txt","w");
    Ugyfelek *mozgo=strazsa->kov;
    fprintf(fp,"%d\n",dbugyfel);
    while (dbugyfel!=0){
        fprintf(fp,"%s\n",mozgo->nev);
        fprintf(fp,"%s\n",mozgo->email);
        fprintf(fp,"%s\n",mozgo->telefonszam);
        fprintf(fp,"%d\n",mozgo->dbauto);
        Autok *mozgoauto;
        for(mozgoauto=mozgo->elsoauto;mozgoauto!=NULL;mozgoauto=mozgoauto->kov){
            fprintf(fp,"%s\n",mozgoauto->tulaj);
            fprintf(fp,"%s\n",mozgoauto->rendszam);
            fprintf(fp,"%s\n",mozgoauto->tipus);
            fprintf(fp,"%d\n",mozgoauto->datum);
            fprintf(fp,"%s\n",mozgoauto->javitasok);
            fprintf(fp,"%s\n",mozgoauto->vizsga);
            fprintf(fp,"%d\n",mozgoauto->ar);
        }
        mozgo=mozgo->kov;
        dbugyfel--;
    }
    fclose(fp);
    return 0;
}
void autofelszabadit (Autok *ptr){
    free(ptr->tulaj);
    free(ptr->rendszam);
    free(ptr->tipus);
    free(ptr->vizsga);
    free(ptr->javitasok);
}
void ugyfelfelszabadit(Ugyfelek *ptr){
    if (ptr->nev != NULL){
        free(ptr->nev);
        free(ptr->email);
        free(ptr->telefonszam);
    }
}
void felszabadit(Ugyfelek *strazsa) {
    Ugyfelek *mozgo=strazsa->kov;
    while(mozgo!=NULL) {
        Ugyfelek *kov=mozgo->kov;

        Autok *mozgoauto = mozgo->elsoauto;

        while (mozgoauto != NULL) {
            Autok *kovauto = mozgoauto->kov;
            autofelszabadit(mozgoauto);
            free(mozgoauto);
            mozgoauto = kovauto;
        }
        ugyfelfelszabadit(mozgo);
        free(mozgo);
        mozgo=kov;
    }
}
