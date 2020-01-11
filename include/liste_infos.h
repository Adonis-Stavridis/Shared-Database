#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "types.h"
#include "custom_acces.h"

#ifndef __LISTE_INFOS_H__
#define __LISTE_INFOS_H__

//fichier pour gerer les types liste_infos_t

//fonction qui affecte la bonne valeur de l'index
void set_index (liste_infos_t *liste_infos);
//fonction qui initialise le type liste_infos_t
void liste_init (liste_infos_t *liste_infos);
//fonction qui ajoute un type infos_t ai a liste_infos_t
void liste_ajout (liste_infos_t *liste_infos, infos_t *infos);
//fonction qui supprime un type infos_t à liste_infos_t
void liste_sup (liste_infos_t *liste_infos, infos_t *infos);
//fonction qui affiche tous les clients de liste_infos_t
void liste_affiche_clients (liste_infos_t *liste_infos);
//fonction qui affiche tous les serveur de donnees de liste_infos_t
void liste_affiche_data (liste_infos_t *liste_infos);
//fonction qui recheche un champ de serveur de donnees dans liste_infos_t
unsigned int liste_rech_data (liste_infos_t *liste_infos, char data[NRML_STRING_SIZE]);
//fonction qui donne tout les champs de serveurs de donnees dans liste_infos_t
void get_champs (liste_infos_t *liste_infos, char string[MAX_STRING_SIZE]);
//fonction qui place tout les champs de serveurs de donnees connectes dans un tableau
unsigned int set_champs (liste_infos_t *liste_infos, char champs[MAX_TAB_SIZE][NRML_STRING_SIZE]);
//fonction qui donne tout les ports de serveurs de donnees avec le meme champ
unsigned int get_data_ports (liste_infos_t *liste_infos, unsigned short ports[MAX_TAB_SIZE],char data[NRML_STRING_SIZE]);
//fonction qui donne tous les ports de serveurs de donees différents de celui entre en argument
unsigned int get_data_ports_diff (liste_infos_t *liste_infos, unsigned short ports[MAX_TAB_SIZE], char data[NRML_STRING_SIZE], unsigned int id);
//fonction qui place le login de l'utilisateur dans un string
unsigned int set_utilisateur (liste_infos_t *liste_infos, unsigned int id, char string[NRML_STRING_SIZE]);

#endif
