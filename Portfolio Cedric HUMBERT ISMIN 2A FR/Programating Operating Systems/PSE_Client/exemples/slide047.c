int lec = open("/etc/passwd", O_RDONLY);
if (lec == -1) {
  perror ("open");
  exit (EXIT_FAILURE);
}

int cre = open("donnee.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
if (crec == -1) {
  perror ("open");
  exit (EXIT_FAILURE);
}

int fle = open("rapport.log", O_RDWR | O_CREAT | O_APPEND, 0644);
if (fle == -1) {
  perror ("open");
  exit (EXIT_FAILURE);
}

/* cf. slide 46 */
if (close (fle) == -1) { 
  perror ("close");
  exit (EXIT_FAILURE);
 }
