/* affichage du code de fin d’un processus fils */
pid_t pid_fils;
int status;
pid_fils = wait (&status);
if (pid_fils == -1) {
  perror ("wait");
  exit (EXIT_FAILURE);
}
if (WIFEXITED (status)) { /* terminaison normale */
  printf ("code du fils %d = %d\n", pid_fils, WEXITSTATUS (status));
}

