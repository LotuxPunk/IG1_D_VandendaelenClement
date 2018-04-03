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
void pseudoObtenu(Message *pLexique, char *pseudo);
void nomObtenu(Message *pLexique, char *nom);
CodeErreur ajouterPersonnageAJoueur(Message *pLexique, Joueur *pJoueur, Personnage *pNouvPerso);
int pointsObtenus(Message *pLexique);

//Gestion
bool joueurExiste(Joueur *pDebJoueur, char *pseudo, Joueur *pJoueur, Joueur *pSauvJoueur);
bool personnageExiste(Joueur *pJoueur, char *nom, Personnage *pPerso, Personnage *pSauvPerso);
bool nouveauJoueur(Joueur *pNouvJoueur);
bool nouveauPersonnage(Personnage *pNouvPerso);
void libereJoueur(Joueur *pJoueur);
void liberePersonnage(Personnage *pPerso);
void ajouteJoueur(Joueur *pDebJoueur, char *pseudo, Joueur *pNouvJoueur, Joueur *pJoueur, Joueur *pSauvJoueur);
void ajoutePersonnage(Joueur *pJoueur, char *nom, int points, Personnage *pNouvPerso, Personnage *pPerso, Personnage *pSauvPerso);
void supprimeJoueur(Joueur *pDebJoueur, Joueur *pJoueur, Joueur *pSauvJoueur);

#endif // !GENERAL_H