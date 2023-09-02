/*GLODARIU Ana - 311CB*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#ifndef _LISTA_GENERICA_
#define _LISTA_GENERICA_

typedef struct celulag
{
  void* info;           /* adresa informatie */
  struct celulag *urm;   /* adresa urmatoarei celule */
} TCelulaG, *TLG; /* tipurile Celula, Lista  */

typedef int (*TFCmp)(void*, void*); /* functie de comparare doua elemente */
typedef void (*TF)(void*);     /* functie eliberare subelement */
typedef void (*TF1)(void*, TF); /*functie de eliberare element*/
typedef void (*TF2)(void*, int); /*functie de afisare*/

/* functii lista generica */
TLG Aloc_CelulaG(void*);
int Ins_IncLG(TLG*, void*);
int Ins_Lista(TLG*, void*, TFCmp, TFCmp);
int Ins_SubLista(TLG*, void*, TFCmp);
void DistrugeLG(TLG*, TF); /* distruge lista */

#endif
