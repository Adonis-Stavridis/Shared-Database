#include "custom_acces.h"

void custom_cat_acces (char dest[MAX_STRING_SIZE], char *src) {
  char tmp[MAX_STRING_SIZE];

  snprintf(tmp, MAX_STRING_SIZE, "%s%s", dest, src);
  snprintf(dest, MAX_STRING_SIZE, "%s", tmp);
}
