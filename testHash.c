/*GLODARIU Ana - 311CB*/
#include <stdio.h>
#include "tlg.h"
#include "thash.h"
#include <string.h>
#define len 200

int codHash(void *element)
{ 
    TSubElem *subelem = (TSubElem *)element;
    char *cuvant = subelem->cuv;
    char c = cuvant[0];
    if (cuvant[0] >= 'A' && cuvant[0] <= 'Z') {
        c = c + 32;
    }
    return c - 'a';
}

void elib_subelem(void * e) 
{
    TSubElem *subelem = (TSubElem *)e;
    free(subelem->cuv);
    free(subelem);
}

void elib_elem(void * e, TF elib_subelem) 
{
    TElem *elem = (TElem *)e;
    DistrugeLG(&elem->l, elib_subelem);
    free(elem);
}

TH* GenerareHash()
{
    TH *h = NULL;
    size_t M = ('Z' - 'A') + 1;

    h = (TH *)InitTH(M, codHash);
    if (h == NULL) {
        return NULL;
    }

    return h;
}

void afisare(void * e, int maxfrecv) 
{
    TElem *elem = (TElem *)e;
    TLG p = elem->l;
    int ok = 0;
    int ok1 = 0;
    //ok1, ok sunt pentru afisarea in formatul conform cerintei
    if (maxfrecv == -1) {
        printf("(%d:", elem->lungime);
    }
    for (; p != NULL; p = p->urm) {
        TSubElem *subelem = (TSubElem *)p->info;
        if (maxfrecv == -1) {
            printf("%s/%d", subelem->cuv, subelem->frecv);
            if (p->urm != NULL) {
                printf(", ");
            }
        } else {
            if (subelem->frecv <= maxfrecv) {
                ok1 = 1;
                if (ok == 0) {
                    printf("(%d: ", elem->lungime);
                    ok = 1;
                }
                printf("%s/%d", subelem->cuv, subelem->frecv);
                if (p->urm != NULL) {
                    printf(", ");
                }
            }  
        }
    }
    if (maxfrecv == -1) {
        printf(")");
    }
    if (ok1 == 1) {
        printf(")");
    }
}
//pentru sortare subliste dupa frecventa lor si lexicografic
int CmpSubListe(void *e1, void *e2)
{
    TSubElem *subelem1 = (TSubElem *)e1;
    TSubElem *subelem2 = (TSubElem *)e2;
    
    if (subelem1->frecv > subelem2->frecv) { 
            return 1; //ordonare descresc dupa frecventa
    }
    if (subelem1->frecv == subelem2->frecv) { 
        if (strcmp(subelem1->cuv, subelem2->cuv) < 0) {
            return 1; //ordonare lexicografica, dc frecv sunt egale
        }
    }

    return 0;
}
//pentru sortare liste dupa lungimea cuvintelor
int CmpDupaLung(void *e1, void *e2)
{
    TElem *elem1 = (TElem *)e1;
    TElem *elem2 = (TElem *)e2;

    if (elem1->lungime < elem2->lungime) {
        return 1; //ordonare cresc dupa lungime cuv
    }

    return 0;
}

TH *citesteLista(FILE *f)
{
    TH *h = NULL;
    char *line = NULL;
    int l = 0;
    int ok1 = 0, ok = 1;
    //generam tabela hash si o initializam
    h = GenerareHash();
    if (h == NULL) {
        return NULL;
    }
    //facem citirea fiecarei linii din fisier / len este un macro
    line = malloc(len * sizeof(char));
    while (fgets(line, len, f) != NULL) {
        ok1  = 0; //cu ok1 vad daca citesc doar comanda simpla print 
        l = strlen(line);
        if (line[l - 1] == '\n') {
            line[l - 1] = '\0';
        }
        if (strcmp(line, "print") == 0) { 
            ok1 = 1; //cand citim din fisier doar comanda print
        }
        char *cuvant = strtok(line, " ,.\n");
        while (cuvant != NULL) {
            ok = 1; //cu ok vad daca citesc un cuv cu caractere de tip '0'-'9' 
            l = strlen(cuvant);

            if (cuvant[0] > '0' && cuvant[0] < '9') {
                ok = 0; 
            } else if (strcmp(cuvant, "print") == 0) {
                if (ok1 == 0) { 
                    //nu avem print normal
                    char *c = strtok(NULL, " ");
                    int ok3 = 0;
                    /*daca in c vom avea un caracter,
                    vom avea afisare de tipul "print c n"*/
                    if (c[0] >= 'a' && c[0] <= 'z') {
                        ok3 = 1;
                    } else if (c[0] >= 'A' && c[0] <= 'Z') {
                        c[0] = c[0] + 32;
                        ok3 = 1;
                    }

                    if (ok3 == 1) { //afisare de tipul "print c n"
                        int ok2 = 0;
                        char *n = strtok(NULL, " ");
                        int lung = atoi(n);
                        int code = c[0] - 'a';
                        AfiTH1(h, code, lung, &ok2, afisare);
                        if (ok2 != 0) {
                            //daca exista cuvinte de acel tip
                            printf("\n");
                        }   
                    } else if (ok3 == 0) { //afisare de tipul "print n"
                        int maxfrecv = atoi(c);
                        AfiTH2(h, maxfrecv, afisare);
                    }
                } else { //afisare de tipul "print"
                    AfiTH(h, afisare);
                }
            } else if (strcmp(cuvant, "insert") != 0 && l >= 3 && ok == 1) {
                /*cand citesc comanda de inserare, 
                consider doar cuvintele diferite de "insert", 
                de lungime >= 3 si fara caractere numerice*/
                //aloc memorie pentru structura TSubElem
                TSubElem *subelem = (TSubElem *)malloc(sizeof(TSubElem));
                if (subelem == NULL) {
                    return h;
                }
                subelem->cuv = (char *)calloc(sizeof(char) , l + 1);
                if (subelem->cuv == NULL) {
                    free(subelem);
                    return h;
                }
                memcpy(subelem->cuv, cuvant, l + 1);
                subelem->frecv = 1;
                int rez = 0; //valoare returnata de functie
                rez = InsTH(h, subelem, CmpDupaLung, CmpSubListe);
                if (rez == 0) {
                    elib_subelem(subelem);
                    return h;
                }
            }
            cuvant = strtok(NULL, " ,.\n");         
        } 
    }
    fclose(f);
    free(line);
    return h;
}
//numele fisierului din care citim este dat ca argument in linia de comanda
int main(int argc, char *argv[]) 
{
    FILE *f = NULL;
    if (argc != 0) {
        f = fopen(argv[1], "rt");
        if (f == NULL) {
            return 0;
        }
    }

    TH *h = NULL; 
    h = citesteLista(f);
    if (h == NULL) {
        printf("Tabela hash nu a putut fi generata\n");
        return 0;
    }
    //eliberare memorie tabela HASH
    DistrTH(&h, elib_elem, elib_subelem);

    return 0;
}
