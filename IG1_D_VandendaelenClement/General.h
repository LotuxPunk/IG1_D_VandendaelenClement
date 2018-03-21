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

//Gestion
bool joueurExiste(Joueur *pDebJoueur, char *pseudo, Joueur *pJoueur, Joueur *pSauvJoueur);
bool nouveauJoueur(Joueur *pNouvJoueur);
bool nouveauPersonnage(Personnage *pNouvPerso);
void libereJoueur(Joueur *pJoueur);
void libèrePersonnage(Personnage *pPerso);

void ajouteJoueur(Joueur *pDebJoueur, char *pseudo, Joueur *pNouvJoueur, Joueur *pJoueur, Joueur *pSauvJoueur);
#endif // !GENERAL_H