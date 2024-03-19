#include "lovichilisteint.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

maillon_int* init_elt() {
    maillon_int* p_nv_elt = malloc(sizeof(maillon_int));
    if (p_nv_elt != NULL) {
        p_nv_elt->val = rand() % 21;
        p_nv_elt->p_suiv = NULL;
    }
    return p_nv_elt;
}

void ajout_tete_v2(maillon_int** p_p_tete, maillon_int* p_nv_elt) {
    p_nv_elt->p_suiv = *p_p_tete;
    *p_p_tete = p_nv_elt;
}

void inserer2(maillon_int** prem, maillon_int* e) {
    maillon_int* n, * prec;
    if (*prem == NULL || e->val <= (*prem)->val) {
        e->p_suiv = *prem;
        *prem = e;
    }
    else {
        n = prec = *prem;
        while (n != NULL && e->val > n->val) {
            prec = n;
            n = n->p_suiv;
        }
        e->p_suiv = n;
        prec->p_suiv = e;
    }
}

void supprimer_debut(maillon_int** prem) {
    if (*prem != NULL) {
        maillon_int* n = *prem;
        *prem = (*prem)->p_suiv;
        free(n);
    }
}

void critere_supp_un2(maillon_int** prem, int val) {
    maillon_int* e = *prem, * prec = NULL, * n;
    while (e != NULL) {
        n = NULL;
        if (e->val == val) {
            n = e;
            if (prec == NULL)
                *prem = e->p_suiv;
            else
                prec->p_suiv = e->p_suiv;
        }
        else
            prec = e;
        e = e->p_suiv;
        if (n != NULL)
            free(n);
    }
}

void detruire_liste2(maillon_int** prem) {
    while (*prem != NULL)
        supprimer_debut(prem);
}

void sauver_liste(maillon_int* prem) {
    FILE* f = fopen("saveliste.bin", "wb");
    if (f != NULL) {
        while (prem != NULL) {
            if (1 != fwrite(prem, sizeof(maillon_int), 1, f)) {
                fprintf(stderr, "Erreur d'écriture du maillon\n");
                break;
            }
            prem = prem->p_suiv;
        }
        fclose(f);
    }
    else {
        fprintf(stderr, "Erreur d'ouverture du fichier\n");
    }
}
void parcourir(maillon_int* p_tete)
{
    if (p_tete == NULL)
        printf("liste vide");
    else
        while (p_tete != NULL) {
            printf("%d--", p_tete->val);
            p_tete = p_tete->p_suiv;
        }
    putchar('\n');
}

maillon_int* load_liste() {
    FILE* f;
    maillon_int* prem = NULL, * p, e;
    if ((f = fopen("saveliste.bin", "rb")) != NULL) {
        prem = malloc(sizeof(maillon_int));
        fread(prem, sizeof(maillon_int), 1, f);
        p = prem;
        while (fread(&e, sizeof(maillon_int), 1, f)) {
            p->p_suiv = malloc(sizeof(maillon_int));
            p = p->p_suiv;
            *p = e;
            p->p_suiv = NULL;
        }
        fclose(f);
    }
    else {
        printf("Erreur ou fichier inexistant\n");
    }
    return prem;
}
