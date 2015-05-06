/* carre.c*/
#include "pse.h"

int main(int argc, char *argv[]) {
  int x; 
  printf ("apres: je suis le fils %s (pid=%d)\n", argv[0], getpid());
  printf ("pid pere = %d\n",getppid() );
  printf ("x = ");
  scanf ("%d", &x);
  x  = x * x;
  printf ("carre = %d\n", x);
  exit(EXIT_SUCCESS);
}
