#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "types.h"
#include "listec_bdd.h"
#include "s_output.h"

#ifndef __T_BDD_H__
#define __T_BDD_H__

//fichier pour le traitement de la base de donnees des logins

//fonction qui initialise / charge la base de donnees en memoire
listec_bdd_t bdd_init ();
//fonction qui verifie si les coordonnees sont valides
unsigned int verif_coordonnees (listec_bdd_t bdd, util_t coord);
//fonction qui verifie si un utilisateur possede les droits de lecture a un champ
unsigned int verif_droits (listec_bdd_t bdd, char utilisateur[NRML_STRING_SIZE], char champ[NRML_STRING_SIZE]);
//fonction qui libere la base de donnees
void bdd_fin (listec_bdd_t bdd);

#endif
