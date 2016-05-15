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
rtree* radacina(char* file_name)
{
	FILE* f = fopen(file_name, "r");
	rtree* nod, *root, *travers;
	root = NULL;
	int a, i;
	while (!feof(f))
	{
		nod = creare_nod();
		fscanf(f, "%d", &a);
		nod->x1 = a;
		fscanf(f, "%d", &a);
		nod->x2 = a;
		fscanf(f, "%d", &a);
		nod->x3 = a;
		fscanf(f, "%d", &a);
		nod->x4 = a;
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
void afisare_arbore(rtree* root, HDC hDC)
{
	int i = 0;
	for (i = 0; i < 3; i++)
	{
		if (root->children[i] != NULL)
		{
			MoveToEx(hDC, root->children[i]->x1 + 10, root->children[i]->x2 + 33, NULL);
			LineTo(hDC, root->children[i]->x3 + 10, root->children[i]->x2 + 33);
			LineTo(hDC, root->children[i]->x3 + 10, root->children[i]->x4 + 33);
			LineTo(hDC, root->children[i]->x1 + 10, root->children[i]->x4 + 33);
			LineTo(hDC, root->children[i]->x1 + 10, root->children[i]->x2 + 33);


			afisare_arbore((root->children[i]), hDC);
		}

	}


}
/*/void main()
{
root = radacina("coord.txt");

afisare_arbore(root);
}*/