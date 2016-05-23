#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<Windows.h>

int lung_nr(int nr)
{
	int a = 0;
	while (nr)
	{
		nr = nr / 10;
		a++;
	}
	return a;
}
char* fisier_help(char* file_name)
{
	FILE* f = fopen(file_name, "r");
	fseek(f, 0, SEEK_END);
	int lung = ftell(f);
	rewind(f);
	char* sir_cuv=(char*)malloc(lung*sizeof(char));
	
	fread(sir_cuv, 1, lung, f); sir_cuv[lung-3] = 0;
	return sir_cuv;
}
typedef struct rtree
{
	int x1, x2, x3, x4;
	char* nume;
	rtree* children[3];
	bool is_leaf;
};
rtree* root;
rtree* creare_nod()
{
	rtree* nod = (rtree*)malloc(sizeof(rtree));
	nod->nume = (char*)malloc(20 * sizeof(char));
	for (int i = 0; i < 3; i++)
		nod->children[i] = NULL;
	nod->is_leaf = true;
	return nod;
}

bool se_afla_in_drept(rtree* nod1, rtree* nod2)
{
	if (nod1->x1 > nod2->x1) return false;
	if (nod1->x2 > nod2->x2) return false;
	if (nod1->x3 < nod2->x3) return false;
	if (nod1->x4 < nod2->x4) return false;
	return true;
}
bool punct_in_drept(rtree* nod, int a, int b)
{
	if (a < nod->x1) return false;
	if (b < nod->x2) return false;
	if (a > nod->x3) return false;
	if (b > nod->x4) return false;
	return true;
}
rtree* radacina(char* file_name)
{
	FILE* f = fopen(file_name, "r");
	rtree* nod, *root, *travers;
	root = NULL;
	int a, i;
	while (!feof(f))
	{
		nod = creare_nod();
		fscanf(f, "%d", &nod->x1);
		fscanf(f, "%d", &nod->x2);
		fscanf(f, "%d", &nod->x3);
		fscanf(f, "%d", &nod->x4);
		fscanf(f, "%s", nod->nume);
		if (root == NULL)
		{
			root = nod;
			root->is_leaf = true;
		}
		else
		{
			i = 0;
			travers = root;

			while (i < 3)
			{
				if (travers->children[i] != NULL)
				{
					if (se_afla_in_drept(travers->children[i], nod))
					{
						if (travers->children[i]->is_leaf)
						{
							travers->children[i]->children[0] = nod;
							travers->children[i]->is_leaf = false;
							break;
						}
						else
						{
							travers = travers->children[i];
							i = 0;
						}
					}
					else
					{
						i++;
					}
				}
				else
				{
					travers->children[i] = nod;
					travers->is_leaf = false;
					i++;
					break;
				}
			}
		}
	}
	return root;
}
int val = 0;
void afisare_arbore(rtree* root, HDC hDC)
{
	int a, b, c;
	int i = 0;
	HFONT font;
	
	for (i = 0; i < 3; i++)
	{
		if (root->children[i] != NULL)
		{
			
			switch (val)
			{
			case 0:a = 0; b =255 ; c = 5; val++; break;
			case 1:a = 255; b =2 ; c = 5; val++; break;
			case 2:c = 250; b =255 ; a = 5; val++; break;
			case 3:c = 0; b =255 ; a = 255; val=0; break;
		
			}
			HBRUSH      NewBrush;
			POINT       Pt[4];
			NewBrush = CreateSolidBrush(RGB(a, b, c));
			SelectObject(hDC, NewBrush);
			Pt[0].x = root->children[i]->x1+10; Pt[0].y = root->children[i]->x2+33;
			Pt[1].x = root->children[i]->x3+10; Pt[1].y = root->children[i]->x2+33;
			Pt[2].x = root->children[i]->x3+10; Pt[2].y = root->children[i]->x4+33;
			Pt[3].x = root->children[i]->x1+10; Pt[3].y = root->children[i]->x4+33;
			Polygon(hDC, Pt, 4);
			DeleteObject(NewBrush);
			/*MoveToEx(hDC, root->children[i]->x1 + 10, root->children[i]->x2 + 33, NULL);
			LineTo(hDC, root->children[i]->x3 + 10, root->children[i]->x2 + 33);
			LineTo(hDC, root->children[i]->x3 + 10, root->children[i]->x4 + 33);
			LineTo(hDC, root->children[i]->x1 + 10, root->children[i]->x4 + 33);
			LineTo(hDC, root->children[i]->x1 + 10, root->children[i]->x2 + 33);*/
			afisare_arbore((root->children[i]), hDC);
		}

	}


}
void localizare(rtree* root, int a, int b, char**sir)
{

	int i = 0;
	for (i = 0; i < 3; i++)
	{
		if (root->children[i] != NULL)
		{
			if (punct_in_drept(root->children[i], a, b))
			{
				strcpy(*sir, root->children[i]->nume);
				localizare((root->children[i]), a, b, sir);

			}

		}

	}

}
char* nume_localizare(rtree* root, int a, int b)
{
	char *sir = (char*)malloc(28);

	localizare(root, a, b, &sir);
	return sir;

}
void adresa(rtree* root, int a, int b, char**sir)
{

	int i = 0;
	for (i = 0; i < 3; i++)
	{
		if (root->children[i] != NULL)
		{
			if (punct_in_drept(root->children[i], a, b))
			{
				
				
				adresa((root->children[i]), a, b, sir);
				strcat(*sir, root->children[i]->nume);
				strcat(*sir,", ");
			}

		}

	}

}
char* nume_adresa(rtree* root, int a, int b)
{
	char *sir = (char*)malloc(128);
	strcpy(sir, "");
	adresa(root, a, b, &sir);
	sir[strlen(sir) - 2] = 0;
	return sir;

}