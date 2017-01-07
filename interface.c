#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>

#include "main.h"
#include "interface.h"


/* ----------------------------------------------------------------- */
/*                       Fonction interface                          */
/* ----------------------------------------------------------------- */

/* Fonction d'initialisation de la grille contenant les symboles */
void init_grille(void){
	int i, j;	// Les indices des boucles ligne, colonne
	
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			grille[i][j] = (ptr_noeud)malloc(sizeof(t_noeud));
			grille[i][j]->symb = ' ';
		}
	}
	
	grille[N/2][N/2]->symb = 'O';
	
	return;
}

/* Fonction qui permet d'insérer un symbole dans la grille pour l'utilisateur */ 
void insert_util(ptr_noeud grille[N][N]){
	int ligne, colonne;
	ptr_noeud noeud_joue;

	printf("Veuillez saisir les coordonnées du symbole à jouer\n");
	do{
		printf("Ligne:");
		scanf("%i", &ligne);
		printf("Colonne:");
		scanf("%i", &colonne);
		if(!est_jouable(ligne, colonne, grille)){
			printf("PLACEMENT IMPOSSIBLE !!\nVeuillez réesayer\n");
		}
	}while(!est_jouable(ligne, colonne, grille));
	
	noeud_joue = grille[ligne-1][colonne-1];
	noeud_joue->symb = 'X';
	noeud_joue->abs = ligne-1;
	noeud_joue->ord = colonne-1;

	dernier_coup = nouveau_noeud(noeud_joue->abs, noeud_joue->ord, noeud_joue->nbX, noeud_joue->nbO, noeud_joue->eval);
	
	return;
}

/* Fonction qui renvoie vrai si la case passée en parametre est une case candidate */
/* LA CASE PREND EN COMPTES LES LIGNES ET COLONNES PAR RAPPORT A L'AFFICHAGE DE LA GRILLE */
int est_jouable(int ligne, int colonne, ptr_noeud grille[N][N]){
	int i, j;
	
	/* Si la case est occupée: ERREUR */
	if(grille[ligne-1][colonne-1]->symb != ' ') return 0;
	
	/* Si la case est en dehors de la grille: ERREUR */
	if(ligne < 1 || ligne > N || colonne < 1 || colonne > N) return 0;
	/* S'il n'y a pas de symbole a cote */
	for(i=0; i<3; i++){	// Boucle sur les lignes voisines
		for(j=0; j<3; j++){	// Boucle sur les colonnes voisines
			if((ligne - i >= 0) && (colonne - j >=0) && (ligne - i < N) && (colonne - j < N)){	// Si la case appartient a la grille
				if(grille[ligne-i][colonne-j]->symb == 'X' || grille[ligne-i][colonne-j]->symb == 'O'){	// Si la case est occupée
					return 1;
				}
			}
		}
	}
	
	return 0;
}

/* Fonction qui renvoie vrai si la partie est terminée */
int partie_terminee(ptr_noeud grille[N][N]){
	int i, j, k;
	int comptO_hor = 0, comptX_hor = 0; // compteur de symboles alignés
	int comptO_ver = 0, comptX_ver = 0; 
	int comptO_diag = 0, comptX_diag = 0;

	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
		
			/* On vérifie les alignements horizontaux */
			if(grille[i][j]->symb == 'X'){
				comptO_hor = 0;
				comptX_hor = comptX_hor + 1;
			}else if(grille[i][j]->symb == 'O'){
				comptX_hor = 0;
				comptO_hor = comptO_hor + 1;
			}else if(grille[i][j]->symb == ' '){
				comptO_hor = 0;
				comptX_hor = 0;
			}
			if(comptX_hor == 5 || comptO_hor == 5){
				return 1;
			}
			
			/* On vérifie les alignements verticaux */
			if(grille[j][i]->symb == 'X'){
				comptO_ver = 0;
				comptX_ver = comptX_ver + 1;
			}else if(grille[j][i]->symb == 'O'){
				comptX_ver = 0;
				comptO_ver = comptO_ver + 1;
			}else if(grille[j][i]->symb == ' '){
				comptO_ver = 0;
				comptX_ver = 0;
			}
			if(comptX_ver == 5 || comptO_ver == 5){
				return 1;
			}
		}
	}

	/* On vérifie la diagonale de en haut à gauche vers en bas à droite */
	for(i=0; i<N-5; i++){
		for(j=0; j<N-5; j++){
			for(k=0; k<5; k++){
				if(grille[k+i][k+j]->symb == 'X'){
					comptX_diag = comptX_diag + 1;
					comptO_diag = 0;
				}else if(grille[k+i][k+j]->symb == 'O'){
					comptO_diag = comptO_diag + 1;
					comptX_diag = 0;
				}else if(grille[k+i][k+j]->symb == ' '){
					comptX_diag = 0;
					comptO_diag = 0;
				}

				if(comptX_diag == 5 || comptO_diag == 5){
					return 1;
				}
			}

			comptX_diag = 0;
			comptO_diag = 0;
		}
	}



	/* On vérifie la diagonale de en haut à droite vers en bas à gauche */
	for(i=0; i<N+1-5; i++){
		for(j=5-1; j<N-1; j++){
			for(k=0; k<N-i; k++){
				if(grille[k+i][j-k]->symb == 'X'){
					comptX_diag = comptX_diag + 1;
					comptO_diag = 0;
				}else if(grille[k+i][j-k]->symb == 'O'){
					comptO_diag = comptO_diag + 1;
					comptX_diag = 0;
				}else if(grille[k+i][j-k]->symb == ' '){
					comptX_diag = 0;
					comptO_diag = 0;
				}
				if(comptX_diag == 5 || comptO_diag == 5){
					return 1;
				}
			}
		}
	}

	return 0;
}