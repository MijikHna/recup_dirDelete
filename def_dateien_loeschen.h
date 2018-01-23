#ifndef DEF_DATEIEN_LOESCHEN_H_INCLUDED
#define DEF_DATEIEN_LOESCHEN_H_INCLUDED

#include <dirent.h>
#define GROESSE 36
#define MEIN_PFAD "/home/kirill/Dokumente/NEU/"
#define PFADNAME_WEITER "recup_dir."
#define ERSTER_ORDER 10
#define LETZTER_ORDER 207

char *pfad_ende_berechnen(char *pfad_ende,size_t laenge_ende, int zaehler);
char **endungen_bestaetigen(int *anzahl_fertig);
int datei_loeschen(const DIR *pfad, char *pfadname, char **endungen_fertig, int anzahl_fertig);

#endif // DEF_DATEIEN_LOESCHEN_H_INCLUDED
