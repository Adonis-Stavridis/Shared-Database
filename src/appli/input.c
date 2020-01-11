#include "input.h"
#include "output.h"

void input_newline (char *string, unsigned int lgr) {
  if (string[lgr] == '\n') string[lgr] = '\0';
}

unsigned int input_connexion (char *string) {
  char tmp[TMP_STRING_SIZE];
  size_t len;
  int pr;

  if (fgets(tmp, TMP_STRING_SIZE, stdin) == NULL) {
    fprintf(stderr, "Error: fgets\n");
    exit(EXIT_FAILURE);
  }

  if (*tmp == '\n') {
    fprintf(stdout, "\e[28m\e[31m| Enter a value!\e[39m\n");
    return 1;
  }

  if ((len = strlen(tmp)) > NRML_STRING_SIZE) {
    fprintf(stdout, "\e[28m\e[31m| The maximum character count is %d!\e[39m\n", NRML_STRING_SIZE-1);
    return 1;
  }

  if (strstr(tmp, BDD_DELIM) != NULL) {
    fprintf(stdout, "\e[28m\e[31m| Do not write the character %s in your values!\e[39m\n", BDD_DELIM);
    return 1;
  }

  input_newline(tmp, len-1);

  memset((char *)&(*string), 0, NRML_STRING_SIZE);

  pr = snprintf(string, NRML_STRING_SIZE, "%s", tmp);
  if (pr < 0 || pr >= NRML_STRING_SIZE) {
    fprintf(stderr, "Error: snprintf\n");
    exit(EXIT_FAILURE);
  }

  return 0;
}

unsigned int input_menu (util_t *coord) {
  char tmp[TMP_STRING_SIZE];
  size_t len;
  unsigned int choix = 0;

  fprintf(stdout, "\e[0m\e[95m");
  fprintf(stdout, "| -> Your choice (1/2): ");
  fprintf(stdout, "\e[0m\e[39m");

  if (fgets(tmp, TMP_STRING_SIZE, stdin) == NULL) {
    fprintf(stderr, "Error: fgets\n");
    exit(EXIT_FAILURE);
  }

  if (*tmp != '\n' && ((len = strlen(tmp)) == 2)) {
    choix = *tmp - '0';
  }

  switch (choix) {
    case 1:
      fprintf(stdout, "\n\e[1m\e[33m");
      fprintf(stdout, "# Connection\n");
      output_connexion(coord);
      return 1;
      break;
    case 2:
      return 2;
      break;
    default:
      fprintf(stdout, "\e[31m| Enter only 1 or 2!\e[39m\n");
      return (input_menu(coord));
      break;
  }
}
