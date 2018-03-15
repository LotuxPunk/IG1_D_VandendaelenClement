#ifndef CONSTANTES_H
#define CONSTANTE_H

#define NBCARMAXJOUEUR 100
#define NBCARMAXPERSONNAGE 100

typedef enum codeErreur CodeErreur;
enum codeErreur {
	JOUEUR_EXITANT,
	PAS_D_ERREUR,
	ALLOCATION_MEMOIRE,
	OUVERTURE_FICHIER,
	MAUVAIS_CHOIX
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

typedef struct joueur Joueur;
struct joueur {
	char pseudo[NBCARMAXJOUEUR];
	Personnage *pDebPersonnages;
	Joueur *pSuiv;
};

typedef struct personnage Personnage;
struct personnage {
	char nom[NBCARMAXPERSONNAGE];
	int point;
	Personnage *pSuiv;
};

#endif // !CONSTANTES_H