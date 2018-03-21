#include "General.h"

bool joueurExiste(Joueur * pDebJoueur, char * pseudo, Joueur * pJoueur, Joueur * pSauvJoueur) {
	pJoueur = pDebJoueur;
	while (pJoueur != NULL && strcmp(pseudo, pJoueur->pseudo)) {
		pSauvJoueur = pJoueur;
		pJoueur = pJoueur->pSuiv;
	}
	return pJoueur != NULL && strcmp(pseudo, pJoueur->pseudo);
}

bool nouveauJoueur(Joueur *pNouvJoueur) {
	pNouvJoueur = (Joueur*)calloc(1, sizeof(Joueur));
	return pNouvJoueur != NULL;
}

bool nouveauPersonnage(Personnage * pNouvPerso)
{
	pNouvPerso = (Personnage*)calloc(1, sizeof(Personnage));
	return pNouvPerso != NULL;
}

void libereJoueur(Joueur *pJoueur) {
	free(pJoueur);
}

void libèrePersonnage(Personnage * pPerso) {
	free(pPerso);
}

void ajouteJoueur(Joueur * pDebJoueur, char * pseudo, Joueur * pNouvJoueur, Joueur * pJoueur, Joueur * pSauvJoueur) {
	strcpy_s(pNouvJoueur->pseudo, NBCARMAXPERSONNAGE,pseudo);
	pNouvJoueur->pDebPersonnages = NULL;
	if (pJoueur == pDebJoueur) {
		pDebJoueur = pNouvJoueur;
	}
	else {
		pSauvJoueur->pSuiv = pJoueur;
	}
	pNouvJoueur->pSuiv = pJoueur;
}

