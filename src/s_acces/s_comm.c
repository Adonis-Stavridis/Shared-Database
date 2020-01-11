#include "s_comm.h"

void *s_comm (void *arg) {
  socklist_t *socklist = arg;
  struct sockaddr_in client, s_datatmp;
  size_t length = sizeof(struct sockaddr_in);
  struct timeval timeout1, timeout2;
  fd_set set1, set2;
  unsigned int bln, n_ports, j, to_sync, cpt;
  int tmp1, tmp2;
  instr_t instr;
  data_t data, datatmp;
  unsigned short ports[MAX_TAB_SIZE];
  demande_t demande;

  timeout1.tv_sec = TIMEOUT*30;
  timeout1.tv_usec = 0;

  timeout2.tv_sec = TIMEOUT;
  timeout2.tv_usec = 0;

  while (!quit) {
    FD_ZERO(&set1);
    FD_SET(socklist->tab[1], &set1);

    memset((char *)&instr, 0, sizeof(instr_t));
    memset((char *)&data, 0, sizeof(data_t));
    memset((char *)&datatmp, 0, sizeof(data_t));
    memset((char *)&s_datatmp, 0, length);
    s_datatmp.sin_family = AF_INET;
    if (inet_aton(LOC_ADR, &s_datatmp.sin_addr) == 0) {
      fprintf(stderr, "inet_aton\n");
      if (close(socklist->tab[0]) == -1) {
        perror("close");
        if (close(socklist->tab[1]) == -1) {
          perror("close");
          exit(EXIT_FAILURE);
        }
        exit(EXIT_FAILURE);
      }
      if (close(socklist->tab[1]) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
      }
      exit(EXIT_FAILURE);
    }
    memset((char *)&demande, 0, sizeof(demande_t));

    if ((tmp1 = select(socklist->tab[1]+1, &set1, NULL, NULL, &timeout1)) == -1) {
      perror("select");
      if (close(socklist->tab[0]) == -1) {
        perror("close");
        if (close(socklist->tab[1]) == -1) {
          perror("close");
          exit(EXIT_FAILURE);
        }
        exit(EXIT_FAILURE);
      }
      if (close(socklist->tab[1]) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
      }
      exit(EXIT_FAILURE);
    }

    if (tmp1 > 0) {
      if (FD_ISSET(socklist->tab[1], &set1)) {
        if(recvfrom(socklist->tab[1], &instr, sizeof(instr_t), 0, (struct sockaddr *)&client, (socklen_t *)&length) == -1) {
          perror("recvfrom");
          if (close(socklist->tab[0]) == -1) {
            perror("close");
            if (close(socklist->tab[1]) == -1) {
              perror("close");
              exit(EXIT_FAILURE);
            }
            exit(EXIT_FAILURE);
          }
          if (close(socklist->tab[1]) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
          }
          exit(EXIT_FAILURE);
        }

        bln = 0;
        if (instr.arg == SYNC_INIT) {
          memset((char *)&ports, 0, MAX_TAB_SIZE*sizeof(unsigned short));
          if ((n_ports = get_data_ports_diff(&s_data, ports, s_data.tab[instr.id].data, instr.id)) == 0) {
            fprintf(stderr, "Error: get_data_ports_diff\n");
            exit(EXIT_FAILURE);
          }
          demande.arg = instr.arg;
          to_sync = instr.id;

          memset((char *)&s_datatmp.sin_port, 0, sizeof(unsigned short));
          s_datatmp.sin_port = ports[0];

          if (sendto(socklist->tab[1], &demande, sizeof(demande_t), 0, (struct sockaddr *)&s_datatmp, (socklen_t) length) == -1) {
            perror("sendto");
            if (close(socklist->tab[0]) == -1) {
              perror("close");
              if (close(socklist->tab[1]) == -1) {
                perror("close");
                exit(EXIT_FAILURE);
              }
              exit(EXIT_FAILURE);
            }
            if (close(socklist->tab[1]) == -1) {
              perror("close");
              exit(EXIT_FAILURE);
            }
            exit(EXIT_FAILURE);
          }

          data.statut = VALIDE;
          bln = 1;
        }

        if ((instr.arg == SYNC_PROC) || (instr.arg == SYNC_FIN)) {
          demande.arg = instr.arg;
          strcpy(demande.utilisateur, instr.champs[0]);
          strcpy(demande.valeur, instr.valeurs[0]);

          memset((char *)&s_datatmp.sin_port, 0, sizeof(unsigned short));
          s_datatmp.sin_port = s_data.tab[to_sync].port;

          FD_ZERO(&set2);
          FD_SET(socklist->tab[1], &set2);

          cpt = 0;

          while (cpt < MAX_SEND) {
            if (sendto(socklist->tab[1], &demande, sizeof(demande_t), 0, (struct sockaddr *)&s_datatmp, (socklen_t) length) == -1) {
              perror("sendto");
              if (close(socklist->tab[0]) == -1) {
                perror("close");
                if (close(socklist->tab[1]) == -1) {
                  perror("close");
                  exit(EXIT_FAILURE);
                }
                exit(EXIT_FAILURE);
              }
              if (close(socklist->tab[1]) == -1) {
                perror("close");
                exit(EXIT_FAILURE);
              }
              exit(EXIT_FAILURE);
            }

            if ((tmp2 = select(socklist->tab[1]+1, &set2, NULL, NULL, &timeout2)) == -1) {
              perror("select");
              if (close(socklist->tab[0]) == -1) {
                perror("close");
                if (close(socklist->tab[1]) == -1) {
                  perror("close");
                  exit(EXIT_FAILURE);
                }
                exit(EXIT_FAILURE);
              }
              if (close(socklist->tab[1]) == -1) {
                perror("close");
                exit(EXIT_FAILURE);
              }
              exit(EXIT_FAILURE);
            }

            if (tmp2 > 0) {
              if(recvfrom(socklist->tab[1], &data, sizeof(data_t), 0, (struct sockaddr *)&s_datatmp, (socklen_t *)&length) == -1) {
                perror("recvfrom");
                if (close(socklist->tab[0]) == -1) {
                  perror("close");
                  if (close(socklist->tab[1]) == -1) {
                    perror("close");
                    exit(EXIT_FAILURE);
                  }
                  exit(EXIT_FAILURE);
                }
                if (close(socklist->tab[1]) == -1) {
                  perror("close");
                  exit(EXIT_FAILURE);
                }
                exit(EXIT_FAILURE);
              }

              if (data.statut == VALIDE) {
                s_data.tab[to_sync].statut = CONNECTE;
                cpt = MAX_SEND+1;
              }
              else {
                cpt = MAX_SEND;
              }
            }
            else {
              cpt++;
            }
          }
          if (cpt == MAX_SEND) {
            data.statut = ERREUR;
          }

          bln = 1;
        }

        //verif champs valides
        for (unsigned int i = 0; ((i < S_DATA_NUMBER) && (instr.champs[i][0] != '\0') && (!bln)); i++) {
          if (liste_rech_data(&s_data, instr.champs[i]) == 1) {
            data.statut = NONVALIDE;
            get_champs(&s_data, data.string);
            bln = 1;
          }
        }

        if (!bln) {
          if (set_utilisateur(&clients, instr.id, demande.utilisateur) == 1) {
            data.statut = ERREUR;
            bln = 1;
          }
        }

        if ((!bln) && (instr.arg == LIRE)) {
          for (unsigned int i = 0; ((i < S_DATA_NUMBER) && (instr.champs[i][0] != '\0')); i++) {
            if (verif_droits(bdd, clients.tab[instr.id].coord.utilisateur, instr.champs[i]) == 1) {
              if (!bln) {
                data.statut = NONVALIDE;
                custom_cat_acces(data.string, "You do not have permissions for\e[33m");
                bln = 1;
              }
              custom_cat_acces(data.string, " ");
              custom_cat_acces(data.string, instr.champs[i]);
            }
          }
        }

        if ((!bln) && (instr.arg == SUPPRIMER)) {
          if (set_champs(&s_data, instr.champs) == 0) {
            data.statut = NONVALIDE;
            get_champs(&s_data, data.string);
            bln = 1;
          }
        }

        if (!bln) {
          demande.arg = instr.arg;

          for (unsigned int i = 0; ((i < S_DATA_NUMBER) && (instr.champs[i][0] != '\0') && (!bln)); i++) {
            memset((char *)&demande.valeur, 0, NRML_STRING_SIZE*sizeof(char));
            if (instr.valeurs[i][0] != '\0') strcpy(demande.valeur, instr.valeurs[i]);

            memset((char *)&ports, 0, MAX_TAB_SIZE*sizeof(unsigned short));
            if ((n_ports = get_data_ports(&s_data, ports, instr.champs[i])) == 0) {
              data.statut = NONVALIDE;
              get_champs(&s_data, data.string);
              bln = 1;
            }

            if (!bln) {
              j = 0;

              while (j < n_ports) {
                FD_ZERO(&set2);
                FD_SET(socklist->tab[1], &set2);

                cpt = 0;

                memset((char *)&s_datatmp.sin_port, 0, sizeof(unsigned short));
                s_datatmp.sin_port = ports[j];

                while (cpt < MAX_SEND) {
                  if (sendto(socklist->tab[1], &demande, sizeof(demande_t), 0, (struct sockaddr *)&s_datatmp, (socklen_t) length) == -1) {
                    perror("sendto");
                    if (close(socklist->tab[0]) == -1) {
                      perror("close");
                      if (close(socklist->tab[1]) == -1) {
                        perror("close");
                        exit(EXIT_FAILURE);
                      }
                      exit(EXIT_FAILURE);
                    }
                    if (close(socklist->tab[1]) == -1) {
                      perror("close");
                      exit(EXIT_FAILURE);
                    }
                    exit(EXIT_FAILURE);
                  }

                  if ((tmp2 = select(socklist->tab[1]+1, &set2, NULL, NULL, &timeout2)) == -1) {
                    perror("select");
                    if (close(socklist->tab[0]) == -1) {
                      perror("close");
                      if (close(socklist->tab[1]) == -1) {
                        perror("close");
                        exit(EXIT_FAILURE);
                      }
                      exit(EXIT_FAILURE);
                    }
                    if (close(socklist->tab[1]) == -1) {
                      perror("close");
                      exit(EXIT_FAILURE);
                    }
                    exit(EXIT_FAILURE);
                  }

                  if (tmp2 > 0) {
                    if(recvfrom(socklist->tab[1], &datatmp, sizeof(data_t), 0, (struct sockaddr *)&s_datatmp, (socklen_t *)&length) == -1) {
                      perror("recvfrom");
                      if (close(socklist->tab[0]) == -1) {
                        perror("close");
                        if (close(socklist->tab[1]) == -1) {
                          perror("close");
                          exit(EXIT_FAILURE);
                        }
                        exit(EXIT_FAILURE);
                      }
                      if (close(socklist->tab[1]) == -1) {
                        perror("close");
                        exit(EXIT_FAILURE);
                      }
                      exit(EXIT_FAILURE);
                    }

                    if (datatmp.statut == ERREUR) {
                      j = n_ports;
                      bln = 1;
                    }
                    data.statut = datatmp.statut;
                    cpt = MAX_SEND+1;

                    if (instr.arg == LIRE) j = n_ports;
                    else j++;
                  }
                  else {
                    cpt++;
                  }
                }
                if (cpt == MAX_SEND) {
                  j = n_ports;
                  bln = 1;
                  data.statut = ERREUR;
                }
              }

              if (!bln) custom_cat_acces(data.string, datatmp.string);
            }
          }
        }

        if (sendto(socklist->tab[1], &data, sizeof(data_t), 0, (struct sockaddr *)&client, (socklen_t) length) == -1) {
          perror("sendto");
          if (close(socklist->tab[0]) == -1) {
            perror("close");
            if (close(socklist->tab[1]) == -1) {
              perror("close");
              exit(EXIT_FAILURE);
            }
            exit(EXIT_FAILURE);
          }
          if (close(socklist->tab[1]) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
          }
          exit(EXIT_FAILURE);
        }
      }
    }
  }

  pthread_exit(NULL);
}
