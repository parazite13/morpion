#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>

#include "main.h"
#include "liste.h"
#include "affichage.h"
#include "ia.h"
#include "interface.h"

/* ----------------------------------------------------------------- */
/*                          Fonction IA                              */
/* ----------------------------------------------------------------- */

/* Fonction qui permet d'évaluer un noeud */
float evaluation(ptr_noeud noeud, int coups){

	int nbO = noeud->nbO;
	int nbX = noeud->nbX;

	if(coups % 2 == 0){
		if(noeud->nbO == 5) return 1;
		if(noeud->nbX == 5)	return 0.95;
		if(noeud->nbO == 4 && noeud->nbX == 4) return 0.90;
		if(noeud->nbO == 3 && noeud->nbX == 4) return 0.85;
		if(noeud->nbO == 2 && noeud->nbX == 4) return 0.80;
		if(noeud->nbO == 1 && noeud->nbX == 4) return 0.75;
		if(noeud->nbO == 4 && noeud->nbX == 3) return 0.70;
		if(noeud->nbO == 4 && noeud->nbX == 2) return 0.65;
		if(noeud->nbO == 4 && noeud->nbX == 1) return 0.60;
		if(noeud->nbO == 3 && noeud->nbX == 3) return 0.55;
		if(noeud->nbO == 3 && noeud->nbX == 2) return 0.50;
		if(noeud->nbO == 3 && noeud->nbX == 1) return 0.45;
		if(noeud->nbO == 2 && noeud->nbX == 3) return 0.40;
		if(noeud->nbO == 2 && noeud->nbX == 2) return 0.35;
		if(noeud->nbO == 2 && noeud->nbX == 1) return 0.30;
		if(noeud->nbO == 1 && noeud->nbX == 3) return 0.25;
		if(noeud->nbO == 1 && noeud->nbX == 2) return 0.20;
		if(noeud->nbO == 1 && noeud->nbX == 1) return 0.15;
	}else{
		if(noeud->nbX == 5) return -1;
		if(noeud->nbO == 5)	return -0.95;
		if(noeud->nbX == 4 && noeud->nbO == 4) return -0.90;
		if(noeud->nbX == 4 && noeud->nbO == 3) return -0.85;
		if(noeud->nbX == 4 && noeud->nbO == 2) return -0.80;
		if(noeud->nbX == 4 && noeud->nbO == 1) return -0.75;
		if(noeud->nbX == 3 && noeud->nbO == 4) return -0.70;
		if(noeud->nbX == 2 && noeud->nbO == 4) return -0.65;
		if(noeud->nbX == 1 && noeud->nbO == 4) return -0.60;
		if(noeud->nbX == 3 && noeud->nbO == 3) return -0.55;
		if(noeud->nbX == 3 && noeud->nbO == 2) return -0.50;
		if(noeud->nbX == 3 && noeud->nbO == 1) return -0.45;
		if(noeud->nbX == 2 && noeud->nbO == 3) return -0.40;
		if(noeud->nbX == 2 && noeud->nbO == 2) return -0.35;
		if(noeud->nbX == 2 && noeud->nbO == 1) return -0.30;
		if(noeud->nbX == 1 && noeud->nbO == 3) return -0.25;
		if(noeud->nbX == 1 && noeud->nbO == 2) return -0.20;
		if(noeud->nbX == 1 && noeud->nbO == 1) return -0.15;
	}

	return 0;

}

/* Fonction qui parcoure la liste des coups possibles et qui renvoie le meilleur noeud a jouer */
ptr_noeud meilleur_coup(ptr_liste liste, int coups){
	float meilleur, x;
	ptr_noeud noeud_a_renvoyer;

	if(coups % 2 == 0){
		meilleur = -1;
	}else{
		meilleur = 1;
	}

	while(liste != NULL){
		x = evaluation(liste->noeud, coups);
		liste->noeud->eval = x;

		if(coups % 2 == 0){
			if(x >= meilleur){
				meilleur = x;
				noeud_a_renvoyer = liste->noeud;
			}
		}else{
			if(x < meilleur){
				meilleur = x;
				noeud_a_renvoyer = liste->noeud;
			}
		}
		liste = liste->suivant;
		meilleur = noeud_a_renvoyer->eval;
	}
	
	return noeud_a_renvoyer;
}

