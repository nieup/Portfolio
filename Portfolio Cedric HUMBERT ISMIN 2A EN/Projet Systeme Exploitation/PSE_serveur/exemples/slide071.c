char texte[20];
int lus = recv (sock, texte, 20, MSG_DONTWAIT);
if ( lus == -1 ) {
  if (errno == EGAIN) {
    printf ( "pas de donnees a recevoir\n" );
    /* ... */
  } 
  else {
    perror ("accept");
    exit (EXIT_FAILURE);
  }
}
else {
  int ecrit = send (sock, texte, 20, 0 );
  /* ... */
}

