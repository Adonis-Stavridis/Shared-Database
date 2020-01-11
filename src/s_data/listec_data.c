#include "listec_data.h"

listec_data_t listec_data_nouv () {
  return NULL;
}

listec_data_t listec_data_adjt (listec_data_t l) {
  listec_data_t nl;

  if ((nl = (listec_data_t)malloc(sizeof(noeud_data_t))) == NULL){
    fprintf(stderr, "Error: malloc\n");
    return NULL;
  }
  nl->suiv = l;

  return nl;
}

listec_data_t listec_data_supt (listec_data_t l) {
  if (l == NULL){
    fprintf(stderr, "Error: listec_data_supt\n");
    return NULL;
  }

  listec_data_t nl = l->suiv;
  free(l);

  return nl;
}

listec_data_t listec_data_supn (listec_data_t l, char utilisateur[NRML_STRING_SIZE]) {
  listec_data_t prec, tmp, nl;
  unsigned int bln;

  if (l == NULL){
    fprintf(stderr, "Error: listec_data_supt\n");
    return NULL;
  }

  prec = NULL;
  nl = l;
  tmp = l;
  bln = 0;

  while((tmp != NULL) && (!bln)) {
    if (strcmp(tmp->utilisateur, utilisateur) == 0) {
      bln = 1;
      if (prec != NULL) {
        prec->suiv = listec_data_supt(tmp);
      }
      else nl = listec_data_supt(tmp);
    }
    else {
      prec = tmp;
      tmp = tmp->suiv;
    }
  }

  return nl;
}

listec_data_t listec_data_rech (listec_data_t l, char *string) {
  if (l == NULL) return NULL;
  if (strcmp(l->utilisateur, string) == 0) {
    return l;
  }
  return listec_data_rech(l->suiv, string);
}

void listec_data_affiche (listec_data_t l) {
  fprintf(stdout, "\e[0m\e[33m> List:");
  if (l == NULL) {
    fprintf(stdout, "\e[0m\e[31m Empty");
  }
  while (l != NULL){
    fprintf(stdout, "\e[36m %s\e[33m:\e[36m%s\e[33m", l->utilisateur,l->valeur);
    l = l->suiv;
  }
  fprintf(stdout, "\e[39m\n");
}

void listec_data_free (listec_data_t l) {
  if (l != NULL) listec_data_free(listec_data_supt(l));
}