/* La fonction qui permet d'actualiser la liste */
ptr_liste coup_possibles(ptr_noeud grille[N][N]){
	int i, j;
	ptr_noeud noeud;
	ptr_liste liste_possible = NULL;
	
	/* Puis on la remplie */
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			if(est_jouable(i+1, j+1, grille)){	// cf fonction est_jouable() pour les arguments + 1
				noeud = (ptr_noeud)malloc(sizeof(t_noeud));
				noeud->abs = i;
				noeud->ord = j;
				noeud->nbX = nombre_de_X(i, j, grille);
				noeud->nbO = nombre_de_O(i, j, grille);
				liste_possible = ajout_liste(liste_possible , noeud);
			}
		}
	}
		
	return liste_possible;
}

ptr_noeud nouveau_noeud(int abs, int ord, int nbX, int nbO, float eval){
	ptr_noeud noeud_a_renvoyer;

	noeud_a_renvoyer = (ptr_noeud)malloc(sizeof(t_noeud));
	noeud_a_renvoyer->abs = abs;
	noeud_a_renvoyer->ord = ord;
	noeud_a_renvoyer->nbX = nbX;
	noeud_a_renvoyer->nbO = nbO;
	noeud_a_renvoyer->eval = eval;
	
	return noeud_a_renvoyer;
}

/* Fonction qui parcourt l'arbre de jeu et qui renvoit l'evaluation de la meilleur feuille */
float parcours(ptr_noeud grille[N][N], int coups){

	ptr_liste liste_possible = coup_possibles(grille);
	ptr_noeud meilleur_courant = meilleur_coup(liste_possible, coups);
	ptr_noeud noeud_a_jouer;
	ptr_liste liste = liste_possible;

	/* Aucune anticipation */
	if(C == 0){
		dernier_coup = parcours_eval(liste, coups);
		dernier_coup = nouveau_noeud(dernier_coup->abs, dernier_coup->ord, dernier_coup->nbX, dernier_coup->nbO, dernier_coup->eval);
		liberer(liste);
		return evaluation(meilleur_courant,coups);
	}

	/* Maximun d'anticipation */
	if(coups == C){	
		liberer(liste);
		return evaluation(meilleur_courant,coups);
	}

	/* Etat Feuille */
	if(evaluation(meilleur_courant, coups) == 1){
		if(coups == 0){
			grille[meilleur_courant->abs][meilleur_courant->ord]->symb = 'O';
		}
		liberer(liste);
		return 1;
	}else
	if(evaluation(meilleur_courant, coups) == -1){
		liberer(liste);
		return -1;
	}

	/* Cas général */
	else{
		while(liste_possible != NULL){
			modifier(grille, liste_possible->noeud, coups);
			liste_possible->noeud->eval = parcours(grille, coups + 1);

			grille[liste_possible->noeud->abs][liste_possible->noeud->ord]->symb = ' ';

			liste_possible = liste_possible->suivant;
		}

		noeud_a_jouer = parcours_eval(liste, coups);

		/* Cas final avant de sortir de la fonction */
		if(coups == 0){
			dernier_coup = parcours_eval(liste, coups);
			dernier_coup = nouveau_noeud(dernier_coup->abs, dernier_coup->ord, dernier_coup->nbX, dernier_coup->nbO, dernier_coup->eval);
		}

		liberer(liste);

		return noeud_a_jouer->eval;	
	}
}

void tempo(void){
	float x = 0;
	while(x < 50000){
		x = x + 0.003;
	}
	aff_grille(grille);
	return;
}

