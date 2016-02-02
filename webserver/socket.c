#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>


int socket(int domain, int type, int protocol);

void detailleSocket(int domain, int type, int protocol)
{
	printf("domain : %d\n", domain);

	printf("type : %d\n", type);
	
	printf("protocol : %d\n", protocol);
}

int socket(int domain, int type, int protocol)
{
	detailleSocket(domain, type, protocol);
	return domain+type+protocol;
}

int creerSocket(int domain, int type, int protocol)
{
	int socket_serveur = socket(domain, type, protocol);
	if (socket_serveur != -1)
	{
		printf("%d\n", socket_serveur);
		perror("socket_serveur");
		/* traitement de l'erreur*/
	}
	/*Utilisation de la socket*/
	return socket_serveur;
}

