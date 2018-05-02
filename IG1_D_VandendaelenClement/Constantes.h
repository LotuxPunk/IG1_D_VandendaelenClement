#ifndef CONSTANTES_H
#define CONSTANTES_H

#define NBCARMAXJOUEUR 30
#define NBCARMAXPERSONNAGE 30
#define NOMFICHIER "joueurs.dat"

typedef enum codeErreur CodeErreur;
enum codeErreur { 
	PAS_D_ERREUR = 0,
	JOUEUR_EXISTANT,
	ALLOCATION_MEMOIRE,
	OUVERTURE_FICHIER,
	MAUVAIS_CHOIX,
	PSEUDO_NON_VALIDE,
	JOUEUR_DEJA_PRESENT,
	PERSONNAGE_DEJA_PRESENT,
	JOUEUR_ABSENT,
	FICHIER_INEXISTANT
};

typedef enum reponse Reponse;
enum reponse {
	OUI = 1,
	NON
};

typedef enum choix Choix;
enum choix {
	CHARGER_JOUEURS_PERSONNAGES = 1,
	AJOUTER_JOUEURS_PERSONNAGES,
	AJOUTER_PERSONNAGES_PERSONNAGES,
	SUPPRIMER_JOUEUR,
	AFFICHER_JOUEUR_PERSONNAGES,
	SAUVER_JOUEUR_PERSONNAGES,
	QUITTER
};

typedef struct personnage Personnage;
struct personnage {
	char nom[NBCARMAXPERSONNAGE];
	int points;
	Personnage *pSuiv;
};

typedef struct joueur Joueur;
struct joueur {
	char pseudo[NBCARMAXJOUEUR];
	Personnage *pDebPersonnages;
	Joueur *pSuiv;
};

typedef struct joueurFi JoueurFi;
struct joueurFi {
	char pseudo[NBCARMAXJOUEUR];
	int nbrPerso;
};

typedef struct persoFi PersoFi;
struct persoFi {
	char nom[NBCARMAXPERSONNAGE];
	int points;
};

#endif // !CONSTANTES_H