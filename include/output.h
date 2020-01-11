#include <stdio.h>
#include <unistd.h>
#include "types.h"

#ifndef __OUTPUT_H__
#define __OUTPUT_H__

//fichier pour l'affichage du client

//fonction qui affiche le lancement de l'application
void output_debut ();
//fonction qui affiche la terminaison de l'application
void output_fin ();
//fonction qui affiche que le serveur d'acces est en ligne
void output_en_ligne ();
//fonction qui affiche que le serveur d'acces est hors ligne
void output_hors_ligne ();
//fonction qui affiche que le serveur d'acces est en surcharge
void output_surcharge ();
//fonction qui affiche erreur serveur
void output_erreur ();
//fonction qui affiche que le serveur d'acces s'est deconnecte
void output_deconexion ();
//fonction qui affiche le menu
void output_menu ();
//fonction qui affiche le menu connexion / authentification
void output_connexion (util_t *coord);
//fonction qui affiche erreur d'authentification
void output_auth_err ();
//fonction qui affiche succes d'authentification
void output_auth_suc ();
//fonction qui affiche succes de desauthentification
void output_desauth ();
//fonction qui affiche le menu instructions
void output_instr ();
//fonction qui affiche erreur de format instructions
void output_instr_err ();
//fonction qui affiche erreur de champs instructions
void output_instr_champs ();
//fonction qui affiche erreur trop de champs instructions
void output_instr_overflow ();

#endif
