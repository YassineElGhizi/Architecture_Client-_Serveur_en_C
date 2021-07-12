#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>

#include "backend.h"
#include "server.h"

/*Supposant Que Les Codes des Utilisateur Sont Les Suivants:*/
//#define CODE_ADMINISTRATEUR "admin"
//#define CODE_INVITE "invite"

#define ERRO 	(-1)
#define PORT 5555
#define NBRECON 10

void aff_addr(struct sockaddr_in x)
{
   printf("\nConnexion Aceepted From IP : %s, port : %d\n",(char *)inet_ntoa(x.sin_addr.s_addr),ntohs(x.sin_port));
}

void succ(struct sockaddr_in x ,char *a ,char *b)
{
    printf("Ur Msg %s With success %s IP:%s, PORT %d\n",a ,b ,(char *)inet_ntoa(x.sin_addr.s_addr),ntohs(x.sin_port));
}

void afficheErrorSortie(char *nomFct)
{
     printf("\n %s -> %s ", nomFct, strerror(errno));
     getchar();
}

int server()
{
    Contact contacts[CLMAX];
    int N=0 , nmbr_ceparatuer=0 , ret_menu = -1;
	struct sockaddr_in addrServeur,addrClient;
	int sClient,sServeur , flg ,indicee = -1;
	int longAddr,ret,oct;
	char msg[800] , utilisateur[30] , cmd[30] ,pt3[420];
	pid_t fils;
	char* pont;
	char nom_pont[30] , prenom_pont[30];
	char code_contact_pont[30] ,tel_pont[30] ,ville_pont[30] ,email_pont[60] ,new_code_contact[30],file_name_pont[30];
	char permission[30] = "Permission denaied \n" ,pp[30] = "Le Serveur est en Pause \n" ,in[30] = "Client Introuvable\n";
	char cmd_error[30] = "Commande n'existe Pas\n" ,deja[30] = "Ce Contact est Deja Existe\n";
	

	men:
	bzero(code_contact_pont , sizeof(code_contact_pont));
	bzero(new_code_contact , sizeof(new_code_contact));
	bzero(nom_pont , sizeof(nom_pont));
	bzero(prenom_pont , sizeof(prenom_pont));
	bzero(tel_pont , sizeof(tel_pont));
	bzero(ville_pont , sizeof(ville_pont));
	bzero(email_pont , sizeof(email_pont));
	bzero(file_name_pont , sizeof(file_name_pont));
	bzero(msg , sizeof(msg));
	bzero(pt3 , sizeof(pt3));
	do{
		ret_menu = menu();
		switch(ret_menu)
		{
			case 1 : goto start; break;
			case 0 : goto close; break;
			case 2 : printf("\nLa Pause N est Valide Sauf Lorsque le Serveur est Actif\n");
					 goto men;
					 break;
			case 3 : lire(contacts,&N);
					 afficherContact(contacts,N);
					 goto men;
					 break;
			case 4 : lire(contacts,&N);
					 trie_order_alph(contacts ,N);
					 sleep(1);
					 lire(contacts,&N);
					 goto men;
					 break;
			case 5 : lire(contacts,&N);
					 printf("\nEntrer le nom de La Ville :");
					 gets(ville_pont);
					 chercherville(contacts,N,ville_pont );
					 sleep(1);
					 goto men;
					 break;
			case 6 : lire(contacts,&N);
					 chercherSans_Email(contacts ,N);
					 goto men;
					 break;
			case 7 : lire(contacts,&N);
					 printf("Entrer Le Code Du Conatct a Modifie\n");
					 gets(code_contact_pont);
					 indicee = chercherCode(contacts,N,code_contact_pont);
					 printf("\nEntrer Le Noveau Code : ");
					 gets(new_code_contact);
					 modifiercode(contacts ,indicee,new_code_contact);
					 sauvegarder(contacts, N);
					 printf("\n\tOperation Termine");
					 goto men;
					 break;
			case 8 : lire(contacts,&N);
					 printf("\nEntrer le Nom du Fichier[Nom_Fichier.Type.Fichier]");
					 gets(file_name_pont);
					 sauvegarder_autre_fichier(contacts,N,file_name_pont);
					 printf("\n\tOperation Termine");
					 goto men;
					 break;
			case 9 : printf("\nEntrer le Nom du Fichier[Nom_Fichier.Type.Fichier]");
					 gets(file_name_pont);
					 lire_autre_fichier(contacts,&N, file_name_pont );
					 afficherContact(contacts,N); printf("\n\tOperation Termine");
					 goto men;
					 break;
	 		case 10 :lire(contacts,&N);
			 		 printf("\t\tEnter les Inforamtion du Contact Selon l'Order Suivant:\n\t\tCODE,NOM,PRENOM,TEL,VILLE,EMAIL\n");
			 		 gets(pt3);
			 		 nmbr_ceparatuer = fiabilite(pt3);
					 if(nmbr_ceparatuer != 5)
					 {
						printf("Syntaxe N'est pas valide\n");
						goto men;
					 }
					 pont = strtok(pt3 , ",");
    				 strcpy(code_contact_pont , pont);

					 if(chercherCode(contacts,N,code_contact_pont) >= 0 )
					 {
						 printf("Ce Contact est Deja Existe\n" , code_contact_pont);
						 goto men;
						 break;
					 }

					 pont = strtok(NULL , ",");
       			     strcpy(nom_pont , pont);

    				 pont = strtok(NULL , ",");
    				 strcpy(prenom_pont , pont);

    			     pont = strtok(NULL , ",");
	       			 strcpy(tel_pont , pont);

    				 pont = strtok(NULL , ",");
    				 strcpy(ville_pont , pont);

	       			 pont = strtok(NULL , ",");
    				 strcpy(email_pont , pont);

					 saisirContact(contacts , &N,code_contact_pont ,nom_pont ,prenom_pont ,tel_pont ,ville_pont ,email_pont);
					 sauvegarder(contacts, N);
					 goto men;
					 break;
			case 11 :lire(contacts,&N);
					 printf("Entrer Le CODE du Clinet\n");
					 gets(code_contact_pont);

				     indicee = chercherCode(contacts,N,code_contact_pont);
					 sleep(1);
					 if(indicee < 0)
					 {
						 printf("\tClient Introuvable\n");
                         goto men;
					 }
					 printf("\t\tEntrer les Informations du Contact Selon l'Ordre Suivants\n\t\tNOM,PRENOM,TEL,VILLE,EMAIL\n");
					 gets(msg);
					 if(fiabilite(msg) != 4)
					 {
						 printf("Syntaxe N'est pas valide\n");
						 goto men;
					 }
					pont = strtok(msg , ",");
       				strcpy(nom_pont , pont);

    				pont = strtok(NULL , ",");
					strcpy(prenom_pont , pont);

 	   				pont = strtok(NULL , ",");
	      			strcpy(tel_pont , pont);

    				pont = strtok(NULL , ",");
    				strcpy(ville_pont , pont);

	       			pont = strtok(NULL , ",");
					strcpy(email_pont , pont);

					modifiecontact(contacts ,indicee ,nom_pont ,prenom_pont , tel_pont , ville_pont ,email_pont);
					sauvegarder(contacts, N);
					printf("\n\tOperation Termine\n");
					goto men;
					break;
			case 12 : lire(contacts,&N);
					  printf("\nEntrer Le Code du Contact\n");
					  gets(code_contact_pont);
					  supprimerContact(contacts ,&N ,code_contact_pont);
					  sauvegarder(contacts, N);
					  printf("\n\tOperation Termine\n");
					  goto men;
		}
	}while(ret_menu != -1);

	start :
	/* Lorsqu'on Demare Le Serveur Le Serveur Restaure La Liste Des Contacts De Puis Le Fichier "DATA.txt" */
	lire(contacts,&N);
	addrServeur.sin_family = AF_INET;
	addrServeur.sin_port = htons(PORT);
	addrServeur.sin_addr.s_addr=0;

	sServeur = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(sServeur==ERRO)
	{
		afficheErrorSortie("socket()");
		exit(1);
	}

	ret = bind(sServeur,(struct sockaddr*)&addrServeur,sizeof(struct sockaddr_in));
    if(ret==ERRO){
		afficheErrorSortie("bind()");
		exit(1);
	}

	printf("\nServeur starting!!  ... \n");

	ret=listen(sServeur,NBRECON);
    if(ret==ERRO)
	{
		afficheErrorSortie("listen()");
		exit(1);
	}

	while(1)
	{

		longAddr=sizeof(struct sockaddr_in);
		sClient=accept(sServeur,(struct sockaddr *)&addrClient,&longAddr);
        if(sClient==ERRO)
		{
			afficheErrorSortie("accept()");
			exit(1);
		}
		printf("\n------Connected-------------------------------------------");
		aff_addr(addrClient);

		flg = fcntl(sClient,F_GETFL,0);
    	fcntl(sClient,F_SETFL,flg | O_NONBLOCK);
   		flg = fcntl(STDIN_FILENO,F_GETFL,0);
   		fcntl(STDIN_FILENO,F_SETFL,flg | O_NONBLOCK);

		if((fils = fork())==0)
		{
			close(sServeur);
    		while(1)
			{
				repeter :
				bzero(utilisateur , sizeof(utilisateur));
				bzero(cmd , sizeof(cmd));
				bzero(pt3 , sizeof(pt3));
				bzero(nom_pont , sizeof(nom_pont));
				bzero(prenom_pont , sizeof(prenom_pont));
				bzero(code_contact_pont , sizeof(code_contact_pont));
				bzero(tel_pont , sizeof(tel_pont));
				bzero(ville_pont , sizeof(ville_pont));
				bzero(email_pont , sizeof(email_pont));

				oct=read(sClient,msg,sizeof(msg)+1);
				if(oct>0)
				{
					/*Le Principe C'est Le Fait De Recus Une Commande Complexe Sous Forme  : CODE_UTILISATER,CODE_COMMANDE,ARGUMENTS*/
					/*Et L Application Du Filtrage Suivant : 1er Filtrage sur le Nombre des Separateurs*/
					/*									   : 2eme Filtrage sur [Code_Utilisateur]  */
					/*									   : 3eme Filtrage sur [Code_Commande] */

 		   			printf("\nCommande Recu de puis [IP %s et PORT %d]--> %s  (%d octets)\n",(char *)inet_ntoa(addrClient.sin_addr.s_addr),ntohs(addrClient.sin_port),msg,oct);
					/*Une Fois La Commande Est Recus On Commance Le Decapsulation*/
					/*1er Filtrage*/
					nmbr_ceparatuer = fiabilite(msg);

					/* 2eme Filtrage*/
					pont = strtok(msg , ",");
					strcpy(utilisateur , msg);
					printf("\n->utilisateur : %s" , utilisateur);

					/*Les Utilisateurs Avec Un Code Non Valied n'ont acces a aucun operation*/
					if( strcmp(pont , "admin") != 0 && strcmp(pont , "invite") != 0)
					{
						printf("\n->utilisateur : %s" , pont);
						non_valide :
						write(sClient,permission,sizeof(permission)+1);
						goto repeter;
					}

					/*Basé sur le 1er Filtrage On Connait La Commande*/
					if(nmbr_ceparatuer == 2)
					{
						pont = strtok(NULL , ",");
						strcpy(cmd , pont);
						if( strcmp( cmd , "4" )== 0 )/* 3eme Filtrage */
							{
								pont = strtok(NULL , "");
								strcpy(code_contact_pont , pont);
								supprimerContact(contacts ,&N ,code_contact_pont);
								printf("a Supprimer Le Contact du Code %s" , code_contact_pont);
								sprintf(msg , "Le Contact de Code %s est supprimer\n" , code_contact_pont );
								write(sClient , msg , sizeof(msg) + 1);
								bzero(msg , sizeof(msg));
								goto repeter;
							}
						else
						if(strcmp( cmd , "4") != 0)
						{
							write(sClient , cmd_error , sizeof(cmd_error) + 1);
							goto repeter;
						}
					}
					else
					if(nmbr_ceparatuer == 3)
						{	
							 if( strcmp( utilisateur , "invite" ) == 0 || strcmp( utilisateur , "admin") == 0 )
							 {
							 	pont = strtok(NULL , ",");
							 	strcpy(cmd , pont);
							 }
								if( strcmp( cmd , "2" )== 0 )
									{
											pont = strtok(NULL , "");
											strcpy(pt3 , pont);

											pont = strtok(pt3 , ",");
       										strcpy(nom_pont , pont);

       										pont = strtok(NULL , "");
       										strcpy(prenom_pont , pont);

											chercher_par_nome_par_prenom(sClient , contacts , N,nom_pont,prenom_pont);
											printf(" a cherche par le nom %s et le prenom %s" , nom_pont , prenom_pont);
											goto repeter;
										}
										else
										if(strcmp( cmd , "2") != 0)
										{
											write(sClient , cmd_error , sizeof(cmd_error) + 1);
											goto repeter;
										}
							}
					else
						if( nmbr_ceparatuer == 7 )
							{
								if( strcmp( utilisateur , "admin") != 0  )
								{
									goto non_valide;
								}
								pont = strtok(NULL , ",");
								strcpy(cmd , pont);

								if(strcmp( cmd , "3") == 0)
								{

									pont = strtok(NULL , "");
									strcpy(pt3 , pont);

 	      							pont = strtok(pt3 , ",");
    								strcpy(code_contact_pont , pont);
									if(chercherCode(contacts,N,code_contact_pont) >= 0 )
					 				{				
						 				write(sClient , deja , sizeof(deja));
						 				goto repeter;
						 				break;
					 				}

									pont = strtok(NULL , ",");
       								strcpy(nom_pont , pont);

       								pont = strtok(NULL , ",");
    								strcpy(prenom_pont , pont);

    	   							pont = strtok(NULL , ",");
	       							strcpy(tel_pont , pont);

    								pont = strtok(NULL , ",");
    								strcpy(ville_pont , pont);

	       							pont = strtok(NULL , ",");
    								strcpy(email_pont , pont);

									saisirContact(contacts , &N,code_contact_pont ,nom_pont ,prenom_pont ,tel_pont ,ville_pont ,email_pont);
									sprintf(msg , "L ' ajoute de Conatct De Code %s est termine avec succes" , code_contact_pont);
									write(sClient , msg , sizeof(msg) + 1);
									goto repeter;
								}

								if(strcmp( cmd , "5") == 0)
								{
									pont = strtok(NULL , "");
									strcpy(pt3 , pont);

									pont = strtok(pt3 , ",");
    								strcpy(code_contact_pont , pont);

									indicee = chercherCode(contacts,N,code_contact_pont);
									sleep(1);
											if(indicee < 0){ write(sClient , in , sizeof(in) + 1); goto repeter; }

									pont = strtok(NULL , ",");
       								strcpy(nom_pont , pont);

    								pont = strtok(NULL , ",");
									strcpy(prenom_pont , pont);

 	   								pont = strtok(NULL , ",");
	      							strcpy(tel_pont , pont);

    								pont = strtok(NULL , ",");
    								strcpy(ville_pont , pont);

	       							pont = strtok(NULL , ",");
    								strcpy(email_pont , pont);

									modifiecontact(contacts ,indicee ,nom_pont ,prenom_pont , tel_pont , ville_pont ,email_pont);
									printf(" a Modifier Le Conatct Du Code %s" , code_contact_pont);
									sprintf(msg , "Modification de Conatct De Code %s est termine avec succes" , code_contact_pont);
									write(sClient , msg , sizeof(msg) + 1);
									bzero(msg , sizeof(msg));
								}

							}
				}
				if(gets(msg))
				{
	       			if(strcmp(msg,"0") == 0)
					   {
						   printf("Fermeture En Cour ....\n");
						   goto close;
						   break;
					   }
					else
					if(strcmp(msg,"1") == 0)
						{
							write(sClient,pp,sizeof(pp)+1);
							printf("\n\t\tTapper 'stop' Pour Annuler La Pause\n");
							while(1)
							{
								gets(msg);
								if(strcmp(msg , "stop") == 0)
								{
									goto repeter;
									break;
								}
								bzero(msg , sizeof(msg));
							}
							goto repeter;
						}
					else
					 	if(strcmp(msg , "menu") == 0)
					 	{
							bzero(msg , sizeof(msg));
							faux_menu();
						}
					else
						if(strcmp(msg , "2") == 0)
						{
							afficherContact(contacts,N);
							sleep(1);
							goto repeter;
						}
					else
						if(strcmp(msg , "3") == 0)
						{
							chercherSans_Email(contacts ,N);
							goto repeter;
						}
				}
			}
		}
	}
	close :
	printf("Tous Modifications Des Donnes a Enregistrer par Default Dans Le Fichier data.txt");
	sauvegarder(contacts, N);/*Le Serveur Sauvegarde La Liste Des Contacts Dans Le Fichier "DATA.txt" Lorsqu'on Arrete Le Serveur */
	close(sServeur);
	close(sClient);
	exit(1);
	return 0;
}
