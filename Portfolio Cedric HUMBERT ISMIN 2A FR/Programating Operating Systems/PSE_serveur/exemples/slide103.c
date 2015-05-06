/* detachement du thread */
if (pthread_detach (pthread_self ()) != 0) {
  perror ("detach");
  exit (EXIT_FAILURE);
}

