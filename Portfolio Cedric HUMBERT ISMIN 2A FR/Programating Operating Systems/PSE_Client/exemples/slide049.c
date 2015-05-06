int val [20];
size_t cpt = 20 * sizeof (int);
ssize_t nb = write (cre, val, cpt); /* cre: cf. slide042.C */
if (nb == -1) {
  perror ("write");
  exit (EXIT_FAILURE);
}
else if (nb < cpt) {
  printf ("autre ecriture de %d octets a faire", cpt – nb);
}
 else {
  printf ("ecriture de 20 entiers\n");
}
