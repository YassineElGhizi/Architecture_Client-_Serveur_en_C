#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"backend.h"
#include"server.h"

int menu()
{
    int choix = -1;
    while(1){
        printf("\n\t\t =======================================================================\t");
        printf("\n\t\t|                         \tCOMMANDES                               |\n");
        printf("\t\t|--------------------------Welcome To GI Server-------------------------|\t\n");
        printf("\t\t|\t\t   1: Demarrer Le Server               \t\t\t|\n");
        printf("\t\t|\t\t   2: Pauser Le Server            \t\t\t|\n");
        printf("\t\t|\t\t   3: Afficher Toute La Liste   \t \t\t|\n");
        printf("\t\t|\t\t   4: Tri Par Order Alphabitique Selon Nom     \t\t|\n");
        printf("\t\t|\t\t   5: Chercher Par ville                       \t\t|\t \n");
        printf("\t\t|\t\t   6: Les Contacts Qui n'Ont pas Un Email               |\n");
        printf("\t\t|\t\t   7: Modifie Le Code D'Un Contact\t                |\n");
        printf("\t\t|                  8: Sauvegarder Dans Un fichier a Choisir  \t        |\n");
        printf("\t\t|                  9: Lister Tous Les Contacts Stocke Dans un Fichier\t|\n");
        printf("\t\t|\t\t   10:Ajouter Un Contact               \t\t\t|\n");
        printf("\t\t|\t\t   11:Modifier Un Contact              \t\t\t|\n");
        printf("\t\t|\t\t   12:Supprimer Un Contact            \t\t\t|\n");
        printf("\t\t|\t\t   0: C'Est Pour Quitter                \t\t|\n");
        printf("\t\t|-----------------------------------------------------------------------|\t\n");
        printf("\t \tApres Le Demarager  ---> Taper 'menu' Pour Consulter le Menu\n");
        printf("\t\t \t\t    --->Taper le code de l'operation : ");
        decision :
        scanf("%d" ,&choix);
        if( choix == -1)
        {
            goto decision;
        }
        mon_getch();
        
        if(choix >=0 && choix < 13){    return choix;   break;  }
        printf("\t----> Votre Code de Commande N'Existe Pas <----\n");
    }
};

void faux_menu()
{
        printf("\n\t\t =======================================================================\t");
        printf("\n\t\t|                         \tCOMMANDES                               |\n");
        printf("\t\t|--------------------------Welcome To GI Server-------------------------|\t\n");
        printf("\t\t|\t\t   1: Pauser Le Server            \t\t\t|\n");
        printf("\t\t|\t\t   2: Afficher Toute La Liste   \t \t\t|\n");
        printf("\t\t|\t\t   3: Les Contacts Qui n'Ont pas Un Email               |\n");
        printf("\t\t|\t\t   0: C'Est Pour Quitter                \t\t|\n");
        printf("\t\t|-----------------------------------------------------------------------|\t\n");
        printf("\t\t \t\t    ---> Taper 'menu' Pour Consulter le Menu\n");
        printf("\t\t \t\t    --->Taper le code de l'operation : ");
};

void sauvegarder(Contact t[], int n){
     FILE* fl;

     fl = fopen(NOMFICHIER,"w");
     if(fl==NULL){  printf("\nErreur d'ouverture de fichier. ");    }
     else{
        fwrite(&n,sizeof(int),1,fl);
        fwrite(t,sizeof(Contact), n,fl);
        };
    fclose(fl);
};

void sauvegarder_autre_fichier(Contact t[], int n ,char new_name[])
{
    FILE* fl;
    fflush(stdin);
    fl = fopen(new_name,"w");
    if(fl==NULL){  printf("\nErreur d'ouverture de fichier. ");    }
    else{
        fwrite(&n,sizeof(int),1,fl);
        fwrite(t,sizeof(Contact), n,fl);
    };
    fclose(fl);
};

void lire(Contact t[], int *n )
{
    FILE* fl;
    fl = fopen(NOMFICHIER,"r");
    if(fl==NULL){ printf("\nErreur d'ouverture de fichier %s. " , NOMFICHIER); }
    else{
        fread(n,sizeof(int),1,fl);
        fread(t,sizeof(Contact),*n,fl);
        printf("--> Par Default Vous etes dans le fichier:\t %s\n" ,NOMFICHIER);
        };
    fclose(fl);
};

void lire_autre_fichier(Contact t[], int *n, char nom[] )
{
    FILE* fl;

    fflush(stdin);
    fl = fopen(nom,"r");
    if(fl==NULL){ printf("\nErreur d'ouverture de fichier %s.\n" , nom); }
    else{
        fread(n,sizeof(int),1,fl);
        fread(t,sizeof(Contact),*n,fl);
        printf("-->Vous etes dans le fichier:\t %s\n" ,nom);
        };
    fclose(fl);
};

int chercherville(Contact t[],int n,char v[])
{
    int i, flg=0;
    printf("\n [Indice] \tCode \t\tName\t   Prenom\t Ville\t");

    for(i=0;i<n;i++)
    {
        if(strcmp(t[i].ville, v) ==0 )
        {
            printf("\n-->[%d]\t\t%s\t%s\t%s\t%s" , i, t[i].codeContact, t[i].nom, t[i].prenom, t[i].ville);
            flg=1;
        }
    }
    if(flg == 0){  printf("\nClient Introuvable\n"); }
};

