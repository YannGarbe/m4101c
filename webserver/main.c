#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h> 
#include <unistd.h>

int socket(int domain, int type, int protocol);

int main ( int argc , char ** argv )
{
	if ( argc > 1 && strcmp ( argv [1] ,"-test")== 0) {
		printf ("Test accompli! \n");
	}
	printf ("OK\n");

	int socket_serveur;
	/*Création de la socket*/
	socket_serveur = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_serveur != -1)
	{
		printf("%d\n", socket_serveur);
		perror("socket_serveur");
		/* traitement de l'erreur*/
	}
	close(socket_serveur);
	/*Fermeture de la socket serveur*/

		return 0;
}


