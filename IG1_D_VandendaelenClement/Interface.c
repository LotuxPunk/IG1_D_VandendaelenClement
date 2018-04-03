#include "General.h"

short reponseObtenue(Message *pLexique);

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
			break;
		case AJOUTER_PERSONNAGES_PERSONNAGES:
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

CodeErreur ajouterPersonnage(Message * pLexique, Joueur * pDebJoueurs)
{
	return PAS_D_ERREUR;
}

CodeErreur ajouterJoueurPersonnage(Message * pLexique, Joueur * pDebJoueur) {
	Joueur *pNouvJoueur = NULL;
	CodeErreur erreur;
	if (nouveauJoueur(pNouvJoueur)) {
		erreur = ALLOCATION_MEMOIRE;
	}
	else {
		char pseudo[NBCARMAXJOUEUR];
		Joueur *pJoueur = NULL, *pSauvJoueur = NULL;
		erreur = PAS_D_ERREUR;
		afficherTitre(pLexique, TITRE_JOUEUR_AJOUT);
		
		pseudoObtenu(pLexique, pseudo);
		
		if (joueurExiste(pDebJoueur, pseudo, pJoueur, pSauvJoueur)) {
			libereJoueur(pJoueur);
			erreur = JOUEUR_DEJA_PRESENT;
		}
		else {
			bool allocationOk;
			ajouteJoueur(pDebJoueur, pseudo, pNouvJoueur, pJoueur, pSauvJoueur);
			do {
				Personnage *pNouvPerso = NULL;
				allocationOk = nouveauPersonnage(pNouvPerso);
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
	char nom[NBCARMAXJOUEUR];
	bool persoExiste;
	Personnage *pPerso = NULL, *pSauvPerso = NULL;
	CodeErreur erreur;
	nomObtenu(pLexique, nom);
	persoExiste = personnageExiste(pJoueur, nom, pPerso, pSauvPerso);
	if (persoExiste) {
		erreur = PERSONNAGE_DEJA_PRESENT;
		afficherMessage(pLexique, NUM_DEB_MESSAGE_ERREUR + erreur);
		liberePersonnage(pNouvPerso);
	}
	else {
		
	}
}

int pointsObtenus(Message * pLexique) {

	return 0;
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

void nomObtenu(Message * pLexique, char * nom){
	afficherMessage(pLexique, OBT_NOM);
	gets_s(nom, NBCARMAXJOUEUR);
}