char text [20];
ssize_t nb = read (lec, text, 20); /* lec: cf. slide042.c */
if ( nb == -1 ) {
  perror ("read");
  exit (EXIT_FAILURE);
}
else if (nb == 0) {
  printf ("fin de fichier\n");
}
else if (nb < 20) {
   printf ("autre lecture de %d octets a faire", 20 - nb);
}
else
  printf ("lecture de 20 octets\n");
