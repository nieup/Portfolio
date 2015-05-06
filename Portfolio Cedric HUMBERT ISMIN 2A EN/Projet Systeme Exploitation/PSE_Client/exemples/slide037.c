#include "pse.h"

int main ( int argc, char *argv[]) {
  /* requete DNS */
  int code;
  struct addrinfo *infos, hints;
  struct sockaddr_in *adresse;

  memset ( &hints, 0, sizeof (struct addrinfo));

  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  code = getaddrinfo ( "www.emse.fr", "http", &hints, &infos );
  if ( code != 0) {
    fprintf ( stderr, "Erreur: %s\n", gai_strerror(code) );
    exit ( EXIT_FAILURE );
  }
  adresse = (struct sockaddr_in *) infos->ai_addr;

  /* adresse->sin_addr.s_addr soit contenir 0xC131AEC2
                                         ie 193.49.174.194 */
  /* adresse->sin_port doit contenir 80 */

  freeaddrinfo ( infos );
  exit(EXIT_SUCCESS);
}