/* Fonction qui parcourt l'arbre de jeu et qui renvoit l'evaluation de la meilleur feuille en utilisant l'optimisation alpha-beta */
float alpha_beta(ptr_noeud grille[N][N], int coups, float alpha, float beta){

	ptr_liste liste_possible = coup_possibles(grille);
	ptr_noeud meilleur_courant = meilleur_coup(liste_possible, coups);
	ptr_liste liste = liste_possible;
	float val;

	if(coups == C){
		liberer(liste);
		return meilleur_courant->eval;

	}else{

		/* Etat Feuille */
		if(meilleur_courant->eval == 1){

			/* Coup gagnant pour l'ordi */
			if(coups == 0){
				dernier_coup = nouveau_noeud(meilleur_courant->abs, meilleur_courant->ord, meilleur_courant->nbX, meilleur_courant->nbO, meilleur_courant->eval);
			}
			liberer(liste);
			return 1 - (float)coups/200;	// Pour gagner le plus tot possible
		}
	
		if(meilleur_courant->eval == -1){
			liberer(liste);
			return -1 + (float)coups/200;	// Pour perdre le plus tard possible
		}

		/* Cas général */
		if(coups % 2 == 1){
			val = 2;
			while(liste_possible != NULL){

				modifier(grille, liste_possible->noeud, coups);
//				tempo();
				val = min_float(val, liste_possible->noeud->eval = alpha_beta(grille, coups+1, alpha, beta));
				grille[liste_possible->noeud->abs][liste_possible->noeud->ord]->symb = ' ';

				/* Coupure Alpha */
				if(alpha >= val){
					liberer(liste);
					return val;
				}

				beta = min_float(beta,val);
				liste_possible = liste_possible->suivant;
			}
		}else{
			val = -2;
			while(liste_possible != NULL){

				modifier(grille, liste_possible->noeud, coups);
//				tempo();
				val = max_float(val, liste_possible->noeud->eval = alpha_beta(grille, coups+1, alpha, beta));
				grille[liste_possible->noeud->abs][liste_possible->noeud->ord]->symb = ' ';

				/* Coupure Beta */
				if(val >= beta){
					liberer(liste);
					return val;
				}

				alpha = max_float(alpha,val);
				liste_possible = liste_possible->suivant;
			}
		}

		/* Cas final avant de sortir de la fonction */
		if(coups == 0){
			dernier_coup = parcours_eval(liste, coups);
			dernier_coup = nouveau_noeud(dernier_coup->abs, dernier_coup->ord, dernier_coup->nbX, dernier_coup->nbO, dernier_coup->eval);
			val = dernier_coup->eval;
//			afficher_liste(liste);
		}

		liberer(liste);
		return val;
	}

}

/* Fonction qui parcourt un étage de l'arbre de jeu et qui renvoit le meilleur noeud */
ptr_noeud parcours_eval(ptr_liste liste, int coups){

	int i, j;
	ptr_noeud noeud_a_renvoyer = liste->noeud;
	int n;

	if(coups % 2 == 0){
		while(liste != NULL){n=0;

			/* Si le dernier coup a été joué à proximité on augmente la valeur de l'évaluation */
			for(i=-1; i<=1; i++){
				for(j=-1; j<=1; j++){
					if((liste->noeud->abs + i >= 0) && (liste->noeud->ord + j >=0) && (liste->noeud->abs + i < N) && (liste->noeud->ord + j < N)){
						if(dernier_coup->abs == liste->noeud->abs + i && dernier_coup->ord == liste->noeud->ord + j){
							liste->noeud->eval = liste->noeud->eval + 0.03;
						}
					}
				}
			}

			/* On augmente l'evaluation en fonction du nombre de croix placé */
			i = 0;
			n = nombre_de_X(liste->noeud->abs, liste->noeud->ord, grille);
			while(i<=n){
				liste->noeud->eval = liste->noeud->eval + 0.005;
				i = i + 1;
			}



			if(liste->noeud->eval > noeud_a_renvoyer->eval){
				noeud_a_renvoyer = liste->noeud;
			}

			liste = liste->suivant;
		}

		return noeud_a_renvoyer;

	}else{
		return meilleur_coup(liste, coups);
	}

}

/* Fonction qui place un symbole en fonction du coup actuel */
void modifier(ptr_noeud grille[N][N], ptr_noeud meilleur, int coups){

	/* Tour de l'ordinateur */
	if(coups % 2 == 0){
		grille[meilleur->abs][meilleur->ord]->symb = 'O';
	}

	/* Tour du joueur */
	else{
		grille[meilleur->abs][meilleur->ord]->symb = 'X';
	}

	return;
}


/* La fonction qui renvoie le maximun entre 2 entiers */
int max(int x, int y){
	if(x>y) return x;
	else return y;
}

/* La fonction qui renvoie le maximun entre 2 flottants */
float max_float(float x, float y){
	if(x>y) return x;
	else return y;
}

