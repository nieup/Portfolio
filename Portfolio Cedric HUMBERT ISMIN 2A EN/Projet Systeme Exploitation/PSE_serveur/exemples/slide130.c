pthread_mutex_t verrouStat = PTHREAD_MUTEX_INITIALIZER;
    
if (pthread_mutex_lock (&verrouStat) != 0) {
  perror ("mutex_lock");
  exit (EXIT_FAILURE);
}

/* section critique … */

if (pthread_mutex_unlock (&verrouStat) != 0) {
  perror ("mutex_unlock");
  exit (EXIT_FAILURE);
}
/* ... */
if ((code = pthread_mutex_trylock (&verrouStat)) != 0) {
  if (code == EBUSY) {
    /* déjà verrouillé… reessayer plus tard ... */
   }
  else {
    perror ("mutex_unlock");
    exit (EXIT_FAILURE);
  }
}

