#include "General.h"

bool joueurExiste(Joueur * pDebJoueur, char * pseudo, Joueur ** ppJoueur, Joueur ** ppSauvJoueur) {
	Joueur *pJoueur = pDebJoueur;
	while (pJoueur != NULL && strcmp(pseudo, pJoueur->pseudo)) {
		*ppSauvJoueur = pJoueur;
		pJoueur = pJoueur->pSuiv;
	}
	*ppJoueur = pJoueur;
	return pJoueur != NULL && strcmp(pseudo, pJoueur->pseudo);
}

bool personnageExiste(Joueur * pJoueur, char * nom, Personnage * pPerso, Personnage * pSauvPerso) {
	pPerso = pJoueur->pDebPersonnages;
	while (pPerso != NULL && strcmp(nom, pPerso->nom)) {
		pSauvPerso = pPerso;
		pPerso = pPerso->pSuiv;
	}
	return pPerso != NULL && strcmp(nom, pPerso->nom);
}

bool nouveauJoueur(Joueur ** ppNouvJoueur) {
	*ppNouvJoueur = (Joueur*)calloc(1, sizeof(Joueur));
	return *ppNouvJoueur != NULL;
}

bool nouveauPersonnage(Personnage ** ppNouvPerso)
{
	*ppNouvPerso = (Personnage*)calloc(1, sizeof(Personnage));
	return *ppNouvPerso != NULL;
}

void libereJoueur(Joueur *pJoueur) {
	free(pJoueur);
}

void liberePersonnage(Personnage * pPerso) {
	free(pPerso);
}

void ajouteJoueur(Joueur ** ppDebJoueur, char * pseudo, Joueur * pNouvJoueur, Joueur * pJoueur, Joueur * pSauvJoueur) {
	strcpy_s(pNouvJoueur->pseudo, NBCARMAXJOUEUR,pseudo);
	pNouvJoueur->pDebPersonnages = NULL;
	if (pJoueur == *ppDebJoueur) {
		*ppDebJoueur = pNouvJoueur;
	}
	else {
		pSauvJoueur->pSuiv = pJoueur;
	}
	pNouvJoueur->pSuiv = pJoueur;
}

void ajoutePersonnage(Joueur * pJoueur, char * nom, int points, Personnage * pNouvPerso, Personnage * pPerso, Personnage * pSauvPerso) {
	strcpy_s(pNouvPerso->nom,NBCARMAXPERSONNAGE, nom);
	pNouvPerso->points = points;
	pNouvPerso->pSuiv = NULL;

	if (pJoueur->pDebPersonnages == NULL) {
		pJoueur->pDebPersonnages = pNouvPerso;
	}
	else {
		pSauvPerso->pSuiv = pNouvPerso;
	}
}

void supprimeJoueur(Joueur ** ppDebJoueur, Joueur * pJoueur, Joueur * pSauvJoueur) {
	Personnage *pPerso, *pSauvPerso;
	pPerso = pJoueur->pDebPersonnages;
	while (pPerso != NULL) {
		pSauvPerso = pPerso->pSuiv;
		liberePersonnage(pPerso);
		pPerso = pSauvPerso;
	}

	if (pJoueur = *ppDebJoueur) {
		*ppDebJoueur = pJoueur->pSuiv;
	}
	else {
		pSauvJoueur->pSuiv = pJoueur->pSuiv;
	}
	libereJoueur(pJoueur);
}

