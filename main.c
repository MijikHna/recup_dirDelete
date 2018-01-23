#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>

#include "def_dateien_loeschen.h"

int main(){
    //Variablen zur Bestimmung des Dateinamens und Pfades
    char pfadname [100];
    //char *mein_pfad="/home/kirill/Dokumente/NEU/";
    char ende[4];
    int zahler=ERSTER_ORDER;
    int anzahl_geloeschte_dateien;
    char dateiname_loeschen[100];
    size_t laenge_bis_pfad_abbruch;
    size_t laenge_ende;
    DIR *pfad;

    //Variablen zur Bestimmung der zu löschenden Endungen
    char **endungen_fertig;
    int i;
    int anzahl_fertig;

    //zu löschende Endungen bestimmen und ausgebn
    endungen_fertig=endungen_bestaetigen(&anzahl_fertig);
    printf("Endungen:\n");
    for(i=0; i<anzahl_fertig; i++){
        printf("%s\n", endungen_fertig[i]);
    }

    //Pfad zum Ordner bestimmen
    printf("Gebe Pfad ein: oder y fuer %s \n", MEIN_PFAD);
    scanf("%s", pfadname);
    if(*pfadname=='y'){
        strcpy(pfadname, MEIN_PFAD);
    }
    laenge_bis_pfad_abbruch=strlen(pfadname);

    //Verzeichnis öffnen, Dateien durchgehen und löschen
    printf("Verzeichnisse: \n");
    while(zahler<=LETZTER_ORDER){
        anzahl_geloeschte_dateien=0;
        strcpy(&pfadname[laenge_bis_pfad_abbruch], PFADNAME_WEITER);
        laenge_ende=4;
        strcat(pfadname,pfad_ende_berechnen(ende, laenge_ende, zahler));
        printf("Verzeichnis ist: %s\n", pfadname);
        //Dir öffnen
        pfad=opendir(pfadname);
        //Wenn Ordner schon geloescht wurde
        if(pfad==NULL){
            printf("Fehler bei Pfadnamen: \n");
            zahler++;
            closedir(pfad);
            continue;
        }
        //Dateien loeschen
        anzahl_geloeschte_dateien=datei_loeschen(pfad, pfadname, endungen_fertig, anzahl_fertig);
        //Anzahl geloeschter Dateien zahlen
        printf("%i Dateien geloescht \n", anzahl_geloeschte_dateien);
        //jede 10 Ordner Ausgabe kurz kontrolieren
        if((zahler%10)==0){
            getchar();
        }
        closedir(pfad);
        pfad=NULL;
        zahler++;
    }
    free(endungen_fertig);
    return EXIT_SUCCESS;
}
