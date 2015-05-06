/* calcul.c */
#include "pse.h"

int main (void) {
  int pid, status;
  char *param [2];
  pid = fork ();
  if (pid == -1) {
    erreur_IO("fork");
  }
  else if (pid == 0) {
    printf ("avant: je suis le fils (pid=%d)\n", getpid () );
    param [0] = "carre";
    param [1] = NULL;
    execv ("slide084_carre", param);
    erreur_IO("execv");
  }
  printf ("je suis le père (pid=%d)\n", getpid () );
  wait (&status);
  printf("fin du pere (status = %d)\n", status);
  exit(EXIT_SUCCESS);
}
