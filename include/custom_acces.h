#include <stdio.h>
#include "types.h"

#ifndef __CUSTOM_ACCES_H__
#define __CUSTOM_ACCES_H__

//fichier avec fonction pour concatener deux chaines dans le serveur d'acces

//fonction qui remplace strcat
void custom_cat_acces (char dest[MAX_STRING_SIZE], char *src);

#endif
