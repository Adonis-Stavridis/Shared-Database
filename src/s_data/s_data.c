#include "s_data.h"

int main (int argc, char *argv[]) {
  struct sockaddr_in s_data, serveur1, serveur2, client;
  int socketfd;
  infos_t infos;
  size_t length = sizeof(struct sockaddr_in);
  unsigned int quit = 0, syncbln = 0;
  char buf[TMP_STRING_SIZE];
  fd_set set;
  demande_t demande;
  data_t data;
  listec_data_t liste, listetmp;

  if (argc != 3) {
    fprintf(stderr, "%s <PORT> <field>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if ((atoi(argv[1]) < 2048) && (atoi(argv[1]) > 65535)) {
    fprintf(stderr, "2048 <= PORT <= 65535\n");
    exit(EXIT_FAILURE);
  }

  if ((socketfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP)) == -1) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  memset((char *)&s_data, 0, length);
  s_data.sin_family = AF_INET;
  s_data.sin_port = htons(atoi(argv[1]));
  s_data.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(socketfd, (struct sockaddr *)&s_data, (socklen_t) length) == -1) {
    perror("bind");
    if (close(socketfd) == -1) {
      perror("close");
      exit(EXIT_FAILURE);
    }
    exit(EXIT_FAILURE);
  }

  memset((char *)&serveur1, 0, length);
  serveur1.sin_family = AF_INET;
  serveur1.sin_port = htons(PORT_1);
  serveur1.sin_addr.s_addr = htonl(INADDR_ANY);

  memset((char *)&serveur2, 0, length);
  serveur2.sin_family = AF_INET;
  serveur2.sin_port = htons(PORT_2);
  serveur2.sin_addr.s_addr = htonl(INADDR_ANY);

  memset((char *)&infos, 0, sizeof(infos_t));
  infos.type = DATA;
  infos.id = MAX_TAB_SIZE;
  infos.port = s_data.sin_port;
  strcpy(infos.data, argv[2]);

  liste = listec_data_nouv();

  sd_output_debut(argv[2]);

  if (connect_init(socketfd, &serveur1, &infos) == 1) {
    if (close(socketfd) == -1) {
      perror("close");
      exit(EXIT_FAILURE);
    }
    sd_output_fin(argv[1]);
    return EXIT_SUCCESS;
  }

  if (infos.statut == SYNC) {
    syncbln = 1;
    if (instr_sync(socketfd, &serveur2, &infos) == 1) {
      if (close(socketfd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
      }
      sd_output_fin(argv[1]);
      return EXIT_SUCCESS;
    }
  }

  while (!quit) {
    FD_ZERO(&set);
    FD_SET(STDIN_FILENO, &set);
    FD_SET(socketfd, &set);

    memset((char *)&data, 0, sizeof(data_t));
    memset((char *)&demande, 0, sizeof(demande_t));

    if (select(socketfd+1, &set, NULL, NULL, NULL) == -1) {
      perror("select");
      if (close(socketfd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
      }
      exit(EXIT_FAILURE);
    }

    if (FD_ISSET(STDIN_FILENO, &set)) {
      if (fgets(buf, TMP_STRING_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error: fgets\n");
        if (close(socketfd) == -1) {
          perror("close");
          exit(EXIT_FAILURE);
        }
        exit(EXIT_FAILURE);
      }

      if (strcmp(buf, "quit\n") == 0) {
        quit = 1;
      }
      else if (strcmp(buf, "list\n") == 0) {
        listec_data_affiche(liste);
      }
      else sd_output_commande();
    }

    if (FD_ISSET(socketfd, &set)) {
      if(recvfrom(socketfd, &demande, sizeof(demande_t), 0, (struct sockaddr *)&client, (socklen_t *)&length) == -1) {
        perror("recvfrom");
        if (close(socketfd) == -1) {
          perror("close");
          exit(EXIT_FAILURE);
        }
        exit(EXIT_FAILURE);
      }

      sd_output_demande(demande);

      if ((demande.arg == LIRE) && (!syncbln)){
        data.statut = VALIDE;
        custom_cat_data(data.string, "# READ - \e[36m");
        custom_cat_data(data.string, argv[2]);
        custom_cat_data(data.string, "\e[33m\n");
        listetmp = liste;
        if (listetmp == NULL) {
          custom_cat_data(data.string, "\e[31m| No users to read\e[33m\n");
        }
        while (listetmp != NULL) {
          custom_cat_data(data.string, "| User: \e[36m");
          custom_cat_data(data.string, listetmp->utilisateur);
          custom_cat_data(data.string, "\e[33m - Value: \e[36m");
          custom_cat_data(data.string, listetmp->valeur);
          custom_cat_data(data.string, "\e[33m\n");
          listetmp = listetmp->suiv;
        }
      }
      else if ((demande.arg == ECRIRE) && (!syncbln)) {
        data.statut = VALIDE;
        custom_cat_data(data.string, "# WRITE - \e[36m");
        custom_cat_data(data.string, argv[2]);
        custom_cat_data(data.string, "\e[33m\n");
        if ((listetmp = listec_data_rech(liste, demande.utilisateur)) == NULL) {
          if ((listetmp = listec_data_adjt(liste)) == NULL) data.statut = ERREUR;
          else liste = listetmp;
        }
        if (data.statut == VALIDE) {
          strcpy(listetmp->utilisateur, demande.utilisateur);
          strcpy(listetmp->valeur, demande.valeur);
          custom_cat_data(data.string, "| User: \e[36m");
          custom_cat_data(data.string, demande.utilisateur);
          custom_cat_data(data.string, "\e[33m | Value: \e[36m");
          custom_cat_data(data.string, demande.valeur);
          custom_cat_data(data.string, "\e[33m\n");
        }
        else fprintf(stdout, "\e[0m\e[31m| Write error\e[39m\n");
      }
      else if ((demande.arg == SUPPRIMER) && (!syncbln)) {
        data.statut = VALIDE;
        custom_cat_data(data.string, "# DELETE - \e[36m");
        custom_cat_data(data.string, argv[2]);
        custom_cat_data(data.string, "\e[33m\n");
        if ((listetmp = listec_data_rech(liste, demande.utilisateur)) == NULL) {
          custom_cat_data(data.string, "\e[31m| No data for \e[33m");
          custom_cat_data(data.string, demande.utilisateur);
        }
        else {
          custom_cat_data(data.string, "| User: \e[36m");
          custom_cat_data(data.string, listetmp->utilisateur);
          custom_cat_data(data.string, "\e[33m - Value: \e[36m");
          custom_cat_data(data.string, listetmp->valeur);
          liste = listec_data_supn(liste, demande.utilisateur);
        }
        custom_cat_data(data.string, "\e[33m\n");
      }
      else if (demande.arg == SYNC_INIT) {
        if (sync_init(socketfd, &serveur2, liste) == 1) fprintf(stdout, "\e[0m\e[31m| Synchronisation error\e[39m\n\n");
        else fprintf(stdout, "\e[0m\e[32m| Synchronisation complete\e[39m\n\n");
      }
      else if (demande.arg == SYNC_PROC) {
        data.statut = VALIDE;
        if ((liste = listec_data_adjt(liste)) == NULL) data.statut = ERREUR;
        else {
          strcpy(liste->utilisateur, demande.utilisateur);
          strcpy(liste->valeur, demande.valeur);
        }
      }
      else if (demande.arg == SYNC_FIN) {
        syncbln = 0;
        data.statut = VALIDE;
        infos.statut = CONNECTE;
      }
      else quit = 1;

      if (demande.arg != SYNC_INIT) {
        if (sendto(socketfd, &data, sizeof(data_t), 0, (struct sockaddr *)&serveur2, (socklen_t) length) == -1) {
          perror("sendto");
          if (close(socketfd) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
          }
          exit(EXIT_FAILURE);
        }
      }
    }
  }

  listec_data_free(liste);

  if (connect_fin(socketfd, &serveur1, &infos) == 1) {
    if (close(socketfd) == -1) {
      perror("close");
      exit(EXIT_FAILURE);
    }
    sd_output_fin(argv[2]);
    return EXIT_SUCCESS;
  }

  if (close(socketfd) == -1) {
    perror("close");
    exit(EXIT_FAILURE);
  }

  sd_output_fin(argv[2]);

  return EXIT_SUCCESS;
}
