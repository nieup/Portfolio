sockaddr_in adresse;
if (bind (sock, (struct sockaddr *) &adresse, sizeof (adresse)) != 0)  {
  perror ("bind");
  exit (EXIT_FAILURE);
}
