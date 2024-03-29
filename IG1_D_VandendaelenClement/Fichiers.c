#include "General.h"

CodeErreur sauverJoueurs(Joueur *pDebJoueurs) {
	FILE *pFichier;
	fopen_s(&pFichier, NOMFICHIER, "wb");

	if (pFichier == NULL) {
		return FICHIER_INEXISTANT;
	}

	Joueur *pJoueur = pDebJoueurs;
	Personnage *pPerso;
	JoueurFi joueur;
	PersoFi perso;

	while (pJoueur != NULL) {
		strcpy_s(joueur.pseudo, NBCARMAXJOUEUR, pJoueur->pseudo);
		joueur.nbrPerso = nbPersonnages(pJoueur);
		fwrite(&joueur, 1,sizeof(joueur),pFichier);
		pPerso = pJoueur->pDebPersonnages;

		while (pPerso != NULL) {
			strcpy_s(perso.nom, NBCARMAXPERSONNAGE, pPerso->nom);
			perso.points = pPerso->points;
			fwrite(&perso, 1, sizeof(perso), pFichier);
			pPerso = pPerso->pSuiv;
		}

		pJoueur = pJoueur->pSuiv;
	}
	fclose(pFichier);
	return PAS_D_ERREUR;
}

CodeErreur chargerJoueurs(Joueur **pDebJoueurs) {
	FILE *pFichier;
	fopen_s(&pFichier, NOMFICHIER, "rb");
	if (pFichier == NULL) {
		return FICHIER_INEXISTANT;
	}

	Joueur *pJoueur = NULL, *pSauveJoueur = NULL, *pNouvJoueur;
	*pDebJoueurs = NULL;
	Personnage *pPerso = NULL, *pSauvPerso, *pNouvPerso;
	JoueurFi joueur;
	PersoFi perso;
	bool allocationOk = true;
	fread_s(&joueur, sizeof(JoueurFi), sizeof(JoueurFi), 1, pFichier);

	while (!feof(pFichier) && allocationOk) {
		allocationOk = nouveauJoueur(&pNouvJoueur);

		if (!allocationOk) {
			return ALLOCATION_MEMOIRE;
		}

		ajouteJoueur(pDebJoueurs, joueur.pseudo, pNouvJoueur, pJoueur, pSauveJoueur);
		pSauveJoueur = pNouvJoueur;
		pSauvPerso = NULL;
		int iPerso = 0;

		while (iPerso < joueur.nbrPerso && allocationOk) {
			allocationOk = nouveauPersonnage(&pNouvPerso);

			if (!allocationOk) {
				return ALLOCATION_MEMOIRE;
			}
				
			fread_s(&perso, sizeof(PersoFi), sizeof(PersoFi), 1, pFichier);
			ajoutePersonnage(pNouvJoueur, perso.nom, perso.points, pNouvPerso, pPerso, pSauvPerso);
			pSauvPerso = pNouvPerso;
			iPerso++;
		}
		if (allocationOk) {
			fread_s(&joueur, sizeof(JoueurFi), sizeof(JoueurFi), 1, pFichier);
		}
	}
	fclose(pFichier);
	return PAS_D_ERREUR;
}

CodeErreur fichierExiste(void) {
	FILE *pFichier;
	fopen_s(&pFichier, NOMFICHIER, "rb");
	if (pFichier == NULL) {
		return FICHIER_INEXISTANT;
	}
	fclose(pFichier);
	return PAS_D_ERREUR;
}