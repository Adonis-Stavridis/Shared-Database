#include "appli.h"

int main (int argc, char *argv[]) {
  struct sockaddr_in client, serveur1, serveur2;
  int socketfd;
  infos_t infos;
  size_t length = sizeof(struct sockaddr_in);
  unsigned int quit = 0, tmp = 0;

  if (argc != 2) {
    fprintf(stderr, "%s <PORT>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if ((atoi(argv[1]) < 2048) && (atoi(argv[1]) > 65535)) {
    fprintf(stderr, "2048 <= PORT <= 65535\n");
    exit(EXIT_FAILURE);
  }

  if ((socketfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP)) == -1) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  memset((char *)&client, 0, length);
  client.sin_family = AF_INET;
  client.sin_port = htons(atoi(argv[1]));
  client.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(socketfd, (struct sockaddr *)&client, (socklen_t) length) == -1) {
    perror("bind");
    if (close(socketfd) == -1) {
      perror("close");
      exit(EXIT_FAILURE);
    }
    exit(EXIT_FAILURE);
  }

  memset((char *)&serveur1, 0, length);
  serveur1.sin_family = AF_INET;
  serveur1.sin_port = htons(PORT_1);
  serveur1.sin_addr.s_addr = htonl(INADDR_ANY);
  if (inet_aton(LOC_ADR, &serveur1.sin_addr) == 0) {
    fprintf(stderr, "inet_aton\n");
    if (close(socketfd) == -1) {
      perror("close");
      exit(EXIT_FAILURE);
    }
    exit(EXIT_FAILURE);
  }

  memset((char *)&serveur2, 0, length);
  serveur2.sin_family = AF_INET;
  serveur2.sin_port = htons(PORT_2);
  if (inet_aton(LOC_ADR, &serveur2.sin_addr) == 0) {
    fprintf(stderr, "inet_aton\n");
    if (close(socketfd) == -1) {
      perror("close");
      exit(EXIT_FAILURE);
    }
    exit(EXIT_FAILURE);
  }

  memset((char *)&infos, 0, sizeof(infos_t));
  infos.type = CLIENT;
  infos.id = MAX_TAB_SIZE;
  infos.port = client.sin_port;

  output_debut();

  if (client_init(socketfd, &serveur1, &infos) == 1) {
    if (close(socketfd) == -1) {
      perror("close");
      exit(EXIT_FAILURE);
    }
    output_fin();
    return EXIT_SUCCESS;
  }

  while (!quit) {
    output_menu();
    memset((char *)&infos.coord, 0, sizeof(util_t));
    switch (input_menu(&infos.coord)) {
      case 1:
        if ((tmp = authentification(socketfd, &serveur1, &infos)) == 0) {
          output_auth_suc();
          output_instr();
          while (tmp != 3) {
            if ((tmp = instructions(socketfd, &serveur2, infos.id)) == 2) {
              quit = 1;
              break;
            }
          }
          if (tmp != 2) {
            if ((tmp = desauthentification(socketfd, &serveur1, &infos)) == 2) quit = 1;
          }
        }
        else {
          if (tmp == 2) quit = 1;
        }
        break;
      case 2:
        quit = 1;
        break;
      default:
        break;
    }
  }

  if (tmp != 2) {
    if (client_fin(socketfd, &serveur1, &infos) == 1) {
      if (close(socketfd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
      }
      output_fin();
      return EXIT_SUCCESS;
    }
  }

  if (close(socketfd) == -1) {
    perror("close");
    exit(EXIT_FAILURE);
  }

  output_fin();

  return EXIT_SUCCESS;
}
