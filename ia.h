/* ----------------------------------------------------------------- */
/*                           Header IA                               */
/* ----------------------------------------------------------------- */

float evaluation(ptr_noeud noeud, int coups);
ptr_noeud parcours_eval(ptr_liste liste, int coups);
ptr_noeud meilleur_coup(ptr_liste liste, int coups);
ptr_liste coup_possibles(ptr_noeud grille[N][N]);
float parcours(ptr_noeud grille[N][N], int coups);
float alpha_beta(ptr_noeud grille[N][N], int coups, float alpha, float beta);
int nombre_de_X(int i, int j, ptr_noeud grille[N][N]);
int nombre_de_O(int i, int j, ptr_noeud grille[N][N]);

void modifier(ptr_noeud grille[N][N], ptr_noeud meilleur, int coups);
ptr_noeud nouveau_noeud(int abs, int ord, int nbX, int nbO, float eval);
int max(int x, int y);
float max_float(float x, float y);
float min_float(float x, float y);
void tempo(void);