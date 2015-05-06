off_t depl = -10;
off_t pos = lseek (lec, depl, SEEK_CUR); /* lec: cf. slide042.c */
if (pos == -1) {
  perror ("lseek");
  exit (EXIT_FAILURE);
}
/* la prochaine lecture relira les dix derniers caractères du tableau text */
