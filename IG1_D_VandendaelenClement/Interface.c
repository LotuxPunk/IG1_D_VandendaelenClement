#include "General.h"

short reponseObtenue(Message *pLexique);
void nomObtenu(Message *pLexique, char *nom);
void pseudoObtenu(Message *pLexique, char *pseudo);
int pointsObtenu(Message *pLexique);

Choix choixObtenu(Message * pLexique, NumMessage numMenu) {
	bool choixValide;
	Choix choix;
	int maxChoix;
	NumMessage numMessage;
	do {
		
		maxChoix = afficherMenu(pLexique, numMenu);
		numMessage = OBT_CHOIX;

		afficherMessage(pLexique, numMessage);
		scanf_s("%d", &choix);
		choixValide = choix >= 1 && choix <= maxChoix;
		if (!choixValide) {
			CodeErreur codeErreur = MAUVAIS_CHOIX;
			numMessage = NUM_DEB_MESSAGE_ERREUR + codeErreur;
			afficherMessage(pLexique, numMessage);
		}

	} while (!choixValide);
	return choix;
}

void dialogue(Message * pLexique) {
	CodeErreur erreur = PAS_D_ERREUR;
	Joueur *pDebJoueurs = NULL;
	NumMessage numMenu = MENU_PRINCIPAL;
	Choix choix = choixObtenu(pLexique, numMenu);

	while (choix != QUITTER) {
		switch (choix) {
		case CHARGER_JOUEURS_PERSONNAGES:
			break;
		case AJOUTER_JOUEURS_PERSONNAGES:
			erreur = ajouterJoueurPersonnage(pLexique, pDebJoueurs);
			break;
		case AJOUTER_PERSONNAGES_PERSONNAGES:
			erreur = ajouterPersonnage(pLexique, pDebJoueurs);
			break;
		case SUPPRIMER_JOUEUR:
			break;
		case AFFICHER_JOUEUR_PERSONNAGES:
			break;
		case SAUVER_JOUEUR_PERSONNAGES:
			break;
		default:
			break;
		}

		if (erreur != PAS_D_ERREUR) {
			
		}
	}
}

CodeErreur ajouterPersonnage(Message * pLexique, Joueur * pDebJoueurs) {
	Personnage *pNouvPerso;
	CodeErreur erreur;
	bool allocationOk =	nouveauPersonnage(&pNouvPerso);
	if (!allocationOk) {
		erreur = ALLOCATION_MEMOIRE;
	}
	else {
		char *pseudo ="";
		Joueur *pJoueur, *pSauveJoueur;
		bool joueurExi;
		erreur = PAS_D_ERREUR;
		afficherTitre(pLexique, TITRE_PERSO_AJOUT);
		pseudoObtenu(pLexique, pseudo);
		joueurExi = joueurExiste(pDebJoueurs,pseudo,&pJoueur, &pSauveJoueur);
		if (!joueurExi) {
			erreur = JOUEUR_ABSENT;
		}
		else {
			Personnage *pNouvPerso = NULL;
			erreur = ajouterPersonnageAJoueur(pLexique,pJoueur, pNouvPerso);
		}
	}
	return erreur;
}

CodeErreur ajouterJoueurPersonnage(Message * pLexique, Joueur * pDebJoueur) {
	Joueur *pNouvJoueur;
	CodeErreur erreur;
	if (nouveauJoueur(&pNouvJoueur)) {
		erreur = ALLOCATION_MEMOIRE;
	}
	else {
		char pseudo[NBCARMAXJOUEUR];
		Joueur *pJoueur = NULL, *pSauvJoueur = NULL;
		erreur = PAS_D_ERREUR;
		afficherTitre(pLexique, TITRE_JOUEUR_AJOUT);
		
		pseudoObtenu(pLexique, pseudo);
		
		if (joueurExiste(pDebJoueur, pseudo, &pJoueur, &pSauvJoueur)) {
			libereJoueur(pJoueur);
			erreur = JOUEUR_DEJA_PRESENT;
		}
		else {
			bool allocationOk;
			ajouteJoueur(&pDebJoueur, pseudo, pNouvJoueur, pJoueur, pSauvJoueur);
			do {
				Personnage *pNouvPerso = NULL;
				allocationOk = nouveauPersonnage(&pNouvPerso);
				if (allocationOk) {
					erreur = ALLOCATION_MEMOIRE;
				}
				else {
					erreur = ajouterPersonnageAJoueur(pLexique, pNouvJoueur, pNouvPerso);
				}
			} while (allocationOk && reponseObtenue(pLexique) == OUI);
		}
	}
	return erreur;
}

CodeErreur ajouterPersonnageAJoueur(Message *pLexique, Joueur *pJoueur, Personnage *pNouvPerso) {
	CodeErreur erreur = PAS_D_ERREUR;
	char * nom = "";
	Personnage *pPerso = NULL, *pSauvePerso = NULL;
	bool persoExiste;

	nomObtenu(pLexique, nom);
	persoExiste = personnageExiste(pJoueur, nom, pPerso, pSauvePerso);
	if (persoExiste) {
		erreur = PERSONNAGE_DEJA_PRESENT;
		afficherMessage(pLexique, NUM_DEB_MESSAGE_ERREUR + erreur);
		liberePersonnage(pNouvPerso);
	}
	else {
		int points = pointsObtenu(pLexique);
		ajoutePersonnage(pJoueur, nom, points, pNouvPerso, pPerso, pSauvePerso);
	}
	return erreur;
}

void pseudoObtenu(Message *pLexique, char *pseudo) {
	bool pseudoValide;
	do {
		afficherMessage(pLexique, OBT_PSEUDO);
		gets_s(pseudo, NBCARMAXJOUEUR);
		pseudoValide = strlen(pseudo) > 0 && pseudo[0] <= 'A' && pseudo[0] >= 'Z';
		if (!pseudoValide) {
			afficherMessage(pLexique, NUM_DEB_MESSAGE_ERREUR + PSEUDO_NON_VALIDE);
		}
	} while (!pseudoValide);
}

short reponseObtenue(Message *pLexique) {
	short reponse;
	do {
		afficherMessage(pLexique, OBT_REPONSE);
		scanf_s("%hd", &reponse);
		if (reponse != OUI || reponse != NON) {
			afficherMessage(pLexique, NUM_DEB_MESSAGE_ERREUR + MAUVAIS_CHOIX);
		}
	} while (reponse != OUI && reponse != NON);	
	return reponse;
}

void nomObtenu(Message * pLexique, char *nom){
	do {
		afficherMessage(pLexique, OBT_NOM);
		gets_s(nom, NBCARMAXJOUEUR);
	} while (strlen(nom) > NBCARMAXJOUEUR);
}

int pointsObtenu(Message *pLexique) {
	int points;
	do {
		afficherMessage(pLexique, OBT_POINTS);
		scanf_s("%d", &points);
	} while (points >= 0);
	return points;
}
