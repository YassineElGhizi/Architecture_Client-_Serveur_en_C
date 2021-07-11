//Encadre Par : Pr M.Aiy kbir

//Devloppe Par : EL GHIZI Yassine - Afkir Hamza
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

#define ERROR 	(-1)
#define PORT 5555
#define TAILLEMESSAGE 299
#define IPADRESSE "127.0.0.1"

void aff_addr(struct sockaddr_in addr)
{
   printf("\nIP : %s, port : %d",(char *)inet_ntoa(addr.sin_addr.s_addr),ntohs(addr.sin_port));
}

void afficheErrorSortie(char *nomFct)
{
     printf("\n %s -> %s ", nomFct, strerror(errno));
     exit(1);
}

int client()
{
   char msg[TAILLEMESSAGE+1] , a[30];
   int sClient,ret_fct ,boul = 0;
	struct sockaddr_in  addrServeur;
	int oct, flg;
   char cod_uti[30] ,nom_prenom[30] ,buff[300] ,buff2[300] , alpha[300];

   sClient=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
   if(sClient==ERROR)
   {
      afficheErrorSortie("socket()");
      exit(1);
   }

	addrServeur.sin_family = AF_INET;
   addrServeur.sin_port   = htons(PORT);
   addrServeur.sin_addr.s_addr=inet_addr(IPADRESSE);

   ret_fct=connect(sClient,(struct sockaddr*)&addrServeur,sizeof(struct sockaddr));
   if(ret_fct==ERROR)
   {
      afficheErrorSortie("connect()");
      exit(1);
   }

   printf("\nConnexion ...");
   aff_addr(addrServeur);
   
   flg = fcntl(sClient,F_GETFL,0);
   fcntl(sClient,F_SETFL,flg | O_NONBLOCK);
   flg = fcntl(STDIN_FILENO,F_GETFL,0);
   fcntl(STDIN_FILENO,F_SETFL,flg | O_NONBLOCK);

   code :
   bzero(cod_uti , sizeof(cod_uti));
   bzero(nom_prenom,sizeof(nom_prenom));
   bzero(buff2 , sizeof(buff2));
   printf("\n\t\tTapper le Code_Utilisateur\n");
   get :
   gets(cod_uti);/*Le Code Utilisateur est en Arrier Plan*/

   /*Même si le Tampon(Buffer) du Clavier est Vide, fcntl() joue le Role d'une Boucle Afin d'Eliminer le Blokage
   c'est-à-dire que gets() sera non bloquant donc --->Meme le Vide Représenté Par -> "", Sera lu par gets()
   et Cela Sera dû à une Boucle infinie de [Permission Denied] Acuse du Filtre Du Ligne 128 */
   if(strcmp(cod_uti , "") == 0)
   {
      goto get;
   }
   strcat(cod_uti , ",");
   fflush(stdin);

   if(strcmp(cod_uti , "admin,") == 0){  goto repeter;}
   else
   if(strcmp(cod_uti , "invite,") == 0)
                                       {
                                       strcat(buff2 , cod_uti);
                                       strcat(buff2 , "2,");
                                       invi :
                                       bzero(a , sizeof(a));
                                       bzero(msg , sizeof(msg));
                                       bzero(nom_prenom , sizeof(nom_prenom));

                                       printf("\n\t\t1: Entrer Le Nom et Prenom du Conatct Separe Par ,\n\t\t2: Changer l'Utilisateur\n\t\t0: Pour quiter\n\t\tVotre Choix :");
                                       gett :
                                       gets(a);
                                       fflush(stdin);
                                       if( strcmp(a , "1") == 0)
                                       {
                                          printf("\nEntrer NOM,PRENOM : ");
                                          abc :
                                          gets(nom_prenom);

                                          if(strcmp(nom_prenom , "") == 0)
                                          {
                                             goto abc;
                                          }

                                          if(fiabilite(nom_prenom) != 1)
                                          {
                                             printf("Syntaxe Error\n");
                                             goto invi;
                                          }

                                          strcat(msg , buff2);
                                          strcat(msg , nom_prenom);

                                          write(sClient , msg , sizeof(msg)+1);

                                          while(1)
                                          {
                                             bzero(msg , sizeof(msg));
                                             oct = read(sClient , msg, TAILLEMESSAGE+1);          
                                             if(oct > 1)
                                             {    
                                                sprintf(alpha , "%s" , msg);
                                                puts(alpha);
                                                bzero(msg , sizeof(msg));
                                                goto invi;
                                                break;
                                              
                                             }
                                          }
                                       }
      else
      if(strcmp(a , "2") == 0)
      {
         goto code;
      }
      else
      if( strcmp(a , "0") == 0)
      {
         exit(1);
      }
      else
      if(strcmp(a , "") == 0)
      {
         goto gett;
      }
      else
      {
         printf("\nCommande n existe pas\n");
         goto invi;
      }
   }
   else
   {
      printf("\n------> Permission Denied\n");
      goto code;
   }
 
   repeter :
   menu();

	while(1)
   {
      bzero(msg , sizeof(msg));
		if(gets(msg)>0)
      {
         if(strcmp(msg , "0") == 0){goto close;}
         else
         if(strcmp(msg , "menu") == 0){goto repeter;}
         else
         if(strcmp(msg , "1") == 0){ goto code;}
         else
         /*Du Deppart il n y a pas d envois des commandes qui ont une fausse syntaxe*/
         if( fiabilite(msg) == 0 || fiabilite(msg) == 2 || fiabilite(msg) == 6 || fiabilite(msg) == 1 )
         {
            bzero(buff , sizeof(buff));
            strcat(buff , cod_uti);
            strcat(buff , msg);
            write(sClient,buff,strlen(buff)+1);
            bzero(buff , sizeof(buff));
         }
         else
            {
               printf("Le Nombre Des Arguments Est errone\n");
               goto repeter;
            }
      }
      bzero(msg , sizeof(msg));
		oct=read(sClient,msg,TAILLEMESSAGE+1);
		if(oct>0)
      {
         printf("\n%s",msg);
		}
	}
   close :
   close(sClient);

   return 0;
}
