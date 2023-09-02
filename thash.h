/*GLODARIU Ana - 311CB*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "tlg.h"

#ifndef _TAB_HASH_
#define _TAB_HASH_

typedef int (*TFCmp)(void*, void*); /* functie de comparare doua elemente */
typedef void (*TF)(void*);     /* functie eliberare subelement */
typedef void (*TF1)(void*, TF); /*functie de eliberare element*/
typedef void (*TF2)(void*, int); /*functie de afisare*/
typedef int (*TFHash)(void*);

typedef struct
{
    size_t M;
    TFHash fh;
    TLG *v;
} TH;
/*structura element*/
typedef struct
{
    int lungime;
    TLG l;
} TElem;
/*structura subelement*/
typedef struct
{
    char *cuv;
    int frecv;
} TSubElem;

/*functii pt TElem si TSubElem*/
TElem* aloc_elemlista(void *);


/* functii tabela hash */
TH* InitTH(size_t M, TFHash fh);
void DistrTH(TH**aa, TF1, TF);
void AfiTH(TH*a, TF2);
void AfiTH1(TH*a, int, int, int*, TF2);
void AfiTH2(TH*a, int, TF2);
int InsTH(TH*a, void*ae, TFCmp, TFCmp);
int verif_afisare(void*, int);

#endif
