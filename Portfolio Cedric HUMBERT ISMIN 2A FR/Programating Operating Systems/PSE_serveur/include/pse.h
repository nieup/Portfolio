#ifndef PSE_INCLUDE_H
#define PSE_INCLUDE_H

/* pse.h: fichiers d'inclusion et quelques constantes utiles
   pour les TP et le Projet de programmation systeme. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>
#include <semaphore.h>

#include "erreur.h"
#include "ligne.h"
#include "resolv.h"
#include "datathread.h"
#include "msgbox.h"
#include "msg.h"

#include "structures.h"
#include "login_Serv.h"
#include "TOMM_Serv.h"
#include "Net_Serv.h"

#define FAUX	0
#define VRAI	1

#endif

