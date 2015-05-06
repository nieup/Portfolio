pthread_attr_t attr;
if (pthread_attr_init (&attr) != 0) {
  perror ("attr_init");
  exit (EXIT_FAILURE);
}
if (pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED) != 0) {
  perror ("pthread_attr_setdetachstate");
  exit (EXIT_FAILURE);
}
if (pthread_create (&leThread, &attr, maFonction, "Bonjour a tous") != 0) {
  perror ("pthread_create");
  exit (EXIT_FAILURE);
}
if (pthread_attr_destroy (&attr) != 0) {
  perror ("pthread_attr_destroy");
  exit (EXIT_FAILURE);
}

