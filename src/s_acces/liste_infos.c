#include "liste_infos.h"

void set_index (liste_infos_t *liste_infos) {
  for (unsigned int i=0; i<MAX_TAB_SIZE; i++) {
    if (liste_infos->bool[i] == 0) {
      liste_infos->index = i;
      return;
    }
  }
  liste_infos->index = MAX_TAB_SIZE;
}

void liste_init (liste_infos_t *liste_infos) {
  memset((char *)liste_infos->tab, 0, MAX_TAB_SIZE*sizeof(infos_t));
  memset((char *)liste_infos->bool, 0, MAX_TAB_SIZE*sizeof(unsigned int));
  liste_infos->index = 0;
}

void liste_ajout (liste_infos_t *liste_infos, infos_t *infos) {
  unsigned int tmp = liste_infos->index;

  if (tmp != MAX_TAB_SIZE) {
    memset((char *)&liste_infos->tab[tmp], 0, sizeof(infos_t));
    liste_infos->tab[tmp].type = infos->type;
    infos->id = tmp;
    liste_infos->tab[tmp].id = tmp;
    liste_infos->tab[tmp].port = infos->port;
    if (infos->type == CLIENT) {
      infos->statut = AUTHENTIFIE;
      liste_infos->tab[tmp].statut = AUTHENTIFIE;
      liste_infos->tab[tmp].coord = infos->coord;
    }
    if (infos->type == DATA) {
      infos->statut = CONNECTE;
      liste_infos->tab[tmp].statut = CONNECTE;
      strcpy(liste_infos->tab[tmp].data, infos->data);
    }
    liste_infos->bool[tmp] = 1;
    set_index (liste_infos);
  }
  else {
    infos->statut = SURCHARGE;
  }
}

void liste_sup (liste_infos_t *liste_infos, infos_t *infos) {
  memset((char *)&liste_infos->tab[infos->id], 0, sizeof(infos_t));
  liste_infos->bool[infos->id] = 0;
  if (infos->type == CLIENT) infos->statut = DESAUTHENTIFIE;
  if (infos->type == DATA) infos->statut = DECONNECTE;
  memset((char *)&infos->coord, 0, sizeof(util_t));
  set_index(liste_infos);
}

void liste_affiche_clients (liste_infos_t *liste_infos) {
  unsigned int num = 0;

  fprintf(stdout, "\e[0m\e[33m");
  fprintf(stdout, "> Connected clients:");
  fprintf(stdout, "\e[0m\e[39m");

  for (unsigned int i = 0; i < MAX_TAB_SIZE; i++) {
    if (liste_infos->bool[i] == 1) {
      fprintf(stdout, "\e[0m\e[36m %s(%hu)\e[0m\e[39m", liste_infos->tab[i].coord.utilisateur, liste_infos->tab[i].port);
      num++;
    }
  }

  if (num == 0) fprintf(stdout, "\e[0m\e[31m None\e[0m\e[39m");
  fprintf(stdout, "\e[0m\e[33m");
  fprintf(stdout, " (\e[0m\e[36m%d\e[0m\e[33m)", num);
  fprintf(stdout, "\e[0m\e[39m\n");
}

void liste_affiche_data (liste_infos_t *liste_infos) {
  unsigned int num = 0;

  fprintf(stdout, "\e[0m\e[33m");
  fprintf(stdout, "> Connected datas:");
  fprintf(stdout, "\e[0m\e[39m");

  for (unsigned int i = 0; i < MAX_TAB_SIZE; i++) {
    if (liste_infos->bool[i]) {
      fprintf(stdout, "\e[0m\e[36m %s(%hu)\e[0m\e[39m", liste_infos->tab[i].data, liste_infos->tab[i].port);
      num++;
    }
  }

  if (num == 0) fprintf(stdout, "\e[0m\e[31m None\e[0m\e[39m");
  fprintf(stdout, "\e[0m\e[33m");
  fprintf(stdout, " (\e[0m\e[36m%d\e[0m\e[33m)", num);
  fprintf(stdout, "\e[0m\e[39m\n");
}

unsigned int liste_rech_data (liste_infos_t *liste_infos, char data[NRML_STRING_SIZE]) {
  for (unsigned int i = 0; i < MAX_TAB_SIZE; i++) {
    if (liste_infos->bool[i]) {
      if (strcmp(liste_infos->tab[i].data, data) == 0) return 0;
    }
  }
  return 1;
}

void get_champs (liste_infos_t *liste_infos, char string[MAX_STRING_SIZE]) {
  char *tmp[MAX_TAB_SIZE];
  unsigned int bln, index;

  index = 0;
  memset((char *)&tmp, 0, MAX_TAB_SIZE*sizeof(char *));

  custom_cat_acces(string, "Accessible fields:\e[33m");

  for (unsigned int i = 0; i < MAX_TAB_SIZE; i++) {
    if (liste_infos->bool[i]) {
      bln = 0;
      for (unsigned int j = 0; ((j < index) && (!bln)); j++) {
        if (strcmp(liste_infos->tab[i].data, tmp[j]) == 0) bln = 1;
      }
      if (!bln) {
        tmp[index++] = liste_infos->tab[i].data;
        custom_cat_acces(string, " ");
        custom_cat_acces(string, liste_infos->tab[i].data);
      }
    }
  }

  if (index == 0) custom_cat_acces(string, "\e[0m\e[31m None\e[0m\e[39m");
}

unsigned int set_champs (liste_infos_t *liste_infos, char champs[MAX_TAB_SIZE][NRML_STRING_SIZE]) {
  unsigned int bln, index;

  index = 0;

  for (unsigned int i = 0; i < MAX_TAB_SIZE; i++) {
    if (liste_infos->bool[i]) {
      bln = 0;
      for (unsigned int j = 0; ((j < index) && (!bln)); j++) {
        if (strcmp(liste_infos->tab[i].data, champs[j]) == 0) bln = 1;
      }
      if (!bln) {
        strcpy(champs[index++], liste_infos->tab[i].data);
      }
    }
  }

  return index;
}

unsigned int get_data_ports (liste_infos_t *liste_infos, unsigned short ports[MAX_TAB_SIZE], char data[NRML_STRING_SIZE]) {
  unsigned int index = 0;

  for (unsigned int i = 0; i < MAX_TAB_SIZE; i++) {
    if (liste_infos->bool[i]) {
      if (strcmp(liste_infos->tab[i].data, data) == 0) {
        ports[index++] = liste_infos->tab[i].port;
      }
    }
  }

  return index;
}

unsigned int get_data_ports_diff (liste_infos_t *liste_infos, unsigned short ports[MAX_TAB_SIZE], char data[NRML_STRING_SIZE], unsigned int id) {
  unsigned int index = 0;

  for (unsigned int i = 0; i < MAX_TAB_SIZE; i++) {
    if (liste_infos->bool[i] && (i != id)) {
      if (strcmp(liste_infos->tab[i].data, data) == 0) {
        ports[index++] = liste_infos->tab[i].port;
      }
    }
  }

  return index;
}

unsigned int set_utilisateur(liste_infos_t *liste_infos, unsigned int id, char string[NRML_STRING_SIZE]) {
  if ((&liste_infos->tab[id] == NULL) || (liste_infos->tab[id].coord.utilisateur[0] == '\0') || (liste_infos->bool[id] == 0)) return 1;

  strcpy(string, liste_infos->tab[id].coord.utilisateur);

  return 0;
}