/* La fonction qui renvoie le minimun entre 2 flottants */
float min_float(float x, float y){
	if(x<y) return x;
	else return y;
}

/* La fonction qui permet de compter le nombre de symboles X consécutifs si on place un X a ligne i et colonne j */
int nombre_de_X(int i, int j, ptr_noeud grille[N][N]){
	int abs = i;
	int ord = j;
	int compt1=1, compt2=1, compt3=1, compt4=1;

	char ancien_symbole = grille[abs][ord]->symb;
	
	grille[abs][ord]->symb = 'X';
	
	/* Parcours vertical */
	while(i-1>=0 && grille[i-1][j]->symb == 'X'){
		i = i - 1;
	}
	while(i+1<N && grille[i+1][j]->symb == 'X'){
		compt1 = compt1 + 1;
		i = i + 1;
	}
	
	/* Parcours diagonale haut droite / bas gauche */
	i = abs;
	j = ord;
	while(i-1>=0 && j+1<N && grille[i-1][j+1]->symb == 'X'){
		i = i - 1;
		j = j + 1;
	}
	while(i+1<N && j-1>=0 && grille[i+1][j-1]->symb == 'X'){
		compt2 = compt2 + 1;
		i = i + 1;
		j = j - 1;
	}	

	/* Parcours horizontal */
	i = abs;
	j = ord;
	while(j-1>=0 && grille[i][j-1]->symb == 'X'){
		j = j - 1;
	}
	while(j+1<N && grille[i][j+1]->symb == 'X'){
		compt3 = compt3 + 1;
		j = j + 1;
	}

	/* Parcours diagonale haut gauche / bas droite */
	i = abs;
	j = ord;
	while(i-1>=0 && j-1>=0 && grille[i-1][j-1]->symb == 'X'){
		i = i - 1;
		j = j - 1;
	}
	while(i+1<N && j+1<N && grille[i+1][j+1]->symb == 'X'){
		compt4 = compt4 + 1;
		i = i + 1;
		j = j + 1;
	}	
	
	grille[abs][ord]->symb = ancien_symbole;
	
	return max(compt1,max(compt2,max(compt3,compt4)));
}

/* La fonction qui permet de compter le nombre de symboles O consécutifs si on place un O a ligne i et colonne j */
int nombre_de_O(int i, int j, ptr_noeud grille[N][N]){
	int abs = i;
	int ord = j;
	int compt1=1, compt2=1, compt3=1, compt4=1;

	char ancien_symbole = grille[abs][ord]->symb;
	
	grille[abs][ord]->symb = 'O';	
	
	/* Parcours vertical */
	while(i-1>=0 && grille[i-1][j]->symb == 'O'){
		i = i - 1;
	}
	while(i+1<N && grille[i+1][j]->symb == 'O'){
		compt1 = compt1 + 1;
		i = i + 1;
	}
	
	/* Parcours diagonale haut droite / bas gauche */
	i = abs;
	j = ord;
	while(i-1>=0 && j+1<N && grille[i-1][j+1]->symb == 'O'){
		i = i - 1;
		j = j + 1;
	}
	while(i+1<N && j-1>=0 && grille[i+1][j-1]->symb == 'O'){
		compt2 = compt2 + 1;
		i = i + 1;
		j = j - 1;
	}	
	
	/* Parcours horizontal */
	i = abs;
	j = ord;
	while(j-1>=0 && grille[i][j-1]->symb == 'O'){
		j = j - 1;
	}
	while(j+1<N && grille[i][j+1]->symb == 'O'){
		compt3 = compt3 + 1;
		j = j + 1;
	}
	
	/* Parcours diagonale haut gauche / bas droite */
	i = abs;
	j = ord;
	while(i-1>=0 && j-1>=0 && grille[i-1][j-1]->symb == 'O'){
		i = i - 1;
		j = j - 1;
	}
	while(i+1<N && j+1<N && grille[i+1][j+1]->symb == 'O'){
		compt4 = compt4 + 1;
		i = i + 1;
		j = j + 1;
	}	
	
	grille[abs][ord]->symb = ancien_symbole;
	
	return max(compt1,max(compt2,max(compt3,compt4)));
}