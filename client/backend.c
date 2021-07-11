//Encadre Par : Pr M.Aiy kbir

//Devloppe Par : EL GHIZI Yassine - Afkir Hamza

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"backend.h"

void menu()
{
        printf("\n========================================================================================================");
        printf("\n                        \tCOMMANDES                       |           ARGUMENTS\t\t        |\n");
        printf("----------------------------------------------------------------|---------------------------------------\t\n");
        printf("|\t\t   1: Changer L'Utilisateur                    \t|\t\t-                       |\n");
        printf("|\t\t   2: Afficher Par Nom et Prenom \t\t|\t   NOM,PRENOM      \t\t|\n");
        printf("|\t\t   3: Ajouter un contact               \t\t|CODE,NOM,PRENOM,TEL,VILLE,EMAIL\t|\n");
        printf("|\t\t   4: Supprimer un contact par code \t\t|\t       CODE      \t\t|\n");
        printf("|\t\t   5: Modifier Un Contact A Un Code Donne       |CODE,NNOM,NPRENOM,NTEL,NVILLE,NEMAIL   |\n");
        printf("|\t\t   0: C'Est Pour Quitter                \t|\t\t-\t\t\t| \n|");
        printf("---------------------------------------------------------------|---------------------------------------|\t\n");
        printf("\nUtiliser Le Separateur','");
        printf("\nPS mets dans un argument espace si tu veux le laisse vide\nPS2 : Si Vous etes Besoin Du 'menu' il suffit de tapper 'menu'");
        printf("\n\t\t\t\t ---> Votre Commande : ");
};

/*Cette focntion return le nombre des separatuers , ce dernier est utiliser pour assurer la fiablite ddes operations*/
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
}
