 /*
 * Polytech Marseille
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de Polytech Marseille.
 * Il ne peut etre reproduit, utilise ou modifie sans l'avis
 * express de ses auteurs.
 */

/* @author MONNOT Alexandre <alexandre.monnot@etu.univ-amu.fr>
 * @author PAOLI Vincent <vincent.paoli.1@etu.univ-amu.fr>

 * @version 3.3.2 / 18/02/2016
 * @todo 
 * @bug
 */

/* Ce programme simule un jeu de morpion modifié.
 * Il comporte une IA capable d'anticiper un nombre C de coups de l'utilisateurs
 *
 */
 
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
/*                             MAIN                                  */
/* ----------------------------------------------------------------- */ 

int main(void){

	int gagnant;
	
	printf("\033[H\033[J");		//	On clear la console
	init_grille();
	aff_grille(grille);
	
	while(1){

		/* Tour de l'utilisateur */

		insert_util(grille);

		if(partie_terminee(grille)){
			gagnant = 1;
			printf("\033[H\033[J");   //  On clear la console
			aff_grille(grille); 
			break;
		}


		/* Tour de l'IA */

//		printf("EVALUATION: %f\n",parcours(grille, 0));
 		printf("EVALUATION DU MEILLEUR COUP: %f\n",alpha_beta(grille, 0, -2, 2) ); 

		grille[dernier_coup->abs][dernier_coup->ord]->symb = 'O';
		printf("\033[H\033[J");   //  On clear la console
		aff_grille(grille); 
		printf("L'ordinateur a joué en: (%i, %i)\n",dernier_coup->abs+1,dernier_coup->ord+1);

		free(dernier_coup);

		if(partie_terminee(grille)){
			gagnant = 0;
			break;
		}
	}
	
	if(gagnant){
		printf("VOUS AVEZ GAGNE !\n");
	}else{
		printf("Désolé vous avez perdu...\n");
	}
	
return 0;
}
