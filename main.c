#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
/*--------------------------------------------------------------
    D�calage � gauche
-----------------------------------------------------------------*/
void decaleGauche(char chaine[], int deb)
{
    int i;
    for(i=deb; i<strlen(chaine);i++)
        chaine[i]=chaine[i+1];
}
/*--------------------------------------------------------------------
    Supprime les caract�res espaces
----------------------------------------------------------------------*/
void formaterCle(char cle[])
{
    int i;
    // Supprimer les carac�res espaces de la cl�
    for(i=0;i<strlen(cle);i++)
    {
        if(cle[i]==' ')
        {
            decaleGauche(cle,i);
            i--;
        }
        else
            cle[i]=toupper(cle[i]);
    }
}
/*---------------------------------------------------------------------
    crypte un caract�re en fonction de la cl�
----------------------------------------------------------------------*/
char crypteCar(char car, char cle)
{
    char  res='A';
    int posCar = car - 'A';
    res = cle + posCar ;
    if(res > 'Z')
        res-=26;
    return res;
}
/*---------------------------------------------------------------------
    Etape 2
----------------------------------------------------------------------*/
void crypteChaineSansEspaces(char chaine[], char cleC[], char resultat[])
{
    int i, j=0;
     for(i=0;i<strlen(chaine);i++)
    {
        resultat[i]=crypteCar(chaine[i],cleC[j]);
        j++;
        if (j>= strlen(cleC))
            j=0;
    }
    // Ins�rer le caract�re de fin de chaine dans resultat
    resultat[i]='\0';
}
/*---------------------------------------------------------------------
    Etape 3
-----------------------------------------------------------------------*/
void crypteChaineAvecEspaces(char chaine[], char cleC[], char resultat[])
{
    int i, j=0;
     for(i=0;i<strlen(chaine);i++)
    {
        if (chaine[i]==' ')
        {
            resultat[i]=' ';
            continue;
        }
        resultat[i]=crypteCar(chaine[i],cleC[j]);
        j++;
        if (j>= strlen(cleC))
            j=0;
    }
    // Ins�rer le caract�re de fin de chaine dans resultat
    resultat[i]='\0';
}
/*---------------------------------------------------------------------
    Etape 4
-----------------------------------------------------------------------*/
void crypteChaineCaracMinus(char chaine[], char cleC[], char resultat[])
{
    int i, j=0;
     for(i=0;i<strlen(chaine);i++)
    {
        if (chaine[i]==' ')
        {
            resultat[i]=' ';
            continue;
        }
        if(chaine[i]>='a'&& chaine[i]<='z')
        {
            resultat[i]=crypteCar(toupper(chaine[i]),cleC[j]);
            j++;
            if (j>= strlen(cleC))
                j=0;
        }
        else{
            printf("La chaine � coder contient des caract�res � crypt�s !\n");
            strcpy(resultat,""); // r�sultat dans la chaine vide
            break;
        }
    }
    //  caract�re de fin de chaine a resultat
    resultat[i]='\0';
}
/*---------------------------------------------------------------------
    Etape 5
-----------------------------------------------------------------------*/
void crypteChaineCaracMinusCleAvecEspace(char chaine[], char cleC[], char resultat[])
{
    formaterCle(cleC);
    crypteChaineCaracMinus(chaine,cleC,resultat);
}
/*--------------------------------------------------------------
    Etape 6
--------------------------------------------------------------*/
void transformCle(char cleCrypte[], char cleDecrypte[])
{
    int i;
    formaterCle(cleCrypte); // Formater la cl�
    for(i=0;i<strlen(cleCrypte);i++)
        cleDecrypte[i]=cleCrypte[i]=='A'?'A':'Z'-(cleCrypte[i]-'A'-1);
    cleDecrypte[i]='\0';
}
void decrypte(char chaine[], char cle[], char resultat[])
{
    char cleDecry[50];
    transformCle(cle,cleDecry);
    crypteChaineAvecEspaces(chaine,cleDecry,resultat);
}
int main()
{
    setlocale(LC_CTYPE,""); // Pour pouvoir afficher des caract�res sp�ciaux
    char chaine[]="il fera beau demain" ; // chaine � crypter
    char chaine2[]="RETAQVFABACAE" ; // chaine � crypter
    char cleC[]="MAISON" ; // Cl� de cryptage
    char resultat[256] ; // chaine crypt�e
    int i=0, j=0;

    /* Lecture des chaines � crypter et la cl� */
    printf("Donner la chaine a crypter : ");
    scanf("%s", chaine);
    printf("Donner la chaine cle :");
    scanf("%s", cleC);
//
    printf("%s - %s\n", chaine, cleC);
    crypteChaineSansEspaces(chaine, cleC, resultat);
    crypteChaineAvecEspaces(chaine,cleC,resultat);
    crypteChaineCaracMinus(chaine, cleC, resultat);
    crypteChaineCaracMinusCleAvecEspace(chaine,cleC,resultat);
    decrypte(chaine2,cleC,resultat);
    printf("Message � crypter = %s\n",chaine);
    printf("Cl� de cryptage = %s\n",cleC);
    printf("Chaine crypt�e : %s\n", resultat);
    return 0;
}
