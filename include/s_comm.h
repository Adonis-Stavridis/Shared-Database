#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>
#include "types.h"
#include "liste_infos.h"
#include "t_bdd.h"
#include "custom_acces.h"

#ifndef __S_COMM_H__
#define __S_COMM_H__

//fichier du thread du serveur d'acces - partie instructions / reponses du serveur

//variables globales initialise dans s_acces
extern listec_bdd_t bdd;
extern liste_infos_t clients;
extern liste_infos_t s_data;
extern unsigned int quit;

//pointeur de fonction du thread qui gere les instructions et reponses du serveurs
void *s_comm (void *arg);

#endif
