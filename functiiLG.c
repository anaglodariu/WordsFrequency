/*GLODARIU Ana - 311CB*/
#include "tlg.h"
#include "thash.h"

TLG Aloc_CelulaG(void* x)
{
	TLG aux = NULL;
  	aux = (TLG)malloc(sizeof(TCelulaG));
   	if (!aux) { 
        return NULL;
    }

	aux->info = x;
	aux->urm = NULL;
	return aux;
}

//intoarce 1/0 = inserare reusita/nereusita
int Ins_SubLista(TLG *aL, void* ae, TFCmp compar) 
{
    TSubElem  *subelem = (TSubElem *)ae;
    TSubElem *elem = NULL;
    int ok = 0; //verific daca am inserat deja cuv
    TLG aux = NULL;
    /*daca cuvantul e deja in sublista, cresc frecventa
    odata ce cresc frecv,
    sublista nu o sa mai fie in ordinea corecta, deci mut celula*/
    TLG p = *aL, ant1 = NULL;
    for(; p != NULL; ant1 = p, p = p->urm) {
        elem = (TSubElem *)p->info;
        if (strcmp(subelem->cuv, elem->cuv) == 0) {
            elem->frecv++;
            ok = 1;
            /* daca cuvantul e deja in sublista
            deja am alocat memorie pt structura in care retin cuv citit
            deci eliberez memoria*/
            free(subelem->cuv);
            free(subelem);
            break;
        }
    }
    if (ok == 1) {
        if (p == *aL) { 
            //daca elementul al carui frecventa o cresc e primul in sublista, nu se muta
            return 1;
        }
        //altfel, distrug legaturile celulei, pentru a o muta
        ant1->urm = p->urm;
        p->urm = NULL;
        aux = p;
    } else {
        aux = Aloc_CelulaG(ae);
        if (!aux) {
            return 0;
        }
        elem = (TSubElem *)ae;
    }
    /*dc am crescut frecv cuv, il reinserez
    ca sublista sa fie in ordine*/
    if (*aL == NULL) {
        //sublista era goala, am o celula acum 
        *aL = aux; 
        return 1;
    }
    TLG p1 = *aL, ant = NULL;
    for (; p1 != NULL ; ant = p1, p1 = p1->urm) {
        if (compar(elem, p1->info) == 1) {
            break;
        }
    }
    if (ant == NULL) {
        //se insereaza la inceput de lista
        aux->urm = *aL;
        *aL = aux;
    }
    else {
        //cand inseram in interior sau la finalul listei
        aux->urm = p1;
        ant->urm = aux;
    }
	return 1;
}

TElem* aloc_elemlista(void *ae)
{
    TSubElem  *subelem = (TSubElem *)ae;
    TElem *elem = (TElem *)malloc(sizeof(TElem));
    if (elem == NULL) {
        return NULL;
    }
    elem->lungime = strlen(subelem->cuv);
    elem->l = NULL;
    return elem;
}

//intoarce 1/0 = inserare reusita/nereusita
int Ins_Lista(TLG* aL, void* ae, TFCmp compar1, TFCmp compar2)
{
    int rez = 0;
    TSubElem  *subelem = (TSubElem *)ae;
    //vedem daca am mai bagat in lista un cuvant de aceeasi lungime
    //daca da, nu mai aloc celula noua in lista
    TLG p = *aL, ant = NULL;
    for (p = *aL ; p != NULL ; p = p->urm) {
        TElem *element = (TElem *)p->info;
        
        if ((strlen(subelem->cuv) == element->lungime)) {
            //inserare in sublista a cuvantului
            rez = Ins_SubLista(&element->l, ae, compar2);
            return rez;
        }
    }
    //daca nu, aloc memorie pt celula si pt informatia din ea
    TElem* elem = aloc_elemlista(ae); 
    if (!elem) {
        return 0;  
    }
    TLG aux = Aloc_CelulaG(elem);
    if (!aux) {
        free(elem);
        return 0;
    }
    
    if (*aL == NULL) {
        *aL = aux; //lista era goala, am o celula acum 
        rez = Ins_SubLista(&elem->l, ae, compar2);
        return rez;
    }
    //fac inserarea in lista in ordine crescatoare a lungimilor cuvintelor
    p = *aL;
    for (; p != NULL ; ant = p, p = p->urm) {
        if (compar1(elem, p->info) == 1) {
            break;
        }
    }
    if (ant == NULL) {
        //se insereaza la inceput de lista
        aux->urm = *aL;
        *aL = aux;
    }
    else {
        //cand inseram in interior sau la finalul listei
        aux->urm = p;
        ant->urm = aux;
    }
    //inserare sublista
    rez = Ins_SubLista(&elem->l, ae, compar2);
	return rez;
}

void DistrugeLG(TLG* aL, TF elib_subelem) /* distruge lista */
{
	while(*aL != NULL) {
        TLG aux = *aL;     /* adresa celulei eliminate */
        if (!aux) {
            return;
        }

        *aL = aux->urm;    /* deconecteaza celula din lista */
        elib_subelem(aux->info); /* elib.spatiul ocupat de element*/
        free(aux);   /* elibereaza spatiul ocupat de celula */
    }
}