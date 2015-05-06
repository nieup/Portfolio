static int codeRetour;  /* variable locale statique */
                        /* ATTENTION a la concurrence */
codeRetour = 0;
pthread_exit (&codeRetour);
