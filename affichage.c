
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>

#include "main.h"
#include "liste.h"
#include "affichage.h"

/* ----------------------------------------------------------------- */
/*                       Fonction affichage                          */
/* ----------------------------------------------------------------- */

/* Cette fonction permet d'afficher la grille au complet (bordures + symboles) */
void aff_grille(ptr_noeud grille[N][N]){
	int i, j;	// Les indices des boucles ligne, colonne
	int ord;	// Numéro de la ligne affiché
	
	/* Affichage des abscisses */
	printf("\n   ");	// Décalage pour les ordonnées
	for(j=1; j<N+1; j++){
		if(j<10){
			printf("  %i ",j);
		}else{
			printf(" %i ",j);
		}
	}
	printf("\n");
	
	/* Boucle sur les lignes */
	for(i=0; i<N; i++){
		
		/* Boucle pour les traits horizontaux */
		printf("   ");	// Décalage pour les ordonnées
		for(j=0; j<4*N+1; j++){
			printf("-");	// 
		}
		printf("\n");
		
		/* Affichage des ordonnées */
		ord = i+1;
		if(ord<10){
			printf("%i  ",ord);
		}else{
			printf("%i ",ord);
		}
		/* Boucle pour affichage des symboles et des traits verticaux */
		for(j=0; j<N; j++){
			printf("| %c ",grille[i][j]->symb);
		}
		printf("|\n");
	}
	
	/* Affichage du dernier trait horizontal */
	printf("   ");	// Décalage pour les ordonnées
	for(j=0; j<4*N+1; j++){
		printf("-");
	}
	printf("\n");
	
	return;
}

/* La fonction qui permet d'afficher tous les maillon de la liste en parametre */
void afficher_liste(ptr_liste liste){

	printf("Affichage de la liste : \n");
	if(liste == NULL){
		printf("La liste est vide !\n");
	}else{
		while(liste != NULL){
			printf("(%i, %i, %f)\n", liste->noeud->abs+1, liste->noeud->ord+1, liste->noeud->eval);
			liste = liste->suivant;
		}
	}
	
	return;
}