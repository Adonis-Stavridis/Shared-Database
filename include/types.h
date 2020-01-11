#include <netdb.h>
#include <errno.h>

#ifndef __TYPES_H__
#define __TYPES_H__

//fichier pour les MACROS et types

// MACROS

//Base de donnees
#define BDD_PATH "bdd/acces.txt"
#define BDD_DELIM ":"

//Tableaux
#define MAX_TAB_SIZE 8

//String / Chaines de caractères
#define MAX_STRING_SIZE 512
#define TMP_STRING_SIZE 64
#define NRML_STRING_SIZE 16

//Timeout et sleep
#define TIMEOUT 1
#define MAX_SEND 3
#define SLEEP 3

//Enumeration sockets et serveur de donnees
#define SOCKET_NUMBER 2
#define S_DATA_NUMBER 2

//Ports du serveur d'acces et Adresse locale
#define PORT_1 4096
#define PORT_2 4097
#define LOC_ADR "127.0.0.1"

//Types et Champs
#define CLIENT 0
#define DATA 1

//Statuts
#define CONNEXION 0
#define CONNECTE 1
#define AUTHENTIFICATION 2
#define AUTHENTIFIE 3
#define DESAUTHENTIFICATION 4
#define DESAUTHENTIFIE 5
#define DECONNEXION 6
#define DECONNECTE 7
#define SURCHARGE 8
#define ERREUR 9
#define VALIDE 10
#define NONVALIDE 11
#define SYNC 12

//Instructions / Demandes
#define LIRE 0
#define ECRIRE 1
#define SUPPRIMER 2
#define SYNC_INIT 3
#define SYNC_PROC 4
#define SYNC_FIN 5

//TYPES

//listec_bdd_t: liste chainee pour stocker la base de donnees
typedef struct noeud_bdd_t {
  char utilisateur[NRML_STRING_SIZE];
  char mot_de_passe[NRML_STRING_SIZE];
  char champs[S_DATA_NUMBER][NRML_STRING_SIZE];
  struct noeud_bdd_t *suiv;
} noeud_bdd_t, *listec_bdd_t;

//listec_data_t: liste chainee pour liste de serveur de donnees
typedef struct noeud_data_t {
  char utilisateur[NRML_STRING_SIZE];
  char valeur[NRML_STRING_SIZE];
  struct noeud_data_t *suiv;
} noeud_data_t, *listec_data_t;

//util_t: structure des coordonnees utilisateur
typedef struct util_t {
  char utilisateur[NRML_STRING_SIZE];
  char mot_de_passe[NRML_STRING_SIZE];
} util_t;

//infos_t: structure qui stocke toute les infos necessaire pour identifier un processus (CLIENT - DATA)
typedef struct infos_t {
  unsigned int type;
  unsigned int id;
  unsigned short port;
  unsigned int statut;
  util_t coord;
  char data[NRML_STRING_SIZE];
} infos_t;

//socklist_t: tableau de descripteurs de sockets
typedef struct socklist_t {
  int tab[SOCKET_NUMBER];
} socklist_t;

//liste_infos_t: structure pour stocker des infos pour identifier les processus connectes
typedef struct liste_infos_t {
  infos_t tab[MAX_TAB_SIZE];
  unsigned int bool[MAX_TAB_SIZE];
  unsigned int index;
} liste_infos_t;

//instr_t: structure qui represente une instruction
typedef struct instr_t {
  unsigned int id;
  unsigned int arg;
  char champs[S_DATA_NUMBER][NRML_STRING_SIZE];
  char valeurs[S_DATA_NUMBER][NRML_STRING_SIZE];
} instr_t;

//demande_t: structure qui represente une demande
typedef struct demande_t {
  unsigned int arg;
  char utilisateur[NRML_STRING_SIZE];
  char valeur[NRML_STRING_SIZE];
} demande_t;

//data_t: strucuture qui represente une reponse des serveurs (acces ou donnees)
typedef struct data_t {
  unsigned int statut;
  char string[MAX_STRING_SIZE];
} data_t;

#endif
