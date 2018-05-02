#ifndef GENERAL_H
#define GENERAL_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Lexique.h"
#include "Constantes.h"

//Interface
Choix choixObtenu(Message *pLexique, NumMessage numMenu);
void dialogue(Message *pLexique);
CodeErreur chargerJoueursPersonnages(Message *pLexique, Joueur **pDebJoueurs);
CodeErreur ajouterPersonnage(Message *pLexique, Joueur **ppDebJoueurs);
CodeErreur ajouterJoueurPersonnage(Message *pLexique, Joueur **ppDebJoueurs);
CodeErreur ajouterPersonnageAJoueur(pLexique, pNouvJoueur, pNouvPerso);
CodeErreur supprimerJoueurPersonnages(Message *pLexique, Joueur ** ppDebJoueurs);
void afficherJoueursPersonnages(Message *pLexique, Joueur *pDebJoueurs);
CodeErreur sauverJoueurPersonnages(Message *pLexique, Joueur *pDebJoueurs);

//Gestion
bool joueurExiste(Joueur *pDebJoueurs, char pseudo[], Joueur **ppJoueur, Joueur **ppSauvJoueur);
bool personnageExiste(Joueur *pJoueur, char nom[], Personnage **pPerso, Personnage **pSauvPerso);
bool nouveauJoueur(Joueur **ppNouvJoueur);
bool nouveauPersonnage(Personnage **ppNouvPerso);
void libereJoueur(Joueur *pJoueur);
void liberePersonnage(Personnage *pPerso);
void ajouteJoueur(Joueur **ppDebJoueurs, char *pseudo, Joueur *pNouvJoueur, Joueur *pJoueur, Joueur *pSauvJoueur);
void ajoutePersonnage(Joueur *pJoueur, char *nom, int points, Personnage *pNouvPerso, Personnage *pPerso, Personnage *pSauvPerso);
void supprimeJoueur(Joueur **ppDebJoueurs, Joueur *pJoueur, Joueur *pSauvJoueur);
void listeJoueurs(Joueur *pDebJoueurs);
int nbPersonnages(Joueur *pJoueur);
void libèreJoueursPersonnages(Joueur *pDebJoueurs);

//Fichiers
CodeErreur sauverJoueurs(Joueur *pDebJoueurs);
CodeErreur fichierExiste(void);
CodeErreur chargerJoueurs(Joueur **pDebJoueurs);
#endif // !GENERAL_H