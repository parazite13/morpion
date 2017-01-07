/* ----------------------------------------------------------------- */
/*                        Header interface                           */
/* ----------------------------------------------------------------- */

void init_grille(void);
void insert_util(ptr_noeud grille[N][N]);
int est_jouable(int ligne, int colonne, ptr_noeud grille[N][N]);
int partie_terminee(ptr_noeud grille[N][N]);