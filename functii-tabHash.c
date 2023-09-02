/*GLODARIU Ana - 311CB*/
#include "thash.h"

TH* InitTH(size_t M, TFHash fh)
{
    TH* h = (TH *) calloc(sizeof(TH), 1);
    if (!h) {
        printf("eroare alocare hash\n");
        return NULL;
    }

    h->v = (TLG *) calloc(M, sizeof(TLG));
    if(!h->v) {
        printf("eroare alocare vector de pointeri TLG in hash\n");
        free(h);
        return NULL;
    }

    h->M = M;
    h->fh = fh;
    return h;
}

void DistrTH(TH** ah, TF1 elib_elem, TF elib_subelem)
{
    TLG *p = NULL, el = NULL, aux = NULL;

    /* parcurgere cu pointeri */
    for (p = (*ah)->v; p < (*ah)->v + (*ah)->M; p++) {
        /* daca exista elemente corespunzatoare acestui hash
         * eliberam info din celula si apoi eliberam celula */
        for (el = *p; el != NULL; ) {
            aux = el;
            el = el->urm;
            elib_elem(aux->info, elib_subelem);
            free(aux);
        }
    }
    free((*ah)->v);
    free(*ah);
    *ah = NULL;
}

void AfiTH(TH* a, TF2 afi_subelem)
{
    TLG p = NULL, el = NULL;
    int i = 0;
    for (i = 0; i < a->M; i++) {
        p = a->v[i];
        if (p) {
            printf("pos %d: ", i);
            for(el = p; el != NULL; el = el->urm) {
                afi_subelem(el->info, -1);
            }
            printf("\n");  
        }  
    }
}
/*pentru afisarea de tipul "print n"
verific daca am ce afisa pentru fiecare 
a->v[i], pentru a respecta formatul de afisare
al cerintei*/
int verif_afisare(void * e, int maxfrecv) {
    TElem *elem = (TElem *)e;
    TLG p = elem->l;
    for(; p != NULL; p = p->urm) {
        TSubElem *subelem = (TSubElem *)p->info;
        if (subelem->frecv <= maxfrecv) {
            return 1;
        }
    }
    return 0;
}

void AfiTH2(TH* a, int maxfrecv, TF2 afi_subelem)
{
    TLG p = NULL, el = NULL;
    int i = 0;
    int ok = 0;
    for (i = 0; i < a->M; i++) {
        p = a->v[i];
        ok = 0;
        if (p) {
            for(el = p; el != NULL; el = el->urm) {
                ok = verif_afisare(el->info, maxfrecv);
                if (ok == 1) {
                    break;
                }
            }
            if (ok == 1) {
                printf("pos%d: ", i);
                for(el = p; el != NULL; el = el->urm) {
                    afi_subelem(el->info, maxfrecv);
                }
                printf("\n");
            }
        }  
    }
}

void AfiTH1(TH* a, int code, int lung, int* ok, TF2 afi_subelem)
{
    TLG p = a->v[code];
    for (; p != NULL; p = p->urm) {
        TElem *elem = (TElem *)p->info;
        if (elem->lungime == lung) {
            //cu ok verific daca am ce afisa
            *ok = 1;
            afi_subelem(p->info, -1);
            return;
        }
    }
}

int InsTH(TH* a, void* ae, TFCmp compar1, TFCmp compar2)
{ 
    //vedem unde in v trebuie bagat cuvantul citit dupa prima litera a sa
    int cod = a->fh(ae), rez = 0;
    rez = Ins_Lista(&a->v[cod], ae, compar1, compar2); 
    return rez;
}
