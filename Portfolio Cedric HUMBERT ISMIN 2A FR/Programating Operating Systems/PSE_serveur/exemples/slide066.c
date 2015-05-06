sockaddr_in adresse;
socklen_t len;
int sockconn = accept ( sock, (struct sockaddr *) &adresse, &len );
if ( sockconn == -1 )  { perror ( "accept" ); exit ( EXIT_FAILURE ); }
/* adresse.sin_addr.s_addr : IP du client
   adresse.sin_port        : port de réponse 
   par la suite : read(sockconn, ...) permettra de lire les octets
   du client et write(sockconn, ...) permettra de lui en envoyer */
