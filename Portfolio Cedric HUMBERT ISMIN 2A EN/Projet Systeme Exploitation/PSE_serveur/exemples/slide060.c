int sock = socket (AF_INET, SOCK_STREAM, 0) ;
if (sock == -1) {
  perror ("socket");
  exit (EXIT_FAILURE);
}
/* ... */
close (sock);

