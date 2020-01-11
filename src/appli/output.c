#include "output.h"
#include "input.h"

void output_debut () {
  fprintf(stdout, "\e[1m\e[36m");
  fprintf(stdout, "========== Start of application ==========");
  fprintf(stdout, "\e[0m\e[39m\n\n");
}

void output_fin () {
  fprintf(stdout, "\n\e[1m\e[36m");
  fprintf(stdout, "========== End of application ============");
  fprintf(stdout, "\e[0m\e[39m\n");
}

void output_en_ligne () {
  fprintf(stdout, "\e[1m\e[93m");
  fprintf(stdout, "@ Server status: ");
  fprintf(stdout, "\e[0m\e[39m");
  fprintf(stdout, "\e[1m\e[32m\e[5m");
  fprintf(stdout, "Online");
  fprintf(stdout, "\e[0m\e[39m\e[25m\n\n");
}

void output_hors_ligne () {
  fprintf(stdout, "\e[1m\e[93m");
  fprintf(stdout, "@ Server status: ");
  fprintf(stdout, "\e[0m\e[39m");
  fprintf(stdout, "\e[1m\e[31m\e[5m");
  fprintf(stdout, "Offline");
  fprintf(stdout, "\e[0m\e[39m\e[25m\n");
  fprintf(stdout, "\e[1m\e[31m");
  fprintf(stdout, "-----> Closing application");
  fprintf(stdout, "\e[0m\e[39m\n");
  sleep(SLEEP);
}

void output_surcharge () {
  fprintf(stdout, "\n\e[1m\e[93m");
  fprintf(stdout, "@ Server status: ");
  fprintf(stdout, "\e[0m\e[39m");
  fprintf(stdout, "\e[1m\e[31m\e[5m");
  fprintf(stdout, "Overload");
  fprintf(stdout, "\e[0m\e[39m\e[25m\n");
  fprintf(stdout, "\e[1m\e[31m");
  fprintf(stdout, "-----> Please try again later!");
  fprintf(stdout, "\e[0m\e[39m\n\n");
}

void output_erreur () {
  fprintf(stdout, "\e[1m\e[31m");
  fprintf(stdout, "-----> A backend error has occured!");
  fprintf(stdout, "\e[0m\e[39m\n\n");
}

void output_deconexion () {
  fprintf(stdout, "\n\e[1m\e[31m");
  fprintf(stdout, "/!\\ The server has disconnected /!\\");
  fprintf(stdout, "\e[0m\e[39m\n");
  output_hors_ligne();
}

void output_menu () {
  fprintf(stdout, "\e[1m\e[95m");
  fprintf(stdout, "# Menu");
  fprintf(stdout, "\e[0m\e[95m\n");
  fprintf(stdout, "| 1. Connect to the database\n");
  fprintf(stdout, "| 2. Quit\n");
  fprintf(stdout, "|\n");
}

void output_connexion (util_t *coord) {
  fprintf(stdout, "\e[0m\e[33m");
  fprintf(stdout, "| User: ");
  fprintf(stdout, "\e[0m\e[39m");
  if (input_connexion(coord->utilisateur) != 0) {
    output_connexion(coord);
    return;
  }

  fprintf(stdout, "\e[0m\e[33m");
  fprintf(stdout, "| Password: ");
  fprintf(stdout, "\e[0m\e[8m");
  if (input_connexion(coord->mot_de_passe) != 0) {
    output_connexion(coord);
    return;
  }

  fprintf(stdout, "\e[0m\e[28m\e[33m");
  fprintf(stdout, "|");
  fprintf(stdout, "\e[0m\e[39m\n");
}

void output_auth_err () {
  fprintf(stdout, "\e[31m| Unknown user or password!\e[39m\n\n");
}

void output_auth_suc () {
  fprintf(stdout, "\e[32m| Logged in successfully!\e[39m\n");
}

void output_desauth () {
  fprintf(stdout, "\e[32m| Logged out successfully!\e[39m\n\n");
}

void output_instr () {
  fprintf(stdout, "\n\e[1m\e[36m");
  fprintf(stdout, "# Instructions");
  fprintf(stdout, "\e[0m\e[39m\n");
}

void output_instr_err () {
  fprintf(stdout, "\e[31m| Format of the instructions:\n");
  fprintf(stdout, "| read <field1> [<field2> ...]\n");
  fprintf(stdout, "| ecrire <field1:value1> [<field2:value2> ...]\n");
  fprintf(stdout, "| delete\n");
  fprintf(stdout, "| quit\e[39m\n");
}

void output_instr_champs () {
  fprintf(stdout, "\e[31m| Field entered twice: enter each field once!\e[39m\n");
}

void output_instr_overflow () {
  fprintf(stdout, "\e[31m| Too many fields: processing only first %d fields!\e[39m\n", S_DATA_NUMBER);
}
