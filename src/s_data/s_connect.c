#include "s_connect.h"

unsigned int connect_init (int socketfd, struct sockaddr_in *serveur, infos_t *infos) {
  size_t length = sizeof(struct sockaddr_in);
  fd_set set;
  struct timeval timeout;
  int tmp;
  unsigned int cpt;

  FD_ZERO(&set);
  FD_SET(socketfd, &set);

  cpt = 0;

  timeout.tv_sec = TIMEOUT;
  timeout.tv_usec = 0;

  infos->statut = CONNEXION;

  while (cpt < MAX_SEND) {
    if (sendto(socketfd, &(*infos), sizeof(infos_t), 0, (struct sockaddr *)&(*serveur), (socklen_t) length) == -1) {
      perror("sendto");
      if (close(socketfd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
      }
      exit(EXIT_FAILURE);
    }

    if ((tmp = select(socketfd+1, &set, NULL, NULL, &timeout)) == -1) {
      perror("select");
      if (close(socketfd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
      }
      exit(EXIT_FAILURE);
    }

    if (tmp > 0) {
      if (FD_ISSET(socketfd, &set)) {
        if (recvfrom(socketfd, &(*infos), sizeof(infos_t), 0, (struct sockaddr *)&(*serveur), (socklen_t *)&length) == -1) {
          perror("recvfrom");
          if (close(socketfd) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
          }
          exit(EXIT_FAILURE);
        }

        if (infos->statut == CONNECTE) {
          sd_output_en_ligne();
          return 0;
        }
        else if (infos->statut == SYNC) {
          sd_output_en_ligne();
          return 0;
        }
        else if (infos->statut == SURCHARGE) {
          sd_output_surcharge();
          return 1;
        }
        else {
          sd_output_erreur();
          return 1;
        }
      }
    }
    else {
      cpt++;
    }
  }

  sd_output_hors_ligne();
  return 1;
}

unsigned int connect_fin (int socketfd, struct sockaddr_in *serveur, infos_t *infos) {
  size_t length = sizeof(struct sockaddr_in);
  fd_set set;
  struct timeval timeout;
  int tmp;
  unsigned int cpt;

  FD_ZERO(&set);
  FD_SET(socketfd, &set);

  cpt = 0;

  timeout.tv_sec = TIMEOUT;
  timeout.tv_usec = 0;

  infos->statut = DECONNEXION;

  while (cpt < MAX_SEND) {
    if (sendto(socketfd, &(*infos), sizeof(infos_t), 0, (struct sockaddr *)&(*serveur), (socklen_t) length) == -1) {
      perror("sendto");
      if (close(socketfd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
      }
      exit(EXIT_FAILURE);
    }

    if ((tmp = select(socketfd+1, &set, NULL, NULL, &timeout)) == -1) {
      perror("select");
      if (close(socketfd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
      }
      exit(EXIT_FAILURE);
    }

    if (tmp > 0) {
      if (FD_ISSET(socketfd, &set)) {
        if (recvfrom(socketfd, &(*infos), sizeof(infos_t), 0, (struct sockaddr *)&(*serveur), (socklen_t *)&length) == -1) {
          perror("recvfrom");
          if (close(socketfd) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
          }
          exit(EXIT_FAILURE);
        }

        if (infos->statut == DECONNECTE) {
          infos->id = MAX_TAB_SIZE;
          return 0;
        }
        else {
          sd_output_erreur();
          return 1;
        }
      }
    }
    else {
      cpt++;
    }
  }

  sd_output_hors_ligne();
  return 1;
}

unsigned int instr_sync (int socketfd, struct sockaddr_in *serveur, infos_t *infos) {
  size_t length = sizeof(struct sockaddr_in);
  instr_t instr;
  data_t data;
  struct timeval timeout;
  fd_set set;
  int tmp;
  unsigned int cpt;

  timeout.tv_sec = TIMEOUT;
  timeout.tv_usec = 0;

  cpt = 0;

  FD_ZERO(&set);
  FD_SET(socketfd, &set);

  memset((char *)&instr, 0, sizeof(instr_t));
  memset((char *)&data, 0, sizeof(data_t));

  instr.id = infos->id;
  instr.arg = SYNC_INIT;

  while (cpt < MAX_SEND) {
    if (sendto(socketfd, &instr, sizeof(instr_t), 0, (struct sockaddr *)&(*serveur), (socklen_t) length) == -1) {
      perror("sendto");
      if (close(socketfd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
      }
      exit(EXIT_FAILURE);
    }

    if ((tmp = select(socketfd+1, &set, NULL, NULL, &timeout)) == -1) {
      perror("select");
      if (close(socketfd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
      }
      exit(EXIT_FAILURE);
    }

    if (tmp > 0) {
      if (FD_ISSET(socketfd, &set)) {
        if (recvfrom(socketfd, &data, sizeof(data_t), 0, (struct sockaddr *)&(*serveur), (socklen_t *)&length) == -1) {
          perror("recvfrom");
          if (close(socketfd) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
          }
          exit(EXIT_FAILURE);
        }

        if (data.statut == VALIDE) {
          sd_output_sync();
          return 0;
        }
        else {
          sd_output_erreur();
          return 1;
        }
      }
    }
    else {
      cpt++;
    }
  }

  sd_output_hors_ligne();
  return 1;
}

unsigned int sync_init (int socketfd, struct sockaddr_in *serveur, listec_data_t liste) {
  size_t length = sizeof(struct sockaddr_in);
  struct timeval timeout;
  listec_data_t cur;
  unsigned int fin, cpt;
  instr_t instr;
  data_t data;
  fd_set set;
  int tmp;

  cur = liste;
  fin = 0;

  timeout.tv_sec = TIMEOUT;
  timeout.tv_usec = 0;

  while (!fin) {
    FD_ZERO(&set);
    FD_SET(socketfd, &set);

    cpt = 0;

    memset((char *)&instr, 0, sizeof(instr_t));
    memset((char *)&data, 0, sizeof(data_t));
    instr.id = MAX_TAB_SIZE;

    if (cur == NULL) {
      fin = 1;
      instr.arg = SYNC_FIN;
    }
    else {
      instr.arg = SYNC_PROC;
      strcpy(instr.champs[0], cur->utilisateur);
      strcpy(instr.valeurs[0], cur->valeur);
    }

    while (cpt < MAX_SEND) {
      if (sendto(socketfd, &instr, sizeof(instr_t), 0, (struct sockaddr *)&(*serveur), (socklen_t) length) == -1) {
        perror("sendto");
        if (close(socketfd) == -1) {
          perror("close");
          exit(EXIT_FAILURE);
        }
        exit(EXIT_FAILURE);
      }

      if ((tmp = select(socketfd+1, &set, NULL, NULL, &timeout)) == -1) {
        perror("select");
        if (close(socketfd) == -1) {
          perror("close");
          exit(EXIT_FAILURE);
        }
        exit(EXIT_FAILURE);
      }

      if (tmp > 0) {
        if (FD_ISSET(socketfd, &set)) {
          if (recvfrom(socketfd, &data, sizeof(data_t), 0, (struct sockaddr *)&(*serveur), (socklen_t *)&length) == -1) {
            perror("recvfrom");
            if (close(socketfd) == -1) {
              perror("close");
              exit(EXIT_FAILURE);
            }
            exit(EXIT_FAILURE);
          }

          if (data.statut == VALIDE) {
            if (!fin) cur = cur->suiv;
            cpt = MAX_SEND+1;
          }
          else {
            return 1;
          }
        }
      }
      else {
        cpt++;
      }
    }

    if (cpt == MAX_SEND) {
      return 1;
    }
  }

  return 0;
}
