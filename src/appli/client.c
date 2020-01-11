#include "client.h"

unsigned int client_init (int socketfd, struct sockaddr_in *serveur, infos_t *infos) {
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
          output_en_ligne();
          return 0;
        }
        else {
          output_erreur();
          return 1;
        }
      }
    }
    else {
      cpt++;
    }
  }

  output_hors_ligne();
  return 1;
}

unsigned int client_fin (int socketfd, struct sockaddr_in *serveur, infos_t *infos) {
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
          return 0;
        }
        else {
          output_erreur();
          return 1;
        }
      }
    }
    else {
      cpt++;
    }
  }

  output_deconexion();
  return 1;
}

unsigned int authentification (int socketfd, struct sockaddr_in *serveur, infos_t *infos) {
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

  infos->statut = AUTHENTIFICATION;

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

        if (infos->statut == AUTHENTIFIE) {
          return 0;
        }
        else if (infos->statut == AUTHENTIFICATION) {
          output_auth_err();
          return 1;
        }
        else if (infos->statut == SURCHARGE) {
          output_surcharge();
          return 1;
        }
        else {
          output_erreur();
          return 1;
        }
      }
    }
    else {
      cpt++;
    }
  }

  output_deconexion();
  return 2;
}

unsigned int desauthentification (int socketfd, struct sockaddr_in *serveur, infos_t *infos) {
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

  infos->statut = DESAUTHENTIFICATION;

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

        if (infos->statut == DESAUTHENTIFIE) {
          infos->id = MAX_TAB_SIZE;
          output_desauth();
          return 0;
        }
        else {
          output_erreur();
          return 1;
        }
      }
    }
    else {
      cpt++;
    }
  }

  output_deconexion();
  return 2;
}

unsigned int instructions (int socketfd, struct sockaddr_in *serveur, unsigned int id) {
  size_t length = sizeof(struct sockaddr_in), len;
  fd_set set;
  struct timeval timeout;
  int tmp;
  char ligne[MAX_STRING_SIZE], *arg, champ[S_DATA_NUMBER][NRML_STRING_SIZE], *str;
  unsigned int i, cpt;
  instr_t instr;
  data_t data;

  timeout.tv_sec = TIMEOUT;
  timeout.tv_usec = 0;

  FD_ZERO(&set);
  FD_SET(socketfd, &set);

  cpt = 0;

  memset((char *)&champ, 0, S_DATA_NUMBER*NRML_STRING_SIZE*sizeof(char));
  memset((char *)&instr, 0, sizeof(instr_t));
  memset((char *)&data, 0, sizeof(data_t));
  instr.id = id;

  fprintf(stdout, "\e[0m\e[36m| \e[0m\e[39m");

  if (fgets(ligne, MAX_STRING_SIZE, stdin) == NULL) {
    fprintf(stderr, "Error: fgets\n");
    exit(EXIT_FAILURE);
  }

  if (*ligne == '\n') {
    fprintf(stdout, "\e[0m\e[31m| Enter at least one instruction!\e[39m\n");
    return 1;
  }

  if ((len = strlen(ligne)) > TMP_STRING_SIZE) {
    fprintf(stdout, "\e[0m\e[31m| The maximum character count is %d!\e[39m\n", TMP_STRING_SIZE);
    return 1;
  }

  input_newline(ligne, len-1);

  if ((arg = strtok(ligne, " ")) == NULL) {
    output_instr_err();
    return 1;
  }

  i = 0;
  str = strtok(NULL, " ");
  while ((str != NULL) && (*str != '\n')) {
    if (i == S_DATA_NUMBER) {
      output_instr_overflow();
      break;
    }
    strcpy(champ[i], str);
    i++;
    str = strtok(NULL, " ");
  }

  if ((strcmp(arg, "quit") == 0) && (champ[0][0] == '\0')) {
    return 3;
  }
  else if (strcmp(arg, "read") == 0) {
    instr.arg = LIRE;
    if (champ[0][0] == '\0') {
      output_instr_err();
      return 1;
    }
    for (i = 0; (champ[i][0] != '\0') && (i < S_DATA_NUMBER); i++) {
      for (unsigned int j = 0; j < i; j++) {
        if (strcmp(instr.champs[j], champ[i]) == 0) {
          output_instr_champs();
          return 1;
        }
      }
      strcpy(instr.champs[i], champ[i]);
    }
  }
  else if (strcmp(arg, "write") == 0) {
    instr.arg = ECRIRE;
    if (champ[0][0] == '\0') {
      output_instr_err();
      return 1;
    }
    for (i = 0; (champ[i][0] != '\0') && (i < S_DATA_NUMBER); i++) {
      if ((str = strtok(champ[i], ":")) == NULL) {
        output_instr_err();
        return 1;
      }
      for (unsigned int j = 0; j < i; j++) {
        if (strcmp(instr.champs[j], str) == 0) {
          output_instr_champs();
          return 1;
        }
      }
      strcpy(instr.champs[i], str);
      if ((str = strtok(NULL, "!")) == NULL) {
        output_instr_err();
        return 1;
      }
      if (strstr(str, BDD_DELIM) != NULL) {
        fprintf(stdout, "\e[28m\e[31m| Do not write the character %s in your values!\e[39m\n", BDD_DELIM);
        return 1;
      }
      strcpy(instr.valeurs[i], str);
    }
  }
  else if ((strcmp(arg, "delete") == 0) && (champ[0][0] == '\0')) {
    instr.arg = SUPPRIMER;
  }
  else {
    output_instr_err();
    return 1;
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
          fprintf(stdout, "\n\e[0m\e[33m");
          fprintf(stdout, "%s", data.string);
          fprintf(stdout, "\e[0m\e[39m\n");
          return 0;
        }
        else if (data.statut == NONVALIDE) {
          fprintf(stdout, "\e[0m\e[31m| %s\e[0m\e[39m\n", data.string);
          return 0;
        }
        else {
          fprintf(stdout, "\e[0m\e[31m| A backend error has occured!\e[0m\e[39m\n");
          return 1;
        }
      }
    }
    else {
      cpt++;
    }
  }

  output_deconexion();
  return 2;
}
