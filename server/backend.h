#ifndef BACKEND_H_INCLUDED
    #define BACKEND_H_INCLUDED

#define NOMFICHIER "data.txt"
#define CLMAX 100

typedef struct
{
    char nom[30],prenom[30],codeContact[30],tel[30],ville[40],email[60];
}Contact;

void saisirContact(Contact [], int* ,char [],char [],char [],char [],char [],char []);
void afficherContact(Contact [], int );
void supprimerContact(Contact [], int*, char[]);
void sauvegarder(Contact [], int );
void sauvegarder_autre_fichier(Contact [], int ,char []);
void lire(Contact [], int* );
void lire_autre_fichier(Contact [], int*,char []);
int chercherville(Contact[],int,char[] );
int fiabilite(char [] );
int menu(void);
void faux_menu(void);
int chercherSans_Email(Contact[],int);
int chercherCode(Contact [],int, char []);
void modifierSolde(Contact [],int,int);
void trierNomPrenom(Contact [],int);
void modifiercode(Contact [], int,char []);
void modifiecontact(Contact [], int ,char [] ,char [] ,char [] ,char [] ,char []);
int chercher_par_nome_par_prenom(int ,Contact [],int ,char [],char []);
char mon_getch(void);
void trie_order_alph(Contact [], int);
int server(void);

#endif
