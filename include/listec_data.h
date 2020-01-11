#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#ifndef __LISTEC_DATA_H__
#define __LISTEC_DATA_H__

//fichier pour gerer les types listec_data_t

//fonction qui initialise un type listec_data_t
listec_data_t listec_data_nouv ();
//fonction qui ajoute un noeud en tete de liste
listec_data_t listec_data_adjt (listec_data_t l);
//fonction qui supprime la tete de la liste
listec_data_t listec_data_supt (listec_data_t l);
//fonction qui supprime le nieme noeud de la liste
listec_data_t listec_data_supn (listec_data_t l, char utilisateur[NRML_STRING_SIZE]);
//fonction qui recherche un noeud dans la liste chainee
listec_data_t listec_data_rech (listec_data_t l, char *string);
//fonction qui affiche la listec_data_t
void listec_data_affiche (listec_data_t l);
//fonction qui libere la listec_data_t
void listec_data_free (listec_data_t l);

#endif
