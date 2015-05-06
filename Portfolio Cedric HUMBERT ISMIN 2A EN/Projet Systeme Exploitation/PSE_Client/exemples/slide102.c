int * codeRetour;  
pthread_t leThread;
/* ... */
if (pthread_join (leThread, (void **) &codeRetour) != 0) {
  perror ("join");
  exit (EXIT_SUCCESS);
}
printf ("code = %d\n", *codeRetour);

