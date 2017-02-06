/******************************************************************************/
/*			Application: ....			              */
/******************************************************************************/
/*									      */
/*			 programme  SERVEUR 				      */
/*									      */
/******************************************************************************/
/*									      */
/*		Auteurs :  ....						      */
/*		Date :  ....						      */
/*									      */
/******************************************************************************/

#include<stdio.h>
//#include <curses.h>

#include<sys/signal.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<string.h>

#include "fon.h"     		/* Primitives de la boite a outils */

#define SERVICE_DEFAUT "1111"
#define NB_REQ_MAX 10 			/* Nombre maximum de requête dans la file d'attente du serveur*/
#define NB_OCTETS 1000      /* Taille du tampon */

void serveur_appli (char *service);   /* programme serveur */


/******************************************************************************/
/*---------------- programme serveur ------------------------------*/

int main(int argc,char *argv[])
{

	char *service= SERVICE_DEFAUT; /* numero de service par defaut */


	/* Permet de passer un nombre de parametre variable a l'executable */
	switch (argc)
 	{
   	case 1:
		  printf("defaut service = %s\n", service);
		  		  break;
 	case 2:
		  service=argv[1];
            break;

   	default :
		  printf("Usage:serveur service (nom ou port) \n");
		  exit(1);
 	}

	/* service est le service (ou numŽro de port) auquel sera affectŽ
	ce serveur*/

	serveur_appli(service);
}


/******************************************************************************/
void serveur_appli(char *service)

/* Procedure correspondant au traitemnt du serveur de votre application */

{
	int idSocket, idSocketAccept, writeServeur, readServeur;
	struct sockaddr_in *p_adr_socket, *p_adr_client;
	pid_t p;
	char tampon[NB_OCTETS];

	/*Création de la socket protocole internet et mode de connection*/
	idSocket = h_socket(AF_INET, SOCK_STREAM);

	/*Affectation de la structure sockaddr_in*/
	adr_socket(service, NULL, SOCK_STREAM, &p_adr_socket);

	/*Association de la socket avec ses adresses*/
	h_bind(idSocket, p_adr_socket);

	/* Mise en écoute de la socket pour 10 requêtes max*/
	h_listen(idSocket, NB_REQ_MAX);

	while(1){

		/*Accepte la connexion client sur la socket du serveur*/
		idSocketAccept = h_accept(idSocket, p_adr_client);
		p = fork();
		if (p == 0){
			h_close(idSocket); /*Fermeture de la socket passive*/


			/* Début de la partie */
			strcpy(tampon, "Bienvenue sur MASTERMIND !!\n\nCombien de couleurs voulez vous jouer ? (min 4 max 8) :\n");
			writeServeur = h_writes(idSocketAccept, tampon, NB_OCTETS);
			readServeur = h_reads(idSocketAccept, tampon, NB_OCTETS);
			printf("%s", tampon);
			h_close(idSocketAccept);
			exit(0);
		}else{
			h_close(idSocketAccept);
		}
	}


}

/******************************************************************************/

