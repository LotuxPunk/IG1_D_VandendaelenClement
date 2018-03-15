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

