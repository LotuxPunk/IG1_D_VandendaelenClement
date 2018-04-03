#ifndef CONSTANTES_H
#define CONSTANTES_H

#define NBCARMAXJOUEUR 30
#define NBCARMAXPERSONNAGE 30

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
	JOUEUR_ABSENT
};

typedef enum reponse Reponse;
enum reponse {
	OUI,
	NON
};

typedef enum choix Choix;
enum choix {
	CHARGER_JOUEURS_PERSONNAGES,
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

#endif // !CONSTANTES_H