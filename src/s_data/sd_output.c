#include "sd_output.h"

void sd_output_debut (char *string) {
  fprintf(stdout, "\e[1m\e[36m");
  fprintf(stdout, "========== Start of server: %s ==========", string);
  fprintf(stdout, "\e[0m\e[39m\n\n");
}

void sd_output_fin (char *string) {
  fprintf(stdout, "\n\e[1m\e[36m");
  fprintf(stdout, "========== End of server: %s ============", string);
  fprintf(stdout, "\e[0m\e[39m\n");
}

void sd_output_en_ligne () {
  fprintf(stdout, "\e[1m\e[93m");
  fprintf(stdout, "@ Server status: ");
  fprintf(stdout, "\e[0m\e[39m");
  fprintf(stdout, "\e[1m\e[32m\e[5m");
  fprintf(stdout, "Online");
  fprintf(stdout, "\e[0m\e[39m\e[25m\n\n");
}

void sd_output_hors_ligne () {
  fprintf(stdout, "\e[1m\e[93m");
  fprintf(stdout, "@ Server status: ");
  fprintf(stdout, "\e[0m\e[39m");
  fprintf(stdout, "\e[1m\e[31m\e[5m");
  fprintf(stdout, "Offline");
  fprintf(stdout, "\e[0m\e[39m\e[25m\n");
  fprintf(stdout, "\e[1m\e[31m");
  fprintf(stdout, "-----> Closing the server");
  fprintf(stdout, "\e[0m\e[39m\n");
  sleep(SLEEP);
}

void sd_output_surcharge () {
  fprintf(stdout, "\n\e[1m\e[93m");
  fprintf(stdout, "@ Server status: ");
  fprintf(stdout, "\e[0m\e[39m");
  fprintf(stdout, "\e[1m\e[31m\e[5m");
  fprintf(stdout, "Surcharge");
  fprintf(stdout, "\e[0m\e[39m\e[25m\n");
  fprintf(stdout, "\e[1m\e[31m");
  fprintf(stdout, "-----> Please try again later!");
  fprintf(stdout, "\e[0m\e[39m\n\n");
}

void sd_output_erreur () {
  fprintf(stdout, "\e[1m\e[31m");
  fprintf(stdout, "-----> A backend error has occured!");
  fprintf(stdout, "\e[0m\e[39m\n\n");
}

void sd_output_commande () {
  fprintf(stdout, "\e[1m\e[31m");
  fprintf(stdout, "-> Unknown instruction");
  fprintf(stdout, "\e[0m\e[39m\n");
}

void sd_output_demande (demande_t demande) {
  if (demande.arg == LIRE) fprintf(stdout, "\e[0m\e[33m| READ: ");
  if (demande.arg == ECRIRE) fprintf(stdout, "\e[0m\e[33m| WRITE: ");
  if (demande.arg == SUPPRIMER) fprintf(stdout, "\e[0m\e[33m| DELETE: ");
  if (demande.arg == SYNC_INIT) fprintf(stdout, "\e[0m\e[36m# Synchronisation");
  if (demande.arg == SYNC_PROC) fprintf(stdout, "\e[0m\e[33m| Sync: ");
  if (demande.arg == SYNC_FIN) fprintf(stdout, "\e[0m\e[32m| End of synchronisation\e[39m\n");
  if (demande.utilisateur[0] != '\0') fprintf(stdout, "\e[36m%s\e[33m", demande.utilisateur);
  if (demande.valeur[0] != '\0') fprintf(stdout, " - \e[36m%s", demande.valeur);
  fprintf(stdout, "\e[39m\n");
}

void sd_output_sync () {
  fprintf(stdout, "\e[0m\e[36m# Synchronisation\e[39m\n");
}
