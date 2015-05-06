pthread_mutexattr_t attr;
if (pthread_mutexattr_init (&attr) != 0) {
  perror ( "mutexattr_init");
   exit (EXIT_FAILURE);
}
if (pthread_mutexattr_settype (&attr, PTHREAD_MUTEX_ERRORCHECK) != 0) {
  perror ("mutexattr_settype");
  exit (EXIT_FAILURE);
}
/* ... */
if (pthread_mutexattr_destroy (&attr) != 0) {
  perror ("mutexattr_destroy");
  exit (EXIT_FAILURE);
}

