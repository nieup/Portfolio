if (mkfifo ("FIFO", 0600) == -1 ) {
  perror ( "mkfifo" );
  exit (EXIT_FAILURE);
 }
fd = open ("FIFO", O_RDONLY);
