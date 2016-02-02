#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h> 
#include <unistd.h>
#include "socket.h"

int creerSocket(int domain, int type, int protocol);


int main ( int argc , char ** argv )
{
	if ( argc > 1 && strcmp ( argv [1] ,"-test")== 0) {
		printf ("Test accompli! \n");
	}
	printf ("OK\n");

	int serveur;
	serveur = creer_serveur(8080);
	

	printf("Fin du serveur : %d \n", serveur);
	return 0;
}


