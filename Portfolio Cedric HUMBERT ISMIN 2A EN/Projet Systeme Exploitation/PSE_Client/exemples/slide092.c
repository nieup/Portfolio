/* attente de la fin de tous les fils d’un processus */
pid_t pid_fils;
while ((pid_fils = wait (NULL)) != -1) continue;
if (errno != ECHILD) {
  perror ("wait");
  exit (EXIT_FAILURE);
}

