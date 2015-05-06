/* initialisation statique */
pthread_mutex_t verrouStat = PTHREAD_MUTEX_INITIALIZER;

/* initialisation dynamique */
pthread_mutex_t verrouDyn;
if (pthread_mutex_init (&verrouDyn, &attr) != 0) {
  perror ("mutex_init");
  exit (EXIT_FAILURE);
}
/* ...*/

/* ATTENTION : pthread_mutex_destroy doit être fait
   sur un mutex verrouillé !!! */
if (pthread_mutex_destroy (&verrouDyn) != 0) {
  perror ("mutex_destroy");
  exit (EXIT_FAILURE);
}

/* NE PAS FAIRE pthread_mutex_destroy sur verrouStat !!! *
