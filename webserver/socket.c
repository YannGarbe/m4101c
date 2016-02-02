#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "socket.h"
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <string.h> 
//int socket(int domain, int type, int protocol);
//int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);



int creer_serveur(int port) {
	//printf("Pas encore implémenté! \n");
	
	int socket_serveur ;
	socket_serveur = socket ( AF_INET , SOCK_STREAM , 0);
	if ( socket_serveur == -1)
	{
		perror ( " socket_serveur " );
		/* traitement de l ’ erreur */
	}
	/* Utilisation de la socket serveur */
	
	struct sockaddr_in saddr;
	saddr.sin_family = AF_INET; /* Socket ipv4 */
	saddr.sin_port = htons (8080); /* Port d ’ écoute */
	saddr.sin_addr.s_addr = INADDR_ANY; /* écoute sur toutes les interfaces */
	if (bind(socket_serveur , (struct sockaddr*)&saddr, sizeof(saddr)) == -1)
	{
		perror ( " bind socker_serveur " );
		/* traitement de l ’ erreur */
	}

	if ( listen ( socket_serveur , 10) == -1)
	{
		perror ( " listen socket_serveur " );
		/* traitement d ’ erreur */
	}

	int socket_client ;
	socket_client = accept ( socket_serveur , NULL , NULL );
	
	if ( socket_client == -1)
	{
		perror ( " accept " );
		/* traitement d ’ erreur */
	}
	/* On peut maintenant dialoguer avec le client */
	const char *message_bienvenue = " Bonjour , bienvenue sur mon serveur. Ce serveur est un projet d'un étudiant de Lille 1 dans le module 'Prog Sys'. \n Mon nom est Yann Garbé et je suis le créateur de ce serveur. Bon pour l'instant, il ne sert pas à grand chose, je vous l'accorde mais j'espère qu'il grandira.\n \n" ;
	sleep(1);
	
	char *recup = "Test non concluant\n";
	write ( socket_client, message_bienvenue , strlen(message_bienvenue ));
	read( socket_client , recup , sizeof(recup));
	//write ( socket_serveur , message_bienvenue ,strlen(message_bienvenue ));
	printf("%s\n", recup);
	
	//close(socket_serveur);
	return port;
} 


/*Cette fonction sert juste à afficher les details de la socket*/
void detailleSocket(int domain, int type, int protocol)
{
	printf("domain : %d\n", domain);

	printf("type : %d\n", type);
	
	printf("protocol : %d\n", protocol);
}

