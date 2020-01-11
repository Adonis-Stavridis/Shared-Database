#include "listec_bdd.h"

listec_bdd_t listec_bdd_nouv () {
  return NULL;
}

listec_bdd_t listec_bdd_adjt (listec_bdd_t l) {
  listec_bdd_t nl;

  if ((nl = (listec_bdd_t)malloc(sizeof(noeud_bdd_t))) == NULL){
    fprintf(stderr, "Error: malloc\n");
    return NULL;
  }
  nl->suiv = l;

  return nl;
}

listec_bdd_t listec_bdd_supt (listec_bdd_t l) {
  if (l == NULL){
    fprintf(stderr, "Error: listec_bdd_supt\n");
    return NULL;
  }

  listec_bdd_t nl = l->suiv;
  free(l);

  return nl;
}

listec_bdd_t listec_bdd_rech (listec_bdd_t l, char *string) {
  if (l == NULL) return NULL;
  if (strcmp(l->utilisateur, string) == 0) {
    return l;
  }
  return listec_bdd_rech(l->suiv, string);
}

void listec_bdd_affiche (listec_bdd_t l) {
  unsigned int i = 0;

  fprintf(stdout, "\e[0m\e[33m> Users of database: \e[36m");
  while (l != NULL){
    fprintf(stdout, " %s", l->utilisateur);
    i++;
    l = l->suiv;
  }

  fprintf(stdout, " \e[33m(\e[36m%d\e[33m)\e[39m\n", i);
}

void listec_bdd_free (listec_bdd_t l) {
  if (l != NULL) listec_bdd_free(listec_bdd_supt(l));
}
