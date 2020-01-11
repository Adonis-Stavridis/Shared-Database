#include <stdio.h>
#include "types.h"

#ifndef __CUSTOM_DATA_H__
#define __CUSTOM_DATA_H__

//fichier avec fonction pour concatener deux chaines dans un serveur de donnees

//fonction qui remplace strcat
void custom_cat_data (char dest[MAX_STRING_SIZE], char *src);

#endif
