#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "def_dateien_loeschen.h"

char *pfad_ende_berechnen(char *pfad_ende, size_t laenge, int zaehler){
    int rest;
    int i;
    int index;

    //Index festlegen
    index=0;
    for(i=1; i<=zaehler;i=i*10){
        if(zaehler>=i){
            index++;
        }
    }
    //Alles auf /0 setzen
    for(i=0; i<laenge;i++){
        pfad_ende[i]='\0';
    }

    while(zaehler>0){
        rest=zaehler%10;
        pfad_ende[(index-1)]=rest+'0';
        zaehler=zaehler/10;
        index--;
    }
    return pfad_ende;
}

char **endungen_bestaetigen(int *anzahl_fertig){
    int i;
    int j;
    char ja_nein[10];
    int check[GROESSE];
    char **endungen_fertig;

    const char *endungen[]={".a", ".bgz",".bmp",".cab",".class",".deb", ".dll", ".DLL", ".elf", ".exe", ".EXE", ".Exe", ".gif", \
    ".gz",".html", ".ini", ".jpg", ".java", ".ldt", ".mp3", ".m4p", ".plist", ".pl", ".png", ".py", ".ppt", \
    ".rar", ".res", ".rpm", ".sh", ".tex", ".tif", ".txt", ".tz", ".xml", ".zip"};
    //const char *endungen[]={".bgz",".bmp",".cab",".class"};
    *anzahl_fertig=0;

    for(i=0; i<GROESSE; i++){
        printf("Endung \"%s\" loeschen? (j=ja/n=nein)\n", endungen[i]);
        scanf("%s",&ja_nein[0]);
        if(ja_nein[0]=='j'){
            check[i]=1;
            (*anzahl_fertig)++;
        }
        else{
            check[i]=0;
        }
        ja_nein[0]='\0';
    }
    printf("Anzahl fertig: %i\n", *anzahl_fertig);
    endungen_fertig=(char *)malloc(sizeof(char *)* *anzahl_fertig);
    //char *endungen_fertig[anzahl_fertig];
    printf("Size: %ld\n",(sizeof(endungen_fertig)/sizeof(char *)));
    for(i=0; i<GROESSE; i++){
        printf("%i ist %i\n",i, check[i]);
    }
    j=0;
    for(i=0; i<GROESSE; i++){
        if(check[i]==1){
            endungen_fertig[j]=(char *) malloc(sizeof(endungen[i]));
            strcpy(endungen_fertig[j], endungen[i]);
            printf("%s\n",endungen_fertig[j]);
            j++;
        }
    }
    return endungen_fertig;
}

int datei_loeschen(const DIR *pfad, char *pfadname, char **endungen_fertig, int anzahl_fertig){
    int i;
    int anzahl_geloeschte_dateien;
    char dateiname_loeschen[250];
    struct dirent *meine_datei;

    anzahl_geloeschte_dateien=0;
    while((meine_datei=readdir(pfad))!=NULL){
        //mit Endungen vergleichen wenn ja löschen
        strcpy(dateiname_loeschen, pfadname);
        strcat(dateiname_loeschen, "/");
        strcat(dateiname_loeschen, meine_datei->d_name);
        printf("\t Datei %s ist ausgewaehlt \n",dateiname_loeschen);
        for(i=0; i<anzahl_fertig; i++){
            if(strstr(dateiname_loeschen, endungen_fertig[i])!=NULL){
                if(remove(dateiname_loeschen)<0){
                    printf("Fehler beim Loeschen");
                }
                else{
                    printf("Datei: %s wurde geloescht\n", dateiname_loeschen);
                    anzahl_geloeschte_dateien++;
                }
            }
        }
    }
    return anzahl_geloeschte_dateien;
}



