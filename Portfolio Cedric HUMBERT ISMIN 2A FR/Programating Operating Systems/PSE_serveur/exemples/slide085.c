pid_t fils = fork ();
if ( fils == -1 ) {
  perror ("fork");
  exit (EXIT_FAILURE);
}
/* le père et le fils */
if ( fils == 0 ) {
  /* uniquement le fils */
}
else {
  /* uniquement le père */
}   
/* le père et le fils */

