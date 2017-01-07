/* ----------------------------------------------------------------- */
/*                          Header main                              */
/* ----------------------------------------------------------------- */

#define N 19					// Taille de la grille (NxN)
#define C 4						// Nombre de coups que l'IA anticipe (i.e difficulté)

/* ----------------------------------------------------------------- */
/*                       Structure listes                            */
/* ----------------------------------------------------------------- */

typedef struct mm1{				// Structure d'un noeud
	char symb;					// Symbole du noeud courant
	int abs;					// Abscisse du noeud courant
	int ord;					// Ordonne du noeud courant
	int nbX;					// Nombre de X consécutifs si un X est joué
	int nbO;					// Nombre de O consécutifs si un O est joué
	float eval;					// Evaluation du noeud
}t_noeud, *ptr_noeud;

typedef struct mm2{				// Structure de la liste
	ptr_noeud noeud;			// Pointeur sur un noeud 
	struct mm2 *suivant;		// Pointeur sur l'élément suivant
}t_liste, *ptr_liste;

ptr_noeud grille[N][N];
ptr_noeud dernier_coup;