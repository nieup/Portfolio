/* ATTENTION : pthread_mutex_destroy doit être fait
    sur un mutex déverrouillé !!! */
if ( pthread_mutex_destroy (&verrouDyn) != 0) {
  perror ("mutex_destroy");
  exit (EXIT_FAILURE);
}

/* NE PAS FAIRE pthread_mutex_destroy sur verrouStat !!! */
