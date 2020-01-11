#include "s_output.h"

void s_output_debut () {
  fprintf(stdout, "\e[1m\e[36m");
  fprintf(stdout, "========== Start of server ==========");
  fprintf(stdout, "\e[0m\e[39m\n\n");
}

void s_output_fin () {
  fprintf(stdout, "\n\e[1m\e[36m");
  fprintf(stdout, "========== End of server ============");
  fprintf(stdout, "\e[0m\e[39m\n");
}

void s_output_infos (infos_t *infos) {
  if (infos->statut == CONNECTE) {
    fprintf(stdout, "\e[1m\e[32m");
    fprintf(stdout, "| Connected: ");
    fprintf(stdout, "\e[0m\e[39m");
  }
  if (infos->statut == AUTHENTIFICATION) {
    fprintf(stdout, "\e[1m\e[31m");
    fprintf(stdout, "| Failed to log in: ");
    fprintf(stdout, "\e[0m\e[39m");
  }
  if (infos->statut == AUTHENTIFIE) {
    fprintf(stdout, "\e[1m\e[32m");
    fprintf(stdout, "| Logged in: ");
    fprintf(stdout, "\e[0m\e[39m");
  }
  if (infos->statut == DESAUTHENTIFIE) {
    fprintf(stdout, "\e[1m\e[31m");
    fprintf(stdout, "| Logged out: ");
    fprintf(stdout, "\e[0m\e[39m");
  }
  if (infos->statut == DECONNECTE) {
    fprintf(stdout, "\e[1m\e[31m");
    fprintf(stdout, "| Disconnected: ");
    fprintf(stdout, "\e[0m\e[39m");
  }
  if (infos->statut == SURCHARGE) {
    fprintf(stdout, "\e[1m\e[31m");
    fprintf(stdout, "| Overload: ");
    fprintf(stdout, "\e[0m\e[39m");
  }
  if (infos->statut == SYNC) {
    fprintf(stdout, "\e[1m\e[36m");
    fprintf(stdout, "| Synchronised: ");
    fprintf(stdout, "\e[0m\e[39m");
  }
  if (infos->statut == ERREUR) {
    fprintf(stdout, "\e[1m\e[31m");
    fprintf(stdout, "| Error: ");
    fprintf(stdout, "\e[0m\e[39m");
  }
  if (infos->type == CLIENT) {
    fprintf(stdout, "\e[0m\e[36m");
    fprintf(stdout, "CLIENT");
  }
  if (infos->type == DATA) {
    fprintf(stdout, "\e[0m\e[33m");
    fprintf(stdout, "DATA");
  }
  fprintf(stdout, " |Port: %hu", infos->port);
  if ((infos->type == CLIENT) && (infos->statut == AUTHENTIFIE) && (infos->coord.utilisateur[0] != '\0')) fprintf(stdout, " |User: %s", infos->coord.utilisateur);
  if (infos->type == DATA) fprintf(stdout, " |Data: %s", infos->data);
  fprintf(stdout, "\e[0m\e[39m\n");
}

void s_output_message () {
  fprintf(stdout, "\e[1m\e[31m");
  fprintf(stdout, "/!\\ Recieved unknown message! /!\\");
  fprintf(stdout, "\e[0m\e[39m\n");
}

void s_output_commande () {
  fprintf(stdout, "\e[1m\e[31m");
  fprintf(stdout, "-> Unknown instruction");
  fprintf(stdout, "\e[0m\e[39m\n");
}

void s_output_champ_overflow (char *string) {
  fprintf(stdout, "\e[0m\e[31m| Too many fields for %s: processing only first %d fields!\e[0m\e[39m\n", string, S_DATA_NUMBER);
}
