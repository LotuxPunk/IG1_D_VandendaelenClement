#include "General.h"

CodeErreur sauverJoueurs(Joueur *pDebJoueurs) {
	CodeErreur erreur = PAS_D_ERREUR;
	FILE *pFichier;
	fopen_s(&pFichier, NOMFICHIER, "wb");
	if (pFichier == NULL) {
		erreur = FICHIER_INEXISTANT;
	}
	else {
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
	}
}

CodeErreur chargerJoueurs(Joueur **pDebJoueur) {
	CodeErreur erreur;
	FILE *pFichier;
	fopen_s(&pFichier, NOMFICHIER, "rb");
	if (pFichier == NULL) {
		erreur = FICHIER_INEXISTANT;
	}
	else {
		Joueur *pJoueur = NULL, *pSauveJoueur = NULL, *pDebJoueur = NULL, *pNouvJoueur;
		Personnage *pPerso = NULL, *pSauvPerso, *pNouvPerso;
		JoueurFi joueur;
		PersoFi perso;
		bool allocationOk = true;
		fread_s(&joueur, sizeof(JoueurFi), 1, 1, pFichier);
		while (!EOF && allocationOk) {
			allocationOk = nouveauJoueur(&pNouvJoueur);
			if (!allocationOk) {
				erreur = ALLOCATION_MEMOIRE;
			}
			else {
				erreur = PAS_D_ERREUR;
				ajouteJoueur(&pDebJoueur, joueur.pseudo, pNouvJoueur, pJoueur, pSauveJoueur);
				pSauveJoueur = pNouvJoueur;
				pSauvPerso = NULL;
				int iPerso = 0;
				while (iPerso < joueur.nbrPerso && allocationOk) {
					allocationOk = nouveauPersonnage(&pNouvPerso);
					if (!allocationOk) {
						erreur = ALLOCATION_MEMOIRE;
					}
					else {
						erreur = PAS_D_ERREUR;
						fread_s(&perso, sizeof(PersoFi), 1, 1, pFichier);
						ajoutePersonnage(pJoueur, perso.nom, perso.points, pNouvPerso, pPerso, pSauvPerso);
						pSauvPerso = pNouvPerso;
						iPerso++;
					}
				}
				if (allocationOk) {
					fread_s(&joueur, sizeof(JoueurFi), 1, 1, pFichier);
				}
			}
		}
		fclose(pFichier);
	}
}

CodeErreur fichierExiste(void) {
	CodeErreur erreur = PAS_D_ERREUR;
	FILE *pFichier;
	fopen_s(&pFichier, NOMFICHIER, "rb");
	if (pFichier == NULL) {
		erreur = FICHIER_INEXISTANT;
	}
	else {
		fclose(pFichier);
	}
	return erreur;
}