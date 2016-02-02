#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h> 
#include <unistd.h>

int creerSocket(int domain, int type, int protocol);


int main ( int argc , char ** argv )
{
	if ( argc > 1 && strcmp ( argv [1] ,"-test")== 0) {
		printf ("Test accompli! \n");
	}
	printf ("OK\n");

	/*Création de la socket*/
	int testSocket = creerSocket(AF_INET, SOCK_STREAM, 0);
	close(testSocket);
	/*Fermeture de la socket serveur*/

		return 0;
}


