#include "t_bdd.h"

listec_bdd_t bdd_init () {
  FILE *fp;
  char ligne[MAX_STRING_SIZE], *tmp;
  unsigned int i;
  listec_bdd_t nouv, prec;

  if ((fp = fopen(BDD_PATH, "r")) == NULL) {
    perror("fopen");
    return NULL;
  }

  prec = listec_bdd_nouv();

  while (fgets(ligne, MAX_STRING_SIZE, fp) != NULL) {
    nouv = listec_bdd_adjt(prec);

    strcpy(nouv->utilisateur, strtok(ligne, BDD_DELIM));
    strcpy(nouv->mot_de_passe, strtok(NULL, BDD_DELIM));

    memset((char *)&nouv->champs, 0, S_DATA_NUMBER*NRML_STRING_SIZE*sizeof(char));
    i = 0;
    while ((tmp = strtok(NULL, BDD_DELIM)) != NULL) {
      if (strcmp(tmp, "\n") == 0) break;
      else {
        if (i >= S_DATA_NUMBER) {
          s_output_champ_overflow(nouv->utilisateur);
          break;
        }
        strcpy(nouv->champs[i++], tmp);
      }
    }

    prec = nouv;
  }

  if (fclose (fp) == EOF) {
    perror("fclose");
    return NULL;
  }

  return nouv;
}

unsigned int verif_coordonnees (listec_bdd_t bdd, util_t coord) {
  listec_bdd_t tmp;

  if ((tmp = listec_bdd_rech(bdd, coord.utilisateur)) != NULL) {
    if (strcmp(tmp->mot_de_passe, coord.mot_de_passe) == 0) return 0;
    else return 1;
  }

  return 1;
}

unsigned int verif_droits (listec_bdd_t bdd, char utilisateur[NRML_STRING_SIZE], char champ[NRML_STRING_SIZE]) {
  listec_bdd_t tmp;

  if ((tmp = listec_bdd_rech(bdd, utilisateur)) != NULL) {
    for (unsigned int i = 0; ((i < MAX_TAB_SIZE) && (tmp->champs[i][0] != '\0')); i++) {
      if (strcmp(tmp->champs[i], champ) == 0) return 0;
    }
  }

  return 1;
}

void bdd_fin (listec_bdd_t bdd) {
  listec_bdd_free(bdd);
}
