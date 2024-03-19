#include "lovichilisteint.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

int menu() {
    int choix = 0;
    printf("1 Creer une liste d'entiers compris entre 0 et 20 de taille aleatoire comprise entre 1 et 20\n"
        "2 Ajouter un élément entier aléatoire (compris entre 0 et 20) en tête de liste\n"
        "3 Inserer un élément entier aléatoire dans sa place dans la liste suivant l'ordre croissant des premiers éléments\n"
        "4 Supprimer l'élément de tête\n"
        "5 Supprimer tous les maillons d'une valeur donnee\n"
        "6 Detruire liste\n"
        "7 Sauver la liste courante en binaire dans le fichier \"saveliste.bin\"\n"
        "8 Charger une liste depuis le fichier \"savelist.bin\"\n");

    scanf("%d", &choix);
    rewind(stdin);

    return choix;
}

int main() {
    maillon_int* premier = NULL;
    int fin = 0;
    int i, nb;

    srand((unsigned)time(NULL));
    while (!fin) {
        i = menu();
        switch (i) {

        case 1: // Creer une liste de taille aleatoire
            premier = init_elt();
            parcourir(premier);
            break;

        case 2: // Ajouter un element en tete de liste
            ajout_tete_v2(&premier, init_elt());
            parcourir(premier);

            break;

        case 3: // Inserer un element dans sa place dans la liste suivant l'ordre croissant
            inserer2(&premier, init_elt());
            parcourir(premier);

            break;

        case 4: // Supprimer l'element de tete
            supprimer_debut(&premier);
            parcourir(premier);

            break;

        case 5: // Supprimer tous les maillons d'une valeur donnee
            scanf("%d", &nb);
            critere_supp_un2(&premier, nb);
            parcourir(premier);

            break;

        case 6: // Detruire liste
            detruire_liste2(&premier);
            parcourir(premier);

            break;

        case 7: // Sauver la liste courante en binaire dans le fichier "saveliste.bin"
            sauver_liste(premier);
            parcourir(premier);

            break;

        case 8: // Charger une liste depuis le fichier "savelist.bin"
            premier = load_liste();
            parcourir(premier);

            break;

        default:
            fin = 1; // Sortir de la boucle si le choix n'est pas valide
            break;
        }
    }

    // Libérer la mémoire avant de quitter
    detruire_liste2(&premier);

    return 0;
}
