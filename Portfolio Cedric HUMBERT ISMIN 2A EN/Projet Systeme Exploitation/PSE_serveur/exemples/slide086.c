#include "pse.h"

int main (void) {
  pid_t pid;
  pid = fork ();
  assert( pid != -1);
  if (pid == 0) {
    printf ("je suis le fils %d (père %d)\n", getpid(), getppid());
  }
  else {
    printf ("je suis le père %d (fils %d)\n", getpid(), pid);
    pause();
  }
  return 0;
}
