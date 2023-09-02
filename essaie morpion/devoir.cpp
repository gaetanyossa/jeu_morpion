#include <stdio.h>
#define nblignes 3
#define nbcolonnes 3

//char grille[nblignes][nbcolonnes];

/*Initialisation de la grille du morpion a vide : */
void initialisergrille(char grille[nblignes][nbcolonnes])
{
	int i, j;
	for (i=0; i<nblignes; i++)
		for (j=0; j<nbcolonnes; j++)
			grille[i][j] = ' ';
}

/*Affichage de la grille du morpion : */
void affichergrille(char grille[nblignes][nbcolonnes])
{
	int i, j;
	for (i=0; i<nblignes; i++)
	{
		for (j=0; j<nbcolonnes; j++)
			printf("%c|", grille[i][j]);
		printf("\n- - -\n");
	}
	return;
}

/*Saisie des coordonnees du symbole a mettre sur la grille. Si les coordonnees
sont en dehors de la grille ou si la case a deja ete remplie, la saisie est
refusee, un message d'erreur s'affiche et le joueur doit rejouer. */
void mettresymbole(char symbole, char grille[nblignes][nbcolonnes])
{
	int ligne, colonne;
	printf("Veuillez donner les numeros de la ligne et de la colonne :");
	do
	{
		scanf("%i %i", &ligne, &colonne);
		if ((ligne>0) && (ligne<=nblignes) && (colonne>0) && (colonne<=nbcolonnes))
		{
			ligne--; /*pour etre compatible avec les indices du tableau*/
			colonne--;
			if (grille[ligne][colonne]!=' ')
				printf("La case a deja ete remplie. Veuillez en choisir une autre :");
			else
			{
				grille[ligne][colonne]=symbole;
				if (symbole=='X')
					symbole='O';
				else
					symbole='X';
			}
		}
		else
			printf("Indice de ligne ou colonne incorrect. Veuillez resaisir :");
	}
	while(grille[ligne][colonne]==' ');
}

/*Test pour voir si l'un des joueurs a gagne : */
int testgagnant(char grille[nblignes][nbcolonnes], char symbole)
{
	int i, j, somme, gagne=0;
	for (i=0; i<nblignes; i++, somme=0)
	{
		for (j=0; j<nbcolonnes; j++)
			somme+=grille[i][j];
		if((somme==237) || (somme==264))
			gagne = 1;
	}
	for(j=0 ; j<nbcolonnes ; j++, somme=0)
	{
		for(i=0 ; i<nblignes ; i++)
			somme+=grille[i][j] ;
		if((somme==237) || (somme==264))
			gagne = 1;
	}
	if ( (grille[0][0] + grille[1][1] + grille[2][2] == 237) ||
			 (grille[0][0] + grille[1][1] + grille[2][2] == 264) ||
			 (grille[0][2] + grille[1][1] + grille[2][0] == 237) ||
			 (grille[0][2] + grille[1][1] + grille[2][0] == 264) )
		gagne = 1;
	if (gagne)
	{
		printf("Felicitations au joueur ayant les %c qui a gagne\n", symbole);
		return 1;
	}
	/* Test si la grille est pleine :*/
	for(i=0; i<nblignes; i++)
		for(j=0; j<nbcolonnes; j++)
			if(grille[i][j] == ' ')
				return 0;
	printf("Aucun des 2 joueurs n'a gagne");
	return 2;
}

int main()
{
	char grille[nblignes][nbcolonnes];
	char symbole;
	initialisergrille(grille);
	affichergrille(grille);
	printf("Veuillez choisir votre symbole, O ou X :");
	scanf("%c", &symbole);
	printf("Veuillez choisir votre symbole, O ou X :");
	scanf("%c", &symbole);
	do
	{
		mettresymbole(symbole, grille);
		affichergrille(grille);
	}
	while(!testgagnant(grille, symbole));
	return 0;
}