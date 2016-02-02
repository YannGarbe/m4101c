#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "socket.h"

//int socket(int domain, int type, int protocol);
//int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);


int creer_serveur(int port) {
	printf("Pas encore implémenté! \n");
	return port;
} 


/*Cette fonction sert juste à afficher les details de la socket*/
void detailleSocket(int domain, int type, int protocol)
{
	printf("domain : %d\n", domain);

	printf("type : %d\n", type);
	
	printf("protocol : %d\n", protocol);
}

