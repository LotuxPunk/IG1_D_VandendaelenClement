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
CodeErreur ajouterPersonnage(Message *pLexique, Joueur *pDebJoueurs);
CodeErreur ajouterJoueurPersonnage(Message *pLexique, Joueur *pDebJoueur);
CodeErreur ajouterPersonnageAJoueur(pLexique, pNouvJoueur, pNouvPerso);

//Gestion
bool joueurExiste(Joueur *pDebJoueur, char *pseudo, Joueur **ppJoueur, Joueur **ppSauvJoueur);
bool personnageExiste(Joueur *pJoueur, char *nom, Personnage *pPerso, Personnage *pSauvPerso);
bool nouveauJoueur(Joueur **ppNouvJoueur);
bool nouveauPersonnage(Personnage **ppNouvPerso);
void libereJoueur(Joueur *pJoueur);
void liberePersonnage(Personnage *pPerso);
void ajouteJoueur(Joueur **ppDebJoueur, char *pseudo, Joueur *pNouvJoueur, Joueur *pJoueur, Joueur *pSauvJoueur);
void ajoutePersonnage(Joueur *pJoueur, char *nom, int points, Personnage *pNouvPerso, Personnage *pPerso, Personnage *pSauvPerso);
void supprimeJoueur(Joueur **ppDebJoueur, Joueur *pJoueur, Joueur *pSauvJoueur);
#endif // !GENERAL_H