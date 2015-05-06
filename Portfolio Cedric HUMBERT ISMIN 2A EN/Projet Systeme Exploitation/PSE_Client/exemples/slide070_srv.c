#include "pse.h"

#define    CMD      "serveur"

int main(int argc, char *argv[]) {
  int ecoute, canal, ret;
  char buf[LIGNE_MAX];
  struct sockaddr_in adrEcoute, reception;
  unsigned int receptionlen;
  short port;
  
  if (argc != 2) {
    erreur("usage: %s port\n", argv[0]);
  }

  port = (short) atoi(argv[1]);

  printf("%s: creating a socket\n", CMD);
  ecoute = socket (AF_INET, SOCK_STREAM, 0);
  if (ecoute < 0) {
    erreur_IO("socket");
  }
  
  adrEcoute.sin_family = AF_INET;
  adrEcoute.sin_addr.s_addr = INADDR_ANY;
  adrEcoute.sin_port = htons(port);
  printf("%s: binding to INADDR_ANY address on port %d\n", CMD, port);
  ret = bind (ecoute,  (struct sockaddr *) &adrEcoute, sizeof(adrEcoute));
  if (ret < 0) {
    erreur_IO("bind");
  }
  
  printf("%s: listening to socket\n", CMD);
  ret = listen (ecoute, 5);
  if (ret < 0) {
    erreur_IO("listen");
  }
  
  receptionlen = sizeof(reception);
  printf("%s: accepting a connection\n", CMD);
  canal = accept(ecoute, (struct sockaddr *) &reception, &receptionlen);
  if (canal < 0) {
    erreur_IO("accept");
  }
  printf("%s: adr %s, port %hu\n", CMD,
	 stringIP(ntohl(reception.sin_addr.s_addr)),
	 ntohs(reception.sin_port));
  
  ret = lireLigne(canal, buf);
  if (ret <=0 || ret == LIGNE_MAX) {
    erreur_IO("lireLigne");
  }
  
  printf("%s: reception %d octets : \"%s\"\n", CMD, ret, buf);

  if (close(canal) == -1) {
    erreur_IO("close canal");
  }

  if (close(ecoute) == -1) {
    erreur_IO("close ecoute");
  }

  exit(EXIT_SUCCESS);
}
