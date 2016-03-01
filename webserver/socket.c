#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "socket.h"
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <string.h> 
#include <signal.h>


void traitement_signal ( int sig )
{
	printf ( "Signal %d reçu \n" , sig );
}

void initialiser_signaux(void)
{
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
	{
		perror("signal");
	}
	struct sigaction sa ;
	sa.sa_handler = traitement_signal ;
	sigemptyset (&sa.sa_mask );
	sa.sa_flags = SA_RESTART;
	if (sigaction (SIGCHLD, &sa, NULL)==-1)
	{
		perror ( " sigaction ( SIGCHLD ) " );
	}

}


int creer_serveur(int port) {
	
	
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

	/*Ajout de la modif socket*/
	int optval = 1;
	if (setsockopt(socket_serveur, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)) == -1)
		perror("Can not set SO_REUSEADDR");


	if (bind(socket_serveur , (struct sockaddr*)&saddr, sizeof(saddr)) == -1)
	{
		perror ( " bind socker_serveur " );
		/* traitement de l ’ erreur */
	}

	if ( listen ( socket_serveur , 10) == -1)
	{
		perror ("listen socket_serveur");
		/* traitement d ’ erreur */
	}
	
	
	int socket_client = 1 ;
	
	/*socket_client = accept ( socket_serveur , NULL , NULL );
	
	if ( socket_client == -1)
	{
		perror ( " accept " );
		
	}*/


	/* On peut maintenant dialoguer avec le client */
	const char *message_bienvenue = " Bonjour , bienvenue sur mon serveur. Ce serveur est un projet d'un étudiant de Lille 1 dans le module 'Prog Sys'. \n Mon nom est Yann Garbé et je suis le créateur de ce serveur. Bon pour l'instant, il ne sert pas à grand chose, je vous l'accorde mais j'espère qu'il grandira.\n Avant tout, merci d'utiliser ce serveur ! \n Aussi, ce projet est disponible sur GitHub ici : 'https://github.com/YannGarbe'. Vous pouvez consulter  la page si vous la voulez mais il n'y a pas grand chose.\n Petit poème : \nA travers les soupirs, les plaintes et le râle\nPoursuivons jusqu’au bout la funèbre spirale\nDe ses détours maudits.\nNotre guide n’est pas Virgile le poëte,\nLa Béatrix vers nous ne penche pas la tête\nDu fond du paradis.\n\nPour guide nous avons une vierge au teint pâle\nQui jamais ne reçut le baiser d’or du hâle\nDes lèvres du soleil.\nSa joue est sans couleur et sa bouche bleuâtre,\nLe bouton de sa gorge est blanc comme l’albâtre,\nAu lieu d’être vermeil.\n\nUn souffle fait plier sa taille délicate ;\nSes bras, plus transparents que le jaspe ou l’agate,\nPendent languissamment ;\nSa main laisse échapper une fleur qui se fane,\nEt, ployée à son dos, son aile diaphane\nReste sans mouvement.\n\nPlus sombres que la nuit, plus fixes que la pierre,\nSous leur sourcil d’ébène et leur longue paupière\nLuisent ses deux grands yeux,\nComme l’eau du Léthé qui va muette et noire,\nSes cheveux débordés baignent sa chair d’ivoire\nA flots silencieux.\n\nDes feuilles de ciguë avec des violettes\nSe mêlent sur son front aux blanches bandelettes,\nChaste et simple ornement ;\nQuant au reste, elle est nue, et l’on rit et l’on tremble\nEn la voyant venir ; car elle a tout ensemble\nL’air sinistre et charmant.\n\nQuoiqu’elle ait mis le pied dans tous les lits du monde,\nSous sa blanche couronne elle reste inféconde\nDepuis l’éternité.\nL’ardent baiser s’éteint sur sa lèvre fatale,\nEt personne n’a pu cueillir la rose pâle\nDe sa virginité.\n\nThéophile Gautier, La comédie de la mort\n\n" ;

	unsigned char buffer [1];
	sleep(1);
	int i;

	initialiser_signaux();
	//write ( socket_client, message_bienvenue , strlen(message_bienvenue ));
	while (socket_client != 0) {
		socket_client = accept ( socket_serveur , NULL , NULL );
	
		if ( socket_client == -1)
		{
			perror ( " accept " );
		}
		
		if (fork() == 0)
		{
			
			close(socket_serveur);
			write ( socket_client, message_bienvenue , strlen(message_bienvenue ));
			while (1) {
				if ((i = read( socket_client , buffer , sizeof(buffer)))== -1  ) {
					perror("read");
				}
				write ( socket_client, buffer , sizeof(buffer));
			}
			close(socket_client);
			exit(0);
		}
	}
	close(socket_serveur);
	return port;

} 




/*Cette fonction sert juste à afficher les details de la socket*/
void detailleSocket(int domain, int type, int protocol)
{
	printf("domain : %d\n", domain);

	printf("type : %d\n", type);
	
	printf("protocol : %d\n", protocol);
}

