if (listen (sock, 20) != 0)  {
  perror ("listen");
  exit (EXIT_FAILURE);
}
