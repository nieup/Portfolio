#include "pse.h"

void * maFonction (void * val) {
  char * chaine = (char *) val;
  printf ("chaine recue: %s\n", chaine);
  pthread_exit(NULL);
}

int main(void) {
  pthread_t leThread;

  int ret = pthread_create (&leThread, NULL, maFonction, "Bonjour a tous");
  if (ret != 0) {
    erreur_IO ("pthread_create");  
  }

  exit(EXIT_SUCCESS);
}
