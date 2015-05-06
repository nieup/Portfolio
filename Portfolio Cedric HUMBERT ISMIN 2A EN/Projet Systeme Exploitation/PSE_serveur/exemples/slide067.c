sockaddr_in adrServ;  /* a valoriser ... */
if (connect (sock, (struct sockaddr *) &adrServ, sizeof (adrServ)) == -1) {
  perror ("accept");
  exit (EXIT_FAILURE);
}
/* read() et write() sont maintenant possibles */
