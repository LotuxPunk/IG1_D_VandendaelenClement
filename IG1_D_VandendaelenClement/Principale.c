#include "General.h"

void main(void) {
	CodeErreur erreur = PAS_D_ERREUR;
	NumMessage numMenu = MENU_PRINCIPAL;
	Message *pLexique = NULL;
	erreur = chargerLexique(&pLexique);
	if (erreur != PAS_D_ERREUR) {
		if (erreur == ALLOCATION_MEMOIRE) {
			printf("Erreur mémoire / Memory error");
			libererLexique(pLexique);
		}
		else {
			if (erreur == OUVERTURE_FICHIER) {
				printf("Erreur ouverture fichier / File opening error");
			}
		}
	}
	else {
		dialogue(pLexique);
		libererLexique(pLexique);
	}
	system("pause");
}