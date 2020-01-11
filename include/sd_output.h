#include <stdio.h>
#include <unistd.h>
#include "types.h"

#ifndef __SD_OUTPUT_H__
#define __SD_OUTPUT_H__

//fichier pour l'affiche du serveur de donnees

//fonction qui affiche le lancement du serveur de donnees
void sd_output_debut (char *string);
//fonction qui affiche la terminaison du serveur de donnees
void sd_output_fin (char *string);
//fonction qui affiche que le serveur d'acces est en ligne
void sd_output_en_ligne ();
//fonction qui affiche que le serveur d'acces est hors ligne
void sd_output_hors_ligne ();
//fonction qui affiche que le serveur d'acces est en surcharge
void sd_output_surcharge ();
//fonction qui affiche erreur serveur
void sd_output_erreur ();
//fonction qui affiche commande inconnue
void sd_output_commande ();
//fonction qui affiche une demande recue
void sd_output_demande (demande_t demande);
//fonction qui affiche debut de synchronisation
void sd_output_sync ();

#endif
