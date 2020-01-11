#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "types.h"
#include "sd_output.h"

#ifndef __S_CONNECT_H__
#define __S_CONNECT_H__

//fichier pour gerer des communications entre serveur de donnees -> serveur d'acces

//fonction qui connecte le serveur de donnees au serveur d'acces
unsigned int connect_init (int socketfd, struct sockaddr_in *serveur, infos_t *infos);
//fonction qui deconnecte le serveur de donnees du serveur d'acces
unsigned int connect_fin (int socketfd, struct sockaddr_in *serveur, infos_t *infos);
//fonction qui commence le protocole de synchronisation entre les serveurs de donnees
unsigned int instr_sync (int socketfd, struct sockaddr_in *serveur, infos_t *infos);
//fonction qui effectue la synchronisation entre les serveurs de donnees
unsigned int sync_init (int socketfd, struct sockaddr_in *serveur, listec_data_t liste);

#endif
