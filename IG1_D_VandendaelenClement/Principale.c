#include "General.h"

void main(void) {
	CodeErreur codeErreur = PAS_D_ERREUR;
	NumMessage numMenu = MENU_PRINCIPAL;
	Message *pLexique;

	codeErreur = chargerLexique(&pLexique);
	if (codeErreur == PAS_D_ERREUR) {
		Choix choix = choixObtenu(pLexique, numMenu);
	}


}