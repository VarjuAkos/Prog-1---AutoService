//
// Created by varju on 2021.11.25..
//
#include <stdio.h>
#include "debugmalloc.h"
#include "fuggvenyek.h"
#include "strukturak.h"

char* muszakivalt (char*datum){//2021:11:25---->2023:11:25
    char*uj=(char*) malloc(11*sizeof (char));
    if(uj==NULL)
        printf("Helyfoglalas sikertelen volt.\n");
    for(int i=0;i<10;i++){
        if(i!=3){
            uj[i]=datum[i];
        }
        else
            uj[i]=datum[i]-'0'+'2';
    }
    uj[10]='\0';
    return uj;
}

int dbauto(Ugyfelek *null){
    Ugyfelek *mozgo;
    Autok  *mozgoauto;
    int dbauto=0;
    for(mozgo=null->kov;mozgo!=NULL;mozgo=mozgo->kov){
        for(mozgoauto=mozgo->elsoauto;mozgoauto!=NULL;mozgoauto=mozgoauto->kov){
            dbauto+=1;
        }
    }
    return dbauto;
}


void listaz(Ugyfelek* null,int dbauto){
    Autok **tomb=(Autok**) malloc(dbauto*sizeof(Autok*));
    if(*tomb==NULL)
        printf("Helyfoglalás sikertelen volt.\n");
    Ugyfelek *mozgo;
    Autok *mozgoauto;
    int szam=0;
    for(mozgo=null->kov;mozgo!=NULL;mozgo=mozgo->kov) {                                     //datumakat tombe rakja
        for (mozgoauto = mozgo->elsoauto; mozgoauto!= NULL; mozgoauto = mozgoauto->kov){    //addig megy amig az osszes datum nincs a tombe
            tomb[szam] = mozgoauto;                                                          //
            szam+=1;
        }
    }       //ezt rendezni kell
    for (int i = dbauto-1; i > 0; --i) {
        /* egymás utáni párok ciklusa */
        for (int j = 0; j < i; ++j) {
            if (tomb[j]->datum > tomb[j+1]->datum) {
                Autok* temp = tomb[j];
                tomb[j] = tomb[j+1];
                tomb[j+1] = temp;
            }
        }
    }
    for (int i = 0; i<dbauto; i++)
        printf("%s %s\n", tomb[i]->rendszam, tomb[i]->vizsga);
    free(tomb);
}
void lejart(Ugyfelek *null){
    char* ido = pontosido();
    char* atvaltott = atvalt(ido);
    int maidatum=datumszam(atvaltott);
    Ugyfelek *mozgo;
    Autok *mozgoauto;
    printf("Lejart:\n");
    for(mozgo=null->kov;mozgo!=NULL;mozgo=mozgo->kov) {
        for (mozgoauto = mozgo->elsoauto; mozgoauto!= NULL; mozgoauto = mozgoauto->kov){
            if(mozgoauto->datum<maidatum){
                printf("%s ervenyes volt:%s-ig\n",mozgoauto->rendszam,mozgoauto->vizsga);
            }
        }
    }
    free(atvaltott);
    free(ido);


}
//ez csunya, nagyon csunya
char *atvalt(char *datum){
    char *helyesforma=(char *) malloc(11*sizeof (char ));
    if(helyesforma==NULL)
        printf("A helyfoglalas sikertelen volt.\n");
    for(int i=0;i<5;i++){
        helyesforma[i]=datum[i];
    }
    helyesforma[4]=':';
    if(datum[7]=='n'& datum[6]=='a'){           //Jan  01
        helyesforma[5]='0'; helyesforma[6]='1';
    }else if(datum[5]=='F'){                    //Feb  02
        helyesforma[5]='0'; helyesforma[6]='2';
    }else if(datum[6]=='a'&datum[7]=='r'){      //Mar  03
        helyesforma[5]='0'; helyesforma[6]='3';
    }else if(datum[6]=='p'){                    //Apr  04
        helyesforma[5]='0'; helyesforma[6]='4';
    }else if(datum[7]=='y'){                    //May  05
        helyesforma[5]='0'; helyesforma[6]='5';
    }else if(datum[6]=='u'&datum[7]=='n'){      //Jun  06
        helyesforma[5]='0'; helyesforma[6]='6';
    }else if(datum[6]=='u'& datum[7]=='l'){     //Jul  07
        helyesforma[5]='0'; helyesforma[6]='7';
    } else if(datum[7]=='g'){                   //Aug  08
        helyesforma[5]='0'; helyesforma[6]='8';
    }else if(datum[5]=='S'){                    //Sep  09
        helyesforma[5]='0'; helyesforma[6]='9';
    }else if(datum[5]=='O'){                    //Okt  10
        helyesforma[5]='1'; helyesforma[6]='0';
    }else if(datum[5]=='N'){                    //Nov  11
        helyesforma[5]='1'; helyesforma[6]='1';
    }else {                                     //Dec  12
        helyesforma[5] = '1';
        helyesforma[6] = '2';
    }
    helyesforma[7]=':';
    for(int i=8;i<10;i++){
        helyesforma[i]=datum[i+1];
    }
    helyesforma[10]='\0';
    return helyesforma;
}
int datumszam(char *datum){
    int ertek=10000000*(datum[0]-'0')+1000000*(datum[1]-'0')+100000*(datum[2]-'0')+10000*(datum[3]-'0')+1000*(datum[5]-'0')+100*(datum[6]-'0')+10*(datum[8]-'0')+(datum[9]-'0');
    return ertek;
}
void listazkiir(){
    printf("(1)Listazva kiir\n");
    printf("(2)Lejartak megjelenitese\n");
    printf("(3)Vissza a fomenube\n");
}
void listazas (Ugyfelek *null){
    int utasitas;
    do{
        listazkiir();
        scanf("%d", &utasitas);
        switch (utasitas){
            case 1:
                listaz(null, dbauto(null));
                break;
            case 2:
                lejart(null);
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
