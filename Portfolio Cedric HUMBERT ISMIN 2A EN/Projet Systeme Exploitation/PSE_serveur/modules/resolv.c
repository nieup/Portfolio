/* module resolv: resolv.c */

#include "pse.h"

/*
  variable globale a visibilite restreinte a ce fichier.
*/
static struct addrinfo *static_infos = NULL;

struct sockaddr_in *resolv (const char *host, const char *service) {
  /* A MODIFIER / COMPLETER */
  return NULL;
}

char *stringIP (unsigned int entierIP) {
  struct in_addr ia;
  ia.s_addr = htonl (entierIP); 
  return inet_ntoa(ia);
}

void freeResolv (void) {
  if (static_infos != NULL) {
    freeaddrinfo (static_infos);
  }
}

