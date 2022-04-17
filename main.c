#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define vmin 5
#define vmax 30

struct T_Case
{
    int no_lig , no_col;
};
int nlig, ncol;

struct T_Case vois[4];
struct T_Case pion;

void lire_entier(int *N, int min, int max, char *message)  //Lire un entier compris entre 2 bornes
{
    int test;
    printf("%s",message);
    do
    {
        scanf("%d",N);
        test=(*N>=min) && (*N<=max);
        if (!test)
        {
            printf("Erreur, Saisir une valeur entre %d et %d \n",min,max);
        }
    }
    while (!test);
}


void affiche_grille (int nlig,int ncol,int l,int c)   //Afficher la grille

{
    char tab[nlig][ncol];
    int i,j;

    for (i=1;i<=nlig;i++)
    {
        for (j=1;j<ncol;j++)
        {
            tab[i][j]= '-';
        }
    }
    tab[l][c]='0';
    printf(" ");
    for (j=1;j<ncol;j++)
    {
        printf("  %2d ",j);
    }
    printf("\n");

    for (i=1;i<nlig;i++)
    {
        printf("%2d",i);
        for (j=1;j<ncol;j++)
        {
            printf(" %2c |",tab[i][j]);
        }
        printf("\n");
    }
}


int Voisines (struct T_Case pion, struct T_Case vois[4], int nlig, int ncol)   //Determiner les voisines d'une case donn�e
{
    int i , j ;
    j=0;

    for (i=1 ; (i < 3) && (pion.no_lig+i <= nlig) ; i++)
    {
        vois[j].no_lig=pion.no_lig+i;
        vois[j].no_col=pion.no_col;
        j++;
    }
    for (i=1 ; (i < 3) && (pion.no_col+i <= ncol) ; i++)
    {
        vois[j].no_lig=pion.no_lig;
        vois[j].no_col=pion.no_col+i;
        j++;
    }
    return j;
}



int coup_joueur (struct T_Case *pion )    // G�rer le coup d�un joueur
{
    int i, nbv, prop;
    printf("A toi de jouer !\n");
    nbv = Voisines(*pion, vois, nlig, ncol);

    printf("Propositions : ");

    for (i=0; i<nbv; i++)
    {
        printf("%d: (%d,%d)  ", i, vois[i].no_lig, vois[i].no_col);
    }
    printf("\n");

    do {
        printf("Ton choix : " );
        scanf("%d",&prop);
    }
    while ((prop<0) || (prop>=nbv));

    pion->no_lig = vois [prop].no_lig;
    pion->no_col = vois [prop].no_col;

}


int generer_alea (int a, int b) //Generer un nombre compris entre a et b al�atoirement
{
    int nRand ;
    srand((unsigned)time(0));
    nRand= a + rand() % (b-a+1);
    return nRand;
}


int coup_ordi_hasard (struct T_Case *pion) //G�rer le coup au hasard r�alis� par l�ordinateur
{
    int prop, nbv;
    printf ("A moi de jouer au hasard!\n");
    nbv = Voisines(*pion, vois, nlig, ncol);
    prop=generer_alea(0,nbv);

    pion->no_lig = vois [prop].no_lig;
    pion->no_col = vois [prop].no_col;
}


int nimber (int nlig, int ncol, int i, int j)
{
    int nimb;
    if (((nlig-i) % 3)==((ncol-j) % 3))
    {
        nimb = 0;
    }
    else
    {
        nimb = 1;
    }
    return nimb;
}


int coup_ordi_gagnant (struct T_Case *pion, int nlig, int ncol) //G�rer le coup gagnant effectu� par l�ordinateur
{
    int nbv, nb, i;

    nb = nimber (nlig, ncol, pion->no_lig, pion->no_col);
    if (nb==0)
    {
        coup_ordi_hasard(pion);
    }
    else
    {
        nbv = Voisines(*pion, vois, nlig, ncol); //Nbv = nombre de cases voisines
        for (i=0; i<nbv; i++)
        {
            if (nimber (nlig, ncol, vois[i].no_lig, vois[i].no_col)==0)
            {
                pion->no_lig=vois[i].no_lig;
                pion->no_col=vois[i].no_col;
                i=nbv;

            }
        }

    }
}


int main()
{
    int i=0;
    int tab[30][30];
    int niveau, next,val,fin,tour;
    fin = 0;

    printf("Parametres du jeu : \n");
    lire_entier(&nlig,vmin,vmax,"Nombre de lignes : ");
    lire_entier(&ncol,vmin,vmax,"Nombre de colonnes : ");
    lire_entier(&niveau,1,4,"Niveau de 1 a 4 : ");
    lire_entier(&next,1,2,"Qui commence ? \n L'ordinateur (1) ou le joueur (2) ");
    printf("c'est parti ! \n");

    pion.no_lig=1;
    pion.no_col=1;
    affiche_grille(nlig+1,ncol+1,pion.no_lig,pion.no_col);

    if (next==1) {tour=1;}
    else {tour=-1;}               //Variable pour g�rer les differents tours

    do {

        if (tour==1)
        {
            if (niveau==1)
            {
                coup_ordi_hasard(&pion);
            }
            else if (niveau==2)
            {
                val=generer_alea(1,3);
                if (val==1)
                {
                    coup_ordi_gagnant(&pion,nlig,ncol);
                }
                else
                {
                    coup_ordi_hasard(&pion);
                }
            }
            else if (niveau==3)
            {
                val=generer_alea(1,3);
                if (val==1)
                {
                    coup_ordi_hasard(&pion);
                }
                else
                {
                    coup_ordi_gagnant(&pion,nlig,ncol);
                }
            }
            else
            {
                coup_ordi_gagnant(&pion,nlig,ncol);
            }

            printf ("L'ordinateur deplace le pion en (%d,%d) \n", pion.no_lig,pion.no_col);
            printf("\n");
        }
        else
        {
            coup_joueur(&pion);
            printf ("Le joueur deplace le pion en (%d,%d) \n", pion.no_lig,pion.no_col);
            printf("\n");

        }
        affiche_grille(nlig+1,ncol+1,pion.no_lig,pion.no_col);

        if (pion.no_lig == nlig && pion.no_col == ncol) //tester si le pion est � la derniere case
        {
            fin = 1;
            if (tour == 1)
            {
                printf("J'AI GAGNE !\n");
            }
            else
            {
                printf("TU AS GAGNE !\n");
            }
        }

        tour=-tour;   //Passer au prochain tour
    }
    while (fin==0);

}

