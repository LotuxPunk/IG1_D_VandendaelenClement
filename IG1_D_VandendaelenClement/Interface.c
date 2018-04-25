#include "General.h"

Reponse reponseObtenue(Message *pLexique);
void nomObtenu(Message *pLexique, char nom[]);
void pseudoObtenu(Message *pLexique, char pseudo[]);
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
	Choix choix = choixObtenu(pLexique, MENU_PRINCIPAL);
	getchar();

	while (choix != QUITTER) {
		switch (choix) {
		case CHARGER_JOUEURS_PERSONNAGES:
			erreur = chargerJoueursPersonnages(pLexique, &pDebJoueurs);
			break;
		case AJOUTER_JOUEURS_PERSONNAGES:
			erreur = ajouterJoueurPersonnage(pLexique, pDebJoueurs);
			break;
		case AJOUTER_PERSONNAGES_PERSONNAGES:
			erreur = ajouterPersonnage(pLexique, pDebJoueurs);
			break;
		case SUPPRIMER_JOUEUR:
			erreur = supprimerJoueurPersonnages(pLexique, &pDebJoueurs);
			break;
		case AFFICHER_JOUEUR_PERSONNAGES:
			afficherJoueursPersonnages(pLexique, pDebJoueurs);
			break;
		case SAUVER_JOUEUR_PERSONNAGES:
			erreur = sauverJoueurPersonnages(pLexique, pDebJoueurs);
			break;
		default:
			break;
		}
		system("pause");

		if (erreur != PAS_D_ERREUR) {
			afficherMessage(pLexique, NUM_DEB_MESSAGE_ERREUR + erreur);
			erreur = PAS_D_ERREUR;
		}
			choix = choixObtenu(pLexique, MENU_PRINCIPAL);
	}
	libèreJoueursPersonnages(pDebJoueurs);
}

CodeErreur chargerJoueursPersonnages(Message * pLexique, Joueur ** pDebJoueurs) {
	CodeErreur erreur = PAS_D_ERREUR;
	erreur = fichierExiste();
	if (erreur == PAS_D_ERREUR) {
		afficherTitre(pLexique, CHARGEMENT);
		if (pDebJoueurs != NULL) {
			afficherMessage(pLexique, MODIFICATIONS_ANNULEES);
			Reponse reponse = reponseObtenue(pLexique);
			if (reponse = OUI) {
				libèreJoueursPersonnages(*pDebJoueurs);
				erreur = chargerJoueurs(pDebJoueurs);
			}
		}
		else {
			erreur = chargerJoueurs(pDebJoueurs);
		}
	}
	return erreur;
}

CodeErreur ajouterPersonnage(Message * pLexique, Joueur * pDebJoueurs) {
	Personnage *pNouvPerso;
	CodeErreur erreur;
	bool allocationOk =	nouveauPersonnage(&pNouvPerso);
	if (!allocationOk) {
		erreur = ALLOCATION_MEMOIRE;
	}
	else {
		char pseudo[NBCARMAXJOUEUR];
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
	if (!nouveauJoueur(&pNouvJoueur)) {
		erreur = ALLOCATION_MEMOIRE;
	}
	else {
		char pseudo[NBCARMAXJOUEUR];
		Joueur *pJoueur = NULL, *pSauvJoueur = NULL;
		bool jExiste;
		erreur = PAS_D_ERREUR;
		afficherTitre(pLexique, TITRE_JOUEUR_AJOUT);
		
		pseudoObtenu(pLexique, pseudo);
		
		jExiste = joueurExiste(pDebJoueur, pseudo, &pJoueur, &pSauvJoueur);
		if (jExiste) {
			libereJoueur(pJoueur);
			erreur = JOUEUR_DEJA_PRESENT;
		}
		else {
			bool allocationOk;
			ajouteJoueur(&pDebJoueur, pseudo, pNouvJoueur, pJoueur, pSauvJoueur);
			do {
				Personnage *pNouvPerso = NULL;
				allocationOk = nouveauPersonnage(&pNouvPerso);
				if (!allocationOk) {
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
	char nom[NBCARMAXJOUEUR] = "";
	Personnage *pPerso = NULL, *pSauvePerso = NULL;
	bool persoExiste;

	nomObtenu(pLexique, nom);
	persoExiste = personnageExiste(pJoueur, nom, &pPerso, &pSauvePerso);
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

void pseudoObtenu(Message *pLexique, char pseudo[]) {
	bool pseudoValide;
	do {
		afficherMessage(pLexique, OBT_PSEUDO);
		//gets_s(pseudo, NBCARMAXJOUEUR-1);
		scanf_s("%s", pseudo, NBCARMAXJOUEUR);
		pseudoValide = strlen(pseudo) > 0 && pseudo[0] >= 'A' && pseudo[0] <= 'Z';
		if (!pseudoValide) {
			afficherMessage(pLexique, NUM_DEB_MESSAGE_ERREUR + PSEUDO_NON_VALIDE);
		}
	} while (!pseudoValide);
}

Reponse reponseObtenue(Message *pLexique) {
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

void nomObtenu(Message * pLexique, char nom[]){
	do {
		afficherMessage(pLexique, OBT_NOM);
		scanf_s("%s", nom, NBCARMAXPERSONNAGE);
		//gets_s(nom, NBCARMAXJOUEUR);
	} while (strlen(nom) > NBCARMAXPERSONNAGE);
}

int pointsObtenu(Message *pLexique) {
	int points;
	do {
		afficherMessage(pLexique, OBT_POINTS);
		scanf_s("%d", &points);
	} while (points <= 0);
	return points;
}

CodeErreur supprimerJoueurPersonnages(Message *pLexique, Joueur ** ppDebJoueurs) {
	char pseudo[NBCARMAXJOUEUR];
	bool jExiste;
	Joueur *pJoueur = NULL, *pSauveJoueur = NULL;
	afficherTitre(pLexique, TITRE_JOUEUR_SUPPR);
	pseudoObtenu(pLexique, pseudo);
	jExiste = joueurExiste(*ppDebJoueurs, pseudo, &pJoueur, &pSauveJoueur);
	if (!jExiste) {
		return JOUEUR_ABSENT;
	}
	else {
		supprimeJoueur(ppDebJoueurs, pJoueur, pSauveJoueur);
		return PAS_D_ERREUR;
	}
}

void afficherJoueursPersonnages(Message * pLexique, Joueur * pDebJoueur) {
	if (pDebJoueur == NULL) {
		afficherMessage(pLexique, AUCUN_JOUEUR);
	}
	else {
		afficherTitre(pLexique, TITRE_LISTE_JOUEURS);
		listeJoueurs(pDebJoueur);
	}
}

CodeErreur sauverJoueurPersonnages(Message * pLexique, Joueur * pDebJoueurs) {
	CodeErreur erreur = PAS_D_ERREUR;
	if (pDebJoueurs == NULL) {
		afficherMessage(pLexique, AUCUN_JOUEUR);
	}
	else {
		afficherTitre(pLexique, SAUVEGARDE);
		erreur = sauverJoueurs(pDebJoueurs);
	}
	return erreur;
}