int chercherSans_Email(Contact t[],int n)
{
    int i, flg=0;
    printf( "\n============================ Affichage en cour =========================================\n");
    printf("\n [Indice] \tCode \t\tName\t Prenom\t Ville\t");
    for(i=0;i<n;i++)
    {
        if(strcmp(t[i].email, " ") ==0 )
        {
            printf("\n-->[%d]\t\t%s\t%s\t%s\t%s" , i, t[i].codeContact, t[i].nom, t[i].prenom, t[i].email);
            flg=1;
        }
    }
    if(flg == 0){ printf("\nContact Introuvable");}
    printf("\n============================== Fin D Afichage =========================================\n");
};

int chercherCode(Contact t[],int n, char code[])
{
    int i, trouve=-1;
    for(i=0;i<n;i++)
    {
        if(strcmp(t[i].codeContact, code)==0)
        {
            trouve=i;
            break;
        }
    }
    return trouve;
};


void modifiercode(Contact t[], int ind,char s[])
{
    strcpy(t[ind].codeContact,s);
};

void modifiecontact(Contact t[], int ind ,char b[] ,char c[] ,char d[] ,char e[] , char f[])
{
    strcpy(t[ind].nom , b);
    strcpy(t[ind].prenom , c);
    strcpy(t[ind].tel , d);
    strcpy(t[ind].ville , e);
    strcpy(t[ind].email , f);
};

char mon_getch(void)
{
    char x ,y;

    scanf("%c",&x);
    printf("Tapper :[Entrer] Pour Confirmer -- [Ctrl + C] Quiter\n");
    scanf("%c",&y);
    return (x);
};

void trie_order_alph(Contact t[],int n)
{

    int i,j ,flg;
     char tmp_char[30];
    for(i=0 ; i<n ;i++)
    {
        for(j=0 ; j<n ;j++)
        {
            flg = strcmp(t[i].nom ,t[j].nom);
            if(flg<0)
            {
                strcpy(tmp_char ,t[i].nom);
                strcpy(t[i].nom ,t[j].nom);
                strcpy(t[j].nom ,tmp_char);
            }
        }

    }
    printf("==================La Liste est trie par ordre aphabitique====================\n");
    printf("\n-->NOM");
    for(i=0;i<n;i++)
        {
            printf("\n-->%s" , t[i].nom);
        }
        printf("\n=================================================================\n");
};

int fiabilite(char msg[] )
{
    char str[300], ch = ',';
    int i, freq = 0;
    strcpy(str , msg);
    for(i = 0; str[i] != '\0'; ++i)
    {
        if(ch == str[i])
            ++freq;
    }
    return freq;
};

void saisirContact(Contact t[], int *pn,char a[] ,char b[] ,char c[] ,char d[] ,char e[] ,char f[])
{
    strcpy(t[*pn].codeContact , a);
    strcpy(t[*pn].nom , b);
    strcpy(t[*pn].prenom , c);
    strcpy(t[*pn].tel , d);
    strcpy(t[*pn].ville , e);
    strcpy(t[*pn].email , f);
    (*pn)++;
    printf("\nL admin est ajoutne le clien du code %s" ,a);
};


int chercher_par_nome_par_prenom(int sClient ,Contact t[],int n,char v[],char w[])
{
    int i, flg=0;
    char buf1[300];
    for(i=0;i<n;i++)
        if(strcmp(t[i].nom, v)==0 && strcmp(t[i].prenom ,w)==0)
        {
            sprintf(buf1 ,"\nCODE : %s\tNOM :%s\tPRENOM : %s\tEMAIL :%s  VILLE: %s\tTEL: %s\n" ,t[i].codeContact, t[i].nom, t[i].prenom, t[i].email , t[i].ville , t[i].tel);
            write(sClient,buf1,strlen(buf1)+1);
            bzero(buf1 , sizeof(buf1));
            sleep(1);
            flg=1;
        }
     if(flg == 0){ strcpy(buf1 , "\nContact Introuvable");}
     write(sClient , buf1 , strlen(buf1) + 1);
};

void  afficherContact(Contact t[], int n)
{
    int i;
    printf("===================================================================\n");
    printf("\n-->[Indice]\tCode\t   Nom\t\tPrenom\tEmail");

    for(i=0;i<n;i++)
    {
        //printf("\n-->[%d]\t\t%s\t%s\t%s\t\t%s" , i ,t[i].codeContact, t[i].nom, t[i].prenom, t[i].email);
        printf("\n-->[%d]\t\t%-10s%-15s%-10s%-10s" , i ,t[i].codeContact, t[i].nom, t[i].prenom, t[i].email);
    }
    printf("\n=================================================================");
};

void  supprimerContact(Contact t[], int *pn, char cod[])
{

      int i;
      for(i=0;i<*pn;i++)
          if( strcmp(cod , t[i].codeContact)==0 )
          {
            t[i]=t[i+1];
            (*pn)--;
            }
};
