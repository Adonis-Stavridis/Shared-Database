#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#ifndef __INPUT_H__
#define __INPUT_H__

//fichier pour gerer les entrees pour l'application

//fonction qui enleve le \n a la fin d'un string et le remplace par \0
void input_newline (char *string, unsigned int lgr);
//fonction qui gere l'entree pour la connexion / authentification
unsigned int input_connexion (char *string);
//fonction qui gere l'entree pour le menu
unsigned int input_menu (util_t *coord);

#endif
