#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

/*************************************************/
void Color(int couleurDuTexte,int couleurDeFond) //Une fonction de la bibliothèque <windows.h> qui affiche un texte colorié
{HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}
/*************************************************/
void calculer_degre(int tab[24],int matrice[24][24])
{int i,j,cpt;
for(i=0;i<24;i++)
{cpt=0;
for(j=0;j<24;j++)
{cpt+=matrice[i][j];
}
tab[i]=cpt;
}
}
/*************************************************/
//Fonction qui trie les sommets//TRI à bulles optimisé
void Tri(int tab[24],int tab_degre_trie[24])
{int i,j,trie,aux,stop=0;
i=0;
while(i<24&&!stop)
    {trie=1;
     for(j=i;j<24;j++)
      {if (tab[j]>tab[i])//trier les degrés
        {aux=tab[i];
         tab[i]=tab[j];
         tab[j]=aux;

         aux=tab_degre_trie[i];//trier les sommets
         tab_degre_trie[i]=tab_degre_trie[j];
         tab_degre_trie[j]=aux;
         trie=0;
        }
      }
if(trie)
stop=1;//on arrete le tri dès qu'il y ait une itération sans échange

i++;
    }
}
/*************************************************/

int main()
{int i,j,ind,test,z,max;
int color;
//int G[24][24];//On utilise cette déclaration de la matrice d'adjacence si on veut la saisir dans le programme principal
//int tab_sommets[24]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};//un tableaui qui contiendra après son tri les sommets du graphe triés dans l'ordre décroissant selon leurs degrés.
int tab_color[24];
//int degres[24];//un tableau qui contiendra dans chacune de ses cases le degré du sommet correspondant à l'indice de cette case.
int degre_dec[24]={7,2,12,13,14,19,20,21,1,5,16,0,3,6,8,9,10,11,15,17,4,18,22,23};//tableau qui range les sommets dans l'ordre décroissant des degrès
char ch[24][25]={"Trois Bassins","Saint Paul","Cilaos","Saint Leu","le Port","la Possession","Saint Denis","Salazie","Sainte Marie","Sainte Suzanne","Saint Andrie","Bras Panon","Saint Benoit","Entre Deux","le Tampon","la Plaine des Palmistes","Sainte Rose","les Avions","Etang Sale","Saint Louis","Saint Pierre","Saint Joseph","Saint Philippe","Petite Ile"};
/*int input[150]={3,1,2,3,4,0,2,4,5,7,0,1,3,7,12,13,19,3,0,2,17,2,1,5,4,1,4,6,7,3,5,7,
8,8,2,5,6,8,9,10,11,12,3,6,7,9,3,7,8,10,3,7,9,11,3,7,10,12,7,2,7,11,13,14,15,16,5,2,12,
14,19,20,5,12,13,15,20,21,3,12,14,16,4,12,15,21,22,4,12,15,21,22,3,3,18,19,2,17,19,5,2,
13,17,18,20,5,13,14,19,21,23,5,14,16,20,22,23,2,16,21,2,20,21};*///Ce sont les inputs du programmes:la première case contient le poids du sommet d'indice 0 suivi de son poids et ensuite ses successeurs, et ainsi de suite. Le compteur avance de la valeur du degre+1.

int G[24][24]={
{0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,0,1,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0},
{1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
{0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,1,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,1,0,0,1,1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0},
{0,0,1,0,0,0,0,1,0,0,0,1,0,1,1,1,1,0,0,0,0,0,0,0},
{0,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,1,1,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,0,0,0,1,1,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,1,0},
{0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0},
{0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,0,1,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,0,1,0,1},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,1,1},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0}};




system("color F0");
//Bloc de saisie de la matrice d'adjacence si on ne veut pas utiliser la matrice toute prete
/*for(i=0;i<24;i++)
    for(j=0;j<24;j++)
      G[i][j]=0;

for(i=0;i<24;i++)
  {//printf("\nDonnez le poids de la ville %s d'indice %i puis les indices de ses seccesseurs:",ch[i],i);
    scanf("\n%i",&n);
     for(j=0;j<n;j++)
     {scanf("\n%i ",&k);
      G[i][k]=1;
     }
  }

for(i=0;i<24;i++)
{printf("\n");
  for(j=0;j<24;j++)
    printf("%i ",G[i][j]);*/

//Ce bloc est utilisé si on veut que le tableau des degres soit rempli et trié par l'utilisateur
/*calculer_degre(degres,G);
Tri(degres,tab_sommets);
for(i=0;i<24;i++)
printf("%i ",tab_sommets[i]);//afficher les sommets triés dans l'ordre décroissant des sommets
printf("\n");
for(i=0;i<24;i++)
printf("%i ",degres[i]);//afficher les degrés dans l'ordre décroissant*/


for(i=0;i<24;i++)
    tab_color[i]=0;//initialiser le tableau des couleurs

color=1;
for(i=0;i<24;i++)
{ind=degre_dec[i];
if(tab_color[ind]==0)//si ce sommet n'est pas coloré
{tab_color[ind]=color;
for(j=i+1;j<24;j++)//on parcourt tous les sommets qui suivent
{if(tab_color[degre_dec[j]]==0)//si le sommet n'est pas coloré
{z=0;test=0;
while(!test&&z<24)
{if((tab_color[degre_dec[z]]==color)&&(G[degre_dec[j]][degre_dec[z]]==1))// on vérifie qu'il n'est adjacent à aucun sommet de le couleur courante
test=1;
else
z++;
}
 if(!test)
 tab_color[degre_dec[j]]=color;//si la condition est vérifiée, on lui affecte la meme couleur
}
}
color++;
}
}

Color(11,3);
printf("\n  °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°  ");
printf("\n  °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°  ");
printf("\n  °°                                                                                                °°  ");
printf("\n  °°                                    Coloration d'une Carte Graphique                            °°  ");
printf("\n  °°                                                                                                °°  ");
printf("\n  °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°  ");
printf("\n  °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°  ");

max=0;
for(i=0;i<24;i++)
    if(tab_color[i]>max)
    max=tab_color[i];

Color(4,15);
printf("\n\nPour colorier cette carte graphique, on a utilis%c %i couleurs diff%crents.\n\n",130,max,130);

Color(0,15);
printf("\n\n");
for(i=0;i<24;i++)
   {Color(0,tab_color[i]);
    printf("'%s'",ch[i]);
    Color(0,15);
    printf("  ");
    if(i%4==0)
    printf("\n\n");
    }
system("start carte_colorée.png");

printf("\n\n");
Color(0,15);

return 0;
}
