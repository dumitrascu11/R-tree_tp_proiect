#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int n,mat_adiac[10][10];
void creare_matrice()
{
	int i, j;
	FILE *f = fopen("Text.txt", "r");
	fscanf(f, "%d", &n);
	for (i = 0; i < n; i++)
	for (j = 0; j < n; j++)
	{
		mat_adiac[i][j] = 0;
	}
	while (!feof(f))
	{
		fscanf(f, "%d", &i);
		fscanf(f, "%d", &j);
		mat_adiac[i][j] = 1;
	}

}
void afisare_matrice()
{
	int i, j;
	for (i = 0; i < n; i++,printf("\n\n"))
	for (j = 0; j < n; j++)
	{
		printf("%d  ",mat_adiac[i][j]);
	}

}

void main()
{
	creare_matrice();
	afisare_matrice();

}