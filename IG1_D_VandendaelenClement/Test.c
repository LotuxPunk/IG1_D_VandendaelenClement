//VANDENDAELEN Clément 1 IG D

#include "General.h"
#define NOM_FICHIER_PARTIES "FiParties.dat"

//typedef enum codeErreur CodeErreur;
//enum codeErreur {
//	PAS_D_ERREUR = 0,
//	JOUEUR_EXISTANT,
//	ALLOCATION_MEMOIRE,
//	MAUVAIS_CHOIX,
//	PSEUDO_NON_VALIDE,
//	JOUEUR_DEJA_PRESENT,
//	PERSONNAGE_DEJA_PRESENT,
//	JOUEUR_ABSENT,
//	FICHIER_INEXISTANT,
//	PERSONNAGE_ABSENT,
//	OUVERTURE_FICHIER = 102
//};

//typedef struct personnage Personnage;
//struct personnage {
//	char nom[NBCARMAXPERSONNAGE];
//	int points;
//	Personnage *pSuiv;
//};

//typedef struct joueur Joueur;
//struct joueur {
//	char pseudo[NBCARMAXJOUEUR];
//	Personnage *pDebPersonnages;
//	Joueur *pSuiv;
//};

typedef struct partie Partie;
struct partie {
	char gagnant[NBCARMAXJOUEUR];
	char perdant[NBCARMAXJOUEUR];
	char personnage[NBCARMAXPERSONNAGE];
};

CodeErreur creationListePlusDePersonnage(Joueur *pDebJoueurs, Joueur **pDebSansPersonnage);
CodeErreur ajoutSansPersonnage(Joueur **pDebSansPersonnages, char perdant[]);
void retraitPersonnage(Joueur **pJoueur, Personnage *pPerso, Personnage **pSauvePerso);
CodeErreur transfertPersonnage(Joueur * pJoueur, char nom[], int points, Personnage * pPerso, Personnage * pSauvPerso);

CodeErreur creationListePlusDePersonnage(Joueur * pDebJoueurs, Joueur ** pDebSansPersonnage) {
	(*pDebSansPersonnage) = NULL;
	FILE *pFichier;
	CodeErreur erreur;
	Partie partie;
	Joueur *pJoueur = NULL, *pSauveJoueur = NULL;
	Personnage *pPerso = NULL, *pSauvPerso, *pPersonnageTransfert;

	fopen_s(&pFichier, NOM_FICHIER_PARTIES, "rb");
	if (pFichier == NULL)
		return FICHIER_INEXISTANT;

	fread_s(&partie, sizeof(Partie), sizeof(Partie), 1, pFichier);

	while (!feof(pFichier)) {
		if (!joueurExiste(pDebJoueurs, partie.perdant, &pJoueur, &pSauveJoueur))
			return JOUEUR_ABSENT;
		if (!personnageExiste(pJoueur, partie.personnage, &pPerso, &pSauvPerso))
			return PERSONNAGE_ABSENT;
		retraitPersonnage(&pJoueur, pPerso, &pSauvPerso);
		pPersonnageTransfert = pPerso;

		if (pJoueur->pDebPersonnages == NULL)
			erreur = ajoutSansPersonnage(pDebSansPersonnage, partie.perdant);

		if (!joueurExiste(pDebJoueurs, partie.gagnant, &pJoueur, &pSauveJoueur))
			return JOUEUR_ABSENT;

		personnageExiste(pJoueur, partie.personnage, &pPerso, &pSauvPerso);
		transfertPersonnage(pJoueur, pPersonnageTransfert->nom, pPersonnageTransfert->points, pPerso, pSauvPerso);

		if (erreur = PAS_D_ERREUR)
			fread_s(&partie, sizeof(Partie), sizeof(Partie), 1, pFichier);
		else
			return erreur;
	}
	fclose(pFichier);
	return PAS_D_ERREUR;
}

CodeErreur ajoutSansPersonnage(Joueur ** pDebSansPersonnage, char perdant[]) {
	Joueur *pJoueur = *pDebSansPersonnage, *pSauvJoueur = NULL;

	while (pJoueur != NULL && strcmp(perdant, pJoueur->pseudo) > 0) {
		pSauvJoueur = pJoueur;
		pJoueur = pJoueur->pSuiv;
	}

	if (!strcmp(perdant, pJoueur->pseudo) == 0) {
		Joueur *pNouvJoueur;
		if (!nouveauJoueur(&pNouvJoueur))
			return ALLOCATION_MEMOIRE;
		strcpy_s(pNouvJoueur->pseudo,NBCARMAXJOUEUR, perdant);
		if (pSauvJoueur != NULL) {
			pNouvJoueur->pSuiv = pSauvJoueur->pSuiv;
			pSauvJoueur->pSuiv = pNouvJoueur;
		}
		else {
			pNouvJoueur->pSuiv = *pDebSansPersonnage;
			*pDebSansPersonnage = pNouvJoueur;
		}
	}

	return PAS_D_ERREUR;
}

void retraitPersonnage(Joueur **pJoueur, Personnage *pPerso, Personnage **pSauvePerso) {
	if (*pSauvePerso != NULL)
		(*pSauvePerso)->pSuiv = pPerso->pSuiv;
	else
		(*pJoueur)->pDebPersonnages = pPerso->pSuiv;
}

CodeErreur transfertPersonnage(Joueur * pJoueur, char nom[], int points, Personnage * pPerso, Personnage * pSauvPerso) {
	Personnage *pNouvPerso = NULL;
	if (!nouveauPersonnage(&pNouvPerso))
		return ALLOCATION_MEMOIRE;
	
	strcpy_s(pNouvPerso->nom, NBCARMAXPERSONNAGE, nom);
	pNouvPerso->points = points;
	pNouvPerso->pSuiv = NULL;

	if (pJoueur->pDebPersonnages == NULL) {
		pJoueur->pDebPersonnages = pNouvPerso;
	}
	else {
		pSauvPerso->pSuiv = pNouvPerso;
	}

	return PAS_D_ERREUR;
}