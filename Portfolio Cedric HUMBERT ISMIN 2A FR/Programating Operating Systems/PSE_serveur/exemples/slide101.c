pthread_t  leThread;
/* ... */
if (pthread_equal (leThread, pthread_self ()) != 0) {
  printf ("ils sont identiques\n");
}
