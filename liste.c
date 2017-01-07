#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>

#include "main.h"
#include "liste.h"
#include "affichage.h"

/* ----------------------------------------------------------------- */
/*                       Fonctions listes                            */
/* ----------------------------------------------------------------- */

/* La fonction qui permet d'ajouter un maillon en tete de liste */
ptr_liste ajout_liste(ptr_liste liste, ptr_noeud x){
	ptr_liste ptr;
	
	ptr = (t_liste*)malloc(sizeof(t_liste));
	ptr->noeud = x;
	ptr->suivant = liste;
	return ptr;
}

/* Fonction qui libere de la memoire une liste */
void liberer(ptr_liste liste){
	ptr_liste liste_a_detruire;
	ptr_liste suivant;

	liste_a_detruire = liste;
	while(liste_a_detruire != NULL){
		suivant = liste_a_detruire->suivant;
		free(liste_a_detruire->noeud);
		free(liste_a_detruire);
		liste_a_detruire = suivant;
	}

	return;
}