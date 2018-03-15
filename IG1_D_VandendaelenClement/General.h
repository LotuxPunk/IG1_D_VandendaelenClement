#ifndef GENERAL_H
#define GENERAL_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Lexique.h"
#include "Constantes.h"

Choix choixObtenu(Message *pLexique, NumMessage numMenu);
void dialogue(Message *pLexique);

#endif // !GENERAL_H