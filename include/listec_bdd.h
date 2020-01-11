#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#ifndef __LISTEC_BDD_H__
#define __LISTEC_BDD_H__

//fichier pour gerer les types listec_bdd_t

//fonction qui initialise un type listec_bdd_t
listec_bdd_t listec_bdd_nouv ();
//fonction qui ajoute un noeud en tete de liste
listec_bdd_t listec_bdd_adjt (listec_bdd_t l);
//fonction qui supprime la tete de la liste
listec_bdd_t listec_bdd_supt (listec_bdd_t l);
//fonction qui recheche un noeud dans la liste chainee
listec_bdd_t listec_bdd_rech (listec_bdd_t l, char *string);
//fonction qui affiche la listec_bdd_t
void listec_bdd_affiche (listec_bdd_t l);
//fonction qui libere la listec_bdd_t
void listec_bdd_free (listec_bdd_t l);

#endif
