#include "General.h"

Reponse reponseObtenue(Message *pLexique, NumMessage message);
void nomObtenu(Message *pLexique, char nom[]);
void pseudoObtenu(Message *pLexique, char pseudo[]);
int pointsObtenu(Message *pLexique);


Choix choixObtenu(Message * pLexique, NumMessage numMenu) {
	bool choixValide;
	Choix choix;
	int maxChoix;
	do {
		maxChoix = afficherMenu(pLexique, numMenu);
		afficherMessage(pLexique, OBT_CHOIX);
		scanf_s("%d", &choix);
		choixValide = choix >= 1 && choix <= maxChoix;
		if (!choixValide) {
			afficherMessage(pLexique, NUM_DEB_MESSAGE_ERREUR + MAUVAIS_CHOIX);
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
			erreur = ajouterJoueurPersonnage(pLexique, &pDebJoueurs);
			break;
		case AJOUTER_PERSONNAGES_PERSONNAGES:
			erreur = ajouterPersonnage(pLexique, &pDebJoueurs);
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
	CodeErreur erreur = fichierExiste();
	if (erreur == PAS_D_ERREUR) {
		afficherTitre(pLexique, CHARGEMENT);
		if ((*pDebJoueurs) != NULL) {
			afficherMessage(pLexique, MODIFICATIONS_ANNULEES);
			Reponse reponse = reponseObtenue(pLexique, ECRASER_LISTE);
			if (reponse = OUI) {
				libèreJoueursPersonnages(*pDebJoueurs);
				return chargerJoueurs(pDebJoueurs);
			}
		}
		else {
			return chargerJoueurs(pDebJoueurs);
		}
	}
	return erreur;
}

CodeErreur ajouterPersonnage(Message * pLexique, Joueur ** pDebJoueurs) {
	Personnage *pNouvPerso;
	if (!nouveauPersonnage(&pNouvPerso)) {
		return ALLOCATION_MEMOIRE;
	}
	else {
		char pseudo[NBCARMAXJOUEUR];
		Joueur *pJoueur, *pSauveJoueur;
		afficherTitre(pLexique, TITRE_PERSO_AJOUT);
		pseudoObtenu(pLexique, pseudo);
		if (!joueurExiste(*pDebJoueurs, pseudo, &pJoueur, &pSauveJoueur)) {
			return JOUEUR_ABSENT;
		}
		else {
			return ajouterPersonnageAJoueur(pLexique, pJoueur, pNouvPerso);
		}
	}
}

CodeErreur ajouterJoueurPersonnage(Message * pLexique, Joueur ** pDebJoueur) {
	Joueur *pNouvJoueur;
	if (!nouveauJoueur(&pNouvJoueur)) {
		return ALLOCATION_MEMOIRE;
	}
	else {
		char pseudo[NBCARMAXJOUEUR];
		Joueur *pJoueur = NULL, *pSauvJoueur = NULL;
		afficherTitre(pLexique, TITRE_JOUEUR_AJOUT);

		pseudoObtenu(pLexique, pseudo);

		if (joueurExiste(*pDebJoueur, pseudo, &pJoueur, &pSauvJoueur)) {
			libereJoueur(pJoueur);
			return JOUEUR_DEJA_PRESENT;
		}
		else {
			ajouteJoueur(pDebJoueur, pseudo, pNouvJoueur, pJoueur, pSauvJoueur);
			do {
				Personnage *pNouvPerso = NULL;
				if(!nouveauPersonnage(&pNouvPerso))
					return ALLOCATION_MEMOIRE;
				ajouterPersonnageAJoueur(pLexique, pNouvJoueur, pNouvPerso);
			} while (reponseObtenue(pLexique, OBT_REPONSE) == OUI);
			return PAS_D_ERREUR;
		}
	}
}

CodeErreur ajouterPersonnageAJoueur(Message *pLexique, Joueur *pJoueur, Personnage *pNouvPerso) {
	char nom[NBCARMAXJOUEUR] = "";
	Personnage *pPerso = NULL, *pSauvePerso = NULL;

	nomObtenu(pLexique, nom);
	if (personnageExiste(pJoueur, nom, &pPerso, &pSauvePerso)) {
		afficherMessage(pLexique, NUM_DEB_MESSAGE_ERREUR + PERSONNAGE_DEJA_PRESENT);
		liberePersonnage(pNouvPerso);
		return PERSONNAGE_DEJA_PRESENT;
	}
	else {
		int points = pointsObtenu(pLexique);
		ajoutePersonnage(pJoueur, nom, points, pNouvPerso, pPerso, pSauvePerso);
		return PAS_D_ERREUR;
	}
}

void pseudoObtenu(Message *pLexique, char pseudo[]) {
	bool pseudoValide;
	do {
		afficherMessage(pLexique, OBT_PSEUDO);
		scanf_s("%s", pseudo, NBCARMAXJOUEUR);
		pseudoValide = strlen(pseudo) > 0 && pseudo[0] >= 'A' && pseudo[0] <= 'Z';
		if (!pseudoValide) {
			afficherMessage(pLexique, NUM_DEB_MESSAGE_ERREUR + PSEUDO_NON_VALIDE);
		}
	} while (!pseudoValide);
}

Reponse reponseObtenue(Message *pLexique, NumMessage message) {
	short reponse;
	do {
		afficherMessage(pLexique, message);
		scanf_s("%hd", &reponse);
		if (reponse != OUI && reponse != NON) {
			afficherMessage(pLexique, NUM_DEB_MESSAGE_ERREUR + MAUVAIS_CHOIX);
		}
	} while (reponse != OUI && reponse != NON);
	return reponse;
}

void nomObtenu(Message * pLexique, char nom[]) {
	do {
		afficherMessage(pLexique, OBT_NOM);
		scanf_s("%s", nom, NBCARMAXPERSONNAGE);
	} while (strlen(nom) > NBCARMAXPERSONNAGE);
}

int pointsObtenu(Message *pLexique) {
	int points;
	do {
		afficherMessage(pLexique, OBT_POINTS);
		scanf_s("%d", &points);
	} while (points < 0);
	return points;
}

CodeErreur supprimerJoueurPersonnages(Message *pLexique, Joueur ** ppDebJoueurs) {
	char pseudo[NBCARMAXJOUEUR];
	Joueur *pJoueur = NULL, *pSauveJoueur = NULL;
	afficherTitre(pLexique, TITRE_JOUEUR_SUPPR);
	pseudoObtenu(pLexique, pseudo);
	if (!joueurExiste(*ppDebJoueurs, pseudo, &pJoueur, &pSauveJoueur)) {
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
	if (pDebJoueurs == NULL) {
		afficherMessage(pLexique, AUCUN_JOUEUR);
		return PAS_D_ERREUR;
	}
	else {
		afficherTitre(pLexique, SAUVEGARDE);
		return sauverJoueurs(pDebJoueurs);
	}
}

