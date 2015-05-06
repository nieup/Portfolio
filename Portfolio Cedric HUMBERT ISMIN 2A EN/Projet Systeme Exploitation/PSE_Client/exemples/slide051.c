/* programme (c) M Kerrisk,
   adapté par P. Lalevée */

#include "pse.h"

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
  int inputFd, outputFd, openFlags;
  mode_t filePerms;
  ssize_t numRead;
  char buf[BUF_SIZE];
  
  if (argc != 3) {
    erreur("usage: %s source dest\n", argv[0]);
  }
  
  inputFd = open(argv[1], O_RDONLY);
  if (inputFd == -1) {
    /* exemples d'erreurs possibles ?
     */
    erreur_IO("open input");
  }

  openFlags = O_CREAT | O_WRONLY | O_TRUNC;
  filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
  outputFd = open(argv[2], openFlags, filePerms);
  if (outputFd == -1) {
    /* exemples d'erreurs possibles ?
     */
    erreur_IO("open output");
  }

  while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0) {
    if (write(outputFd, buf, numRead) != numRead) {
      /* exemples d'erreurs possibles ?
       */
      erreur_IO("write");
    }
  }
  
  if (numRead == -1) {
    /* exemples d'erreurs possibles ?
     */
    erreur_IO("read");
  }

  if (close(inputFd) == -1) {
    /* exemples d'erreurs possibles ?
     */
    erreur_IO("close input");
  }

  if (close(outputFd) == -1) {
    /* exemples d'erreurs possibles ?
     */
    erreur_IO("close output");
  }

  exit(EXIT_SUCCESS);
}
