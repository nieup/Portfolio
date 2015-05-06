extern char **environ;
int main (int argc, char *argv[]) {
  int retour = execve ("/bin/ls", argv, environ);
  /* ici, obligatoirement une erreur (retour vaut -1) */
  erreur_IO ("execve");
}
