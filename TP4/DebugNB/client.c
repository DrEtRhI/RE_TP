/******************************************************************************/
/*			Application: ...					*/
/******************************************************************************/
/*									      */
/*			 programme  CLIENT				      */
/*									      */
/******************************************************************************/
/*									      */
/*		Auteurs : ... 					*/
/*									      */
/******************************************************************************/	


#include <stdio.h>
//#include <curses.h> 		/* Primitives de gestion d'�cran */
#include <sys/signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#include "fon.h"   		/* primitives de la boite a outils */

#define SERVICE_DEFAUT "1111"
#define SERVEUR_DEFAUT "localhost"

#define NB_OCTETS 10000      /* Taille du tampon */

void client_appli (char *serveur, char *service);


/*****************************************************************************/
/*--------------- programme client -----------------------*/

int main(int argc, char *argv[])
{

	char *serveur= SERVEUR_DEFAUT; /* serveur par defaut */
	char *service= SERVICE_DEFAUT; /* numero de service par defaut (no de port) */



	/* Permet de passer un nombre de parametre variable a l'executable */
	switch(argc)
	{
 	case 1 :		/* arguments par defaut */
		  printf("serveur par defaut: %s\n",serveur);
		  printf("service par defaut: %s\n",service);
		  break;
  	case 2 :		/* serveur renseigne  */
		  serveur=argv[1];
		  printf("service par defaut: %s\n",service);
		  break;
  	case 3 :		/* serveur, service renseignes */
		  serveur=argv[1];
		  service=argv[2];
		  break;
    default:
		  printf("Usage:client serveur(nom ou @IP)  service (nom ou port) \n");
		  exit(1);
	}

	/* serveur est le nom (ou l'adresse IP) auquel le client va acceder */
	/* service le numero de port sur le serveur correspondant au  */
	/* service desire par le client */
	
	client_appli(serveur,service);
}

/*****************************************************************************/
void client_appli (char *serveur,char *service)

/* procedure correspondant au traitement du client de votre application */

{
  

	int idSocket, readClient, writeClient;
	struct sockaddr_in *p_adr_socket, *p_adr_client;
	pid_t p;

	//char tampon[NB_OCTETS];
	char *tampon;
  tampon = (char*) malloc (NB_OCTETS * sizeof(char));
	
	/*Cr�ation de la socket protocole internet et mode de connection*/
	idSocket = h_socket(AF_INET, SOCK_STREAM);
	
	/*Affectation de la structure sockaddr_in*/
	adr_socket(service, serveur, SOCK_STREAM, &p_adr_socket);

	/* Connexion a la socket du serveur */
	h_connect(idSocket, p_adr_socket);
	

	/* Description des règles du jeu */
	readClient = h_reads(idSocket, tampon, NB_OCTETS);
	printf("%s", tampon);
	/* Partie en cours */
	while(1){
		readClient = h_reads(idSocket, tampon, NB_OCTETS);
		if (strcmp(tampon, "fin") == 0) break;
		printf("%s", tampon);
		scanf("%s", tampon);
		writeClient = h_writes(idSocket, tampon, NB_OCTETS);
	}
	h_close(idSocket);

 }

/*****************************************************************************/

