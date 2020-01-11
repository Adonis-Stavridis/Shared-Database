#include "s_acces.h"

listec_bdd_t bdd;
liste_infos_t clients;
liste_infos_t s_data;
unsigned int quit = 0;

int main (int argc, char const *argv[]) {
  pthread_t tid;
  socklist_t socklist;
  struct sockaddr_in serveur1, serveur2, client;
  size_t length = sizeof(struct sockaddr_in);
  fd_set set;
  char tmp[TMP_STRING_SIZE];
  unsigned int ind;
  infos_t infostmp;

  if (argc != 1) {
    fprintf(stderr, "%s doesn't take any argument\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  s_output_debut();

  if ((bdd = bdd_init()) == NULL) {
    fprintf(stderr, "Error: bdd_init\n");
    exit(EXIT_FAILURE);
  }

  if ((socklist.tab[0] = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  memset((char *)&serveur1, 0, length);
  serveur1.sin_family = AF_INET;
  serveur1.sin_port = htons(PORT_1);
  serveur1.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(socklist.tab[0], (struct sockaddr *)&serveur1, (socklen_t) length) == -1) {
    perror("bind");
    if (close(socklist.tab[0]) == -1) {
      perror("close");
      exit(EXIT_FAILURE);
    }
    exit(EXIT_FAILURE);
  }

  if ((socklist.tab[1] = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
    perror("socket");
    if (close(socklist.tab[0]) == -1) {
      perror("close");
      exit(EXIT_FAILURE);
    }
    exit(EXIT_FAILURE);
  }

  memset((char *)&serveur2, 0, length);
  serveur2.sin_family = AF_INET;
  serveur2.sin_port = htons(PORT_2);
  serveur2.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(socklist.tab[1], (struct sockaddr *)&serveur2, (socklen_t) length) == -1) {
    perror("bind");
    if (close(socklist.tab[0]) == -1) {
      perror("close");
      if (close(socklist.tab[1]) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
      }
      exit(EXIT_FAILURE);
    }
    if (close(socklist.tab[1]) == -1) {
      perror("close");
      exit(EXIT_FAILURE);
    }
    exit(EXIT_FAILURE);
  }

  memset((char *)&client, 0, length);

  liste_init(&clients);
  liste_init(&s_data);

  if ((errno = pthread_create(&tid, NULL, s_comm, &socklist)) != 0) {
    perror("pthread_create");
    if (close(socklist.tab[0]) == -1) {
      perror("close");
      if (close(socklist.tab[1]) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
      }
      exit(EXIT_FAILURE);
    }
    if (close(socklist.tab[1]) == -1) {
      perror("close");
      exit(EXIT_FAILURE);
    }
    exit(EXIT_FAILURE);
  }

  while (!quit) {
    FD_ZERO(&set);
    FD_SET(STDIN_FILENO, &set);
    FD_SET(socklist.tab[0], &set);

    if (select(socklist.tab[0]+1, &set, NULL, NULL, NULL) == -1) {
      perror("select");
      if (close(socklist.tab[0]) == -1) {
        perror("close");
        if (close(socklist.tab[1]) == -1) {
          perror("close");
          exit(EXIT_FAILURE);
        }
        exit(EXIT_FAILURE);
      }
      if (close(socklist.tab[1]) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
      }
      exit(EXIT_FAILURE);
    }

    if (FD_ISSET(socklist.tab[0], &set)) {
      if(recvfrom(socklist.tab[0], &infostmp, sizeof(infos_t), 0, (struct sockaddr *)&client, (socklen_t *)&length) == -1) {
        perror("recvfrom");
        if (close(socklist.tab[0]) == -1) {
          perror("close");
          if (close(socklist.tab[1]) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
          }
          exit(EXIT_FAILURE);
        }
        if (close(socklist.tab[1]) == -1) {
          perror("close");
          exit(EXIT_FAILURE);
        }
        exit(EXIT_FAILURE);
      }

      if (infostmp.type == CLIENT) {
        if (infostmp.statut == CONNEXION) {
          infostmp.statut = CONNECTE;
        }
        else if (infostmp.statut == AUTHENTIFICATION) {
          if ((ind = verif_coordonnees(bdd, infostmp.coord)) == 0) {
            liste_ajout(&clients, &infostmp);
          }
        }
        else if (infostmp.statut == DESAUTHENTIFICATION) {
          liste_sup(&clients, &infostmp);
        }
        else if (infostmp.statut == DECONNEXION) {
          infostmp.statut = DECONNECTE;
        }
        else infostmp.statut = ERREUR;
      }
      else if (infostmp.type == DATA) {
        if (infostmp.statut == CONNEXION) {
          if (liste_rech_data(&s_data, infostmp.data) == 0) {
            liste_ajout(&s_data, &infostmp);
            s_data.tab[infostmp.id].statut = SYNC;
            infostmp.statut = SYNC;
          }
          else liste_ajout(&s_data, &infostmp);
        }
        else if (infostmp.statut == DECONNEXION) {
          liste_sup(&s_data, &infostmp);
        }
        else infostmp.statut = ERREUR;
      }
      else {
        infostmp.statut = ERREUR;
        s_output_message();
      }

      s_output_infos(&infostmp);

      if (sendto(socklist.tab[0], &infostmp, sizeof(infos_t), 0, (struct sockaddr *)&client, (socklen_t) length) == -1) {
        perror("sendto");
        if (close(socklist.tab[0]) == -1) {
          perror("close");
          if (close(socklist.tab[1]) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
          }
          exit(EXIT_FAILURE);
        }
        if (close(socklist.tab[1]) == -1) {
          perror("close");
          exit(EXIT_FAILURE);
        }
        exit(EXIT_FAILURE);
      }
    }

    if (FD_ISSET(STDIN_FILENO, &set)) {
      if (fgets(tmp, TMP_STRING_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error: fgets\n");
        if (close(socklist.tab[0]) == -1) {
          perror("close");
          if (close(socklist.tab[1]) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
          }
          exit(EXIT_FAILURE);
        }
        if (close(socklist.tab[1]) == -1) {
          perror("close");
          exit(EXIT_FAILURE);
        }
        exit(EXIT_FAILURE);
      }

      if (strcmp(tmp, "quit\n") == 0) {
        quit = 1;
      }
      else if (strcmp (tmp, "clients\n") == 0) {
        liste_affiche_clients(&clients);
      }
      else if (strcmp (tmp, "datas\n") == 0) {
        liste_affiche_data(&s_data);
      }
      else if (strcmp (tmp, "users\n") == 0) {
        listec_bdd_affiche(bdd);
      }
      else {
        s_output_commande();
      }
    }
  }

  fprintf(stdout, "\e[1m\e[36m-> Waiting for the thread to end\e[0m\e[39m\n");

  if ((errno = pthread_join(tid, NULL)) != 0) {
    perror("pthread_join");
    if (close(socklist.tab[0]) == -1) {
      perror("close");
      if (close(socklist.tab[1]) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
      }
      exit(EXIT_FAILURE);
    }
    if (close(socklist.tab[1]) == -1) {
      perror("close");
      exit(EXIT_FAILURE);
    }
    exit(EXIT_FAILURE);
  }

  bdd_fin(bdd);

  if (close(socklist.tab[0]) == -1) {
    perror("close");
    if (close(socklist.tab[1]) == -1) {
      perror("close");
      exit(EXIT_FAILURE);
    }
    exit(EXIT_FAILURE);
  }

  if (close(socklist.tab[1]) == -1) {
    perror("close");
    exit(EXIT_FAILURE);
  }

  s_output_fin();

  return EXIT_SUCCESS;
}
