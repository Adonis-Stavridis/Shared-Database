#include <stdio.h>
#include "types.h"

#ifndef __S_OUTPUT_H__
#define __S_OUTPUT_H__

//fichier pour l'affichage du serveur d'acces

//fonction qui affiche le lancement du serveur d'acces
void s_output_debut ();
//fonction qui affiche la terminaison du serveur d'acces
void s_output_fin ();
//fonction qui affiches les infos_t recus
void s_output_infos (infos_t *infos);
//fonction qui affiche message recu inconnu
void s_output_message ();
//fonction qui affiche commande inconnue
void s_output_commande ();
//fonction qui affiche erreur trop de champs
void s_output_champ_overflow (char *string);

#endif
