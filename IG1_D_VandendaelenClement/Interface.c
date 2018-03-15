#include "General.h"

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

