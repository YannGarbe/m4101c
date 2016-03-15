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

char* concatenation(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}


void traitement_signal ( int sig )
{
	int statut;
	printf ( "Signal %d reçu \n" , sig );
	if (sig == SIGCHLD) {
		while (waitpid(-1, &statut, WNOHANG)>0);
	}
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

char * req(char * buf, FILE * file, int taille) {

	int i;
	for(i = 0; i<taille; i++) {
		buf[i] = '\0';
	}

	fgets(buf, taille, file); 
	fflush(stdout);

	if(buf[0] == '\0')
	{
		perror("fgets");
		exit(1);
	}
	return buf;
}

int verif(const char * message){
	
	int nb_mots=0;
	unsigned int i = 0;
	char * delim;
	char * buf;

	buf= strdup(message);
	delim = strtok(buf," ");

	if(strncmp(delim, "GET", 4) != 0)
		return -1;

	while(i<strlen(message)){
		if(message[i]== ' ')
			nb_mots++;
		i++;
    }
		if(nb_mots!=2)
			return -1;

		delim = strtok(NULL," ");
		if(strcmp("/",delim)!=0)
			return 404;

		delim = strtok(NULL," ");
	if((strcmp(delim, "HTTP/1.0\n") != 0) && (strcmp(delim, "HTTP/1.1\n") != 0))	
		return -1;

	return 0;

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
	saddr.sin_port = htons (port); /* Port d ’ écoute */
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
	
	
	int socket_client;
	

	/* On peut maintenant dialoguer avec le client */
	const char *message_bienvenue = " Bonjour , bienvenue sur mon serveur. Ce serveur est un projet d'un étudiant de Lille 1 dans le module 'Prog Sys'. \n Mon nom est Yann Garbé et je suis le créateur de ce serveur. Bon pour l'instant, il ne sert pas à grand chose, je vous l'accorde mais j'espère qu'il grandira.\n Avant tout, merci d'utiliser ce serveur ! \n Aussi, ce projet est disponible sur GitHub ici : 'https://github.com/YannGarbe'. Vous pouvez consulter  la page si vous la voulez mais il n'y a pas grand chose.\n Petit poème : \nA travers les soupirs, les plaintes et le râle\nPoursuivons jusqu’au bout la funèbre spirale\nDe ses détours maudits.\nNotre guide n’est pas Virgile le poëte,\nLa Béatrix vers nous ne penche pas la tête\nDu fond du paradis.\n\nPour guide nous avons une vierge au teint pâle\nQui jamais ne reçut le baiser d’or du hâle\nDes lèvres du soleil.\nSa joue est sans couleur et sa bouche bleuâtre,\nLe bouton de sa gorge est blanc comme l’albâtre,\nAu lieu d’être vermeil.\n\nUn souffle fait plier sa taille délicate ;\nSes bras, plus transparents que le jaspe ou l’agate,\nPendent languissamment ;\nSa main laisse échapper une fleur qui se fane,\nEt, ployée à son dos, son aile diaphane\nReste sans mouvement.\n\nPlus sombres que la nuit, plus fixes que la pierre,\nSous leur sourcil d’ébène et leur longue paupière\nLuisent ses deux grands yeux,\nComme l’eau du Léthé qui va muette et noire,\nSes cheveux débordés baignent sa chair d’ivoire\nA flots silencieux.\n\nDes feuilles de ciguë avec des violettes\nSe mêlent sur son front aux blanches bandelettes,\nChaste et simple ornement ;\nQuant au reste, elle est nue, et l’on rit et l’on tremble\nEn la voyant venir ; car elle a tout ensemble\nL’air sinistre et charmant.\n\nQuoiqu’elle ait mis le pied dans tous les lits du monde,\nSous sa blanche couronne elle reste inféconde\nDepuis l’éternité.\nL’ardent baiser s’éteint sur sa lèvre fatale,\nEt personne n’a pu cueillir la rose pâle\nDe sa virginité.\n\nThéophile Gautier, La comédie de la mort\n\n" ;

	char buffer [512];
	sleep(1);
	int pid;
	FILE * file;
	int erreur = 1;
	int errorNotFound = 0;
	char * msgError="\nHTTP/1.1 400 Bad Request\n\rConnection: close\n\rContent-Length: 17 \n\n\r400 Bad request\n\r\n";
	
	char * msgSuccess="\nHTTP/1.1 200 OK\n\rContent-Length: \n\n";

	char * msgNotFound="\nHTTP/1.1 404 Not Found\n\rConnection: close\n\rContent-Length: 17 \n\n\r404 Not Found\n\r";
	initialiser_signaux();
	while ((socket_client = accept(socket_serveur, NULL, NULL)) != -1) 
	{

		file = fdopen (socket_client , "w+" );
			if (file==NULL)
			{
				perror("fdopen");
			}
	
		pid = fork();
		if (pid == 0)
		{
			
			//write ( socket_client, message_bienvenue , strlen(message_bienvenue));
			/*while(fgets(buffer, 512, file) != NULL) 
			{*/
			char * msg;
			while((msg=req(buffer, file, sizeof(buffer)/sizeof(buffer[0]))))
			{	
				//fprintf(file, "<mygaServer> %s", buffer);
				//printf("%s\n", buffer);
				if(errorNotFound==1 && ((strcmp(msg,"\r\n")==0)||(strcmp(msg,"\n")==0))){
					fprintf(file, msgNotFound);
					errorNotFound=0;
				}

	
				else if(erreur==1 && ((strcmp(msg,"\r\n")==0)||(strcmp(msg,"\n")==0)))
				{
					fprintf(file, msgError);
				}
				else if(errorNotFound == 0 && erreur==0 && ((strcmp(msg,"\r\n")==0)||(strcmp(msg,"\n")==0)))
				{
							char str[15];
							sprintf(str, "%d", (int)strlen(message_bienvenue));
							char * message_end = concatenation(str,"\n\n\r200 OK\n\r");
							msgSuccess = concatenation(msgSuccess,message_end);
							fprintf(file, msgSuccess);
							msgSuccess="\nHTTP/1.1 200 OK\n\rContent-Length: ";
							printf("Connection Accomplie!\n");
							erreur=1;
							fprintf(file, message_bienvenue);
				}
				if(verif(msg)==0)
				{
					erreur=0;
				} 
				else if (verif(msg) ==404)
				{
					errorNotFound = 1;
				}
			}	
			fclose(file);
			exit (0);
		} else {
			close(socket_client);
		}
		
		}
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

