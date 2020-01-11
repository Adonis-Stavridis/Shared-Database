#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "types.h"
#include "input.h"
#include "output.h"

#ifndef __CLIENT_H__
#define __CLIENT_H__

//fichier qui gere la communication client -> serveur acces

//fonction qui connecte le client au serveur d'acces
unsigned int client_init (int socketfd, struct sockaddr_in *serveur, infos_t *infos);
//fonction qui deconnecte le client du serveur d'acces
unsigned int client_fin (int socketfd, struct sockaddr_in *serveur, infos_t *infos);
//fonction qui authentifie le client
unsigned int authentification (int socketfd, struct sockaddr_in *serveur, infos_t *infos);
//fonction qui desauthentifie le client
unsigned int desauthentification (int socketfd, struct sockaddr_in *serveur, infos_t *infos);
//fonction qui envoie les instructions au serveurs d'acces
unsigned int instructions (int socketfd, struct sockaddr_in *serveur, unsigned int id);

#endif
