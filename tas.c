#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h> 
#include "conio.h"
#include "conio.c"

////////////////////////////////////// ETAPE 1 : création d'une structure //////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct Tas 
{
    int size;
    int *tab; 
}Tas; 

int* create_entrance(int real_size)                // creation d'un tableau d'entrée aléatoire
{
    int* tab_entrance;
    int i;

    tab_entrance = malloc(sizeof(int) * real_size);

    srand(time(NULL));

    for(i = 0; i < real_size; i++)
    {
        tab_entrance[i] = rand() % 101;             // génération entre 0 et 100 
    }
    return tab_entrance;
}

Tas* create_tas(int real_size)                     // création d'un tas binaire
{
    Tas* new_tas = malloc(sizeof(Tas));
    new_tas->size = 0;
    new_tas->tab = malloc(sizeof(int) * real_size);
    return new_tas;
}

////////////////////////////////////// ETAPE 2 : Renvoyer le plus grand élément //////////////////////////////////////////////////////////////////////////////////////////////////////////

int max_tas(Tas* tas)                             // retourne la racine d'un tas binaire
{
    return tas->tab[0]; 
}

void print_tas(Tas* tas)                         // fonction d'affichage du tableau d'un tas binaire
{
    int i;
    printf("Taille = %d : ", tas->size);
    for(i = 0; i < tas->size; i++ )
    {
        printf("- %d ", tas->tab[i]);
    }
    printf("\n");

}

void print_tab(int* tab, int size)               // fonction d'affichage d'un tableau
{
    int i;
    for(i = 0; i < size; i++)
    {
        printf("- %d ", tab[i]);
    }
    printf("\n");
}

void print_invert_tab(int* tab, int size)        // fonction d'affichage inversé d'un tableau
{
    int i;
    for(i = size - 1; i > -1; i--)
    {
        printf("- %d ", tab[i]);
    }
    printf("\n\n");    
}

////////////////////////////////////// ETAPE 3 : Ajouter un élément //////////////////////////////////////////////////////////////////////////////////////////////////////////

int parent(int n)                               // retourne l'index d'un parent
{
    if(n % 2 == 0) return (n - 2) / 2;     
    
    else return (n - 1) / 2;      
}

void push_up(int n, int* tab)
{
    int temp;                                     // variable temporaire permettant l'echange
    int p_n = parent(n);
    while(n > 0 && tab[p_n] <= tab[n])         // tas min on change la deuxième condition condition en >  // tant que le parent est plus petit que l'élément
    {                                            
        temp = tab[n];
        tab[n] = tab[p_n];                      // on echange l'enfant et le parent à l'aide d'une varibale temporaire
        tab[p_n] = temp;                        // en d'autres termes, on fait remonter 
        
        n = p_n;
        p_n = parent(n);
        
    }   

}

void add_in_tas(Tas* tas, int e)  
{

    int n = tas -> size;                             
    tas->tab[n] = e;                             // on met l'élément à ajouter à la fin

    push_up(n, tas->tab);                             
    tas->size += 1;                              // on à ajouter un élément dans le tableau, on incrémente donc sa taille
}


////////////////////////////////////// ETAPE 4 : supprimer la racine //////////////////////////////////////////////////////////////////////////////////////////////////////////

int max_descendants(int n, int* tab)             // retourne l'index de l'enfant le plus grand 
{
    if (tab[(2 * n) + 1] > tab[(2 * n) + 2])
    {
        return (2 * n) + 1;    
    }
    else 
    {
        return (2 * n) + 2;
    }
}


void push_down(int n, int size, int* tab)
{
    int temp;
    int e_n = max_descendants(n, tab);            // on créer une variable qui prend l'index de l'enfant le plus grand

    while(2 * n + 2 < size && tab[n] < tab[e_n])   //tas min on change la deuxième condition en >=  // tant qu'un enfant existe et que l'élément actuel est inferieur à son enfant      
    {
        temp = tab[n];                           
        tab[n] = tab[e_n];                       // on fait descendre l'élément dans le tableau
        tab[e_n] = temp;

        n = e_n;                                 // on passe au suivant
        e_n = max_descendants(n, tab);
    }   

}


void delete_in_tas(Tas* tas)                  
{
    //if (tas->size == 0) return; 

    tas->tab[0] = tas->tab[tas->size - 1];              // on met le dernier élément à la place de la racine

    int n = 0; 
    
    push_down(n, tas->size, tas->tab);                  // on fait descendre l'élément qui est à la racine jusqu'à sa place
    tas->size -= 1;                                   // on réduit la taille du tableau
    
}

////////////////////////////////////// ETAPE 5 : tri par tas //////////////////////////////////////////////////////////////////////////////////////////////////////////

int* sorted_tab(Tas* tas, int* tab, int real_size)           // fonction qui permet de trier un tableau en passant par un tas binaire
{
    int i;

    textcolor(BLUE);
    for(i = 0; i < real_size; i++)                          // on ajoute toutes les valeurs du tableau d'entré une par une dans le tas        
    {
        if (i == real_size - 1) textcolor(WHITE);
        add_in_tas(tas, tab[i]);                            // a chaque ajout on respecte les caracteristique d'un tas
        print_tas(tas);
    }                                              

    int* output_tab = malloc(sizeof(int) * real_size);      // on creer le tableau de sortie qui sera trié

    textcolor(RED);
    for(i = 0; i < real_size; i++)                 
    {
        output_tab[i] = max_tas(tas);                       // on retient la racine dans le tableau de sortie
        if (i != 0) print_tas(tas);                       
        delete_in_tas(tas);                                 // on supprime la racine 
    }   

    return output_tab;
}

void sorted_tab_tas()                                       // meme fonctionnement que la précèdente mais avec la création du tas et tout les affichage
{
    float time;
    clock_t t1, t2;

    Tas* new_tas;
    int* input_tab;
    int real_size;
    
    textcolor(WHITE);
    printf("\nQuelle est la taille du tableau souhaite ?\n");
    scanf("%d", &real_size);

    printf("\nLe tableau inital est: ");
    input_tab = create_entrance(real_size);                        // creation du tableau d'entrée
    print_tab(input_tab, real_size);
    printf("\n");

    new_tas = create_tas(real_size);                               // creation du tas

    t1 = clock();
    int* output_tab = sorted_tab(new_tas, input_tab, real_size);   // tableau de sortie qui sera trié à la fin
    t2 = clock();
    textcolor(WHITE);
    printf("\nLe tableau inital est donc trie: ");
    print_invert_tab(output_tab, real_size);                       // permet un affichage dans l'ordre croissant

    time = (float)(t2 - t1) / CLOCKS_PER_SEC;                       // calcul le temps d'execution
    textcolor(YELLOW);
    printf("Le programme de tri par tas a mis %f secondes ! \n\n", time);
    textcolor(WHITE);

    free(input_tab);
    free(output_tab);
    free(new_tas->tab);
    free(new_tas);
}

////////////////////////////////////// ETAPE 6 : tri en place //////////////////////////////////////////////////////////////////////////////////////////////////////////

void sort_in_place()
{
    textcolor(YELLOW);
    printf("Tri en place : \n");

    int i;
    int size;

    textcolor(WHITE);
    printf("\nQuelle est la taille du tableau ?\n");
    scanf("%d", &size);

    int* tab = create_entrance(size);
    printf("\nLe tableau est le suivant : ");
    print_tab(tab, size);
    printf("\n");

    textcolor(BLUE);
    for(i = 0; i < size ; i++)
    {
        push_up(i, tab);
        printf("Etape %d de l'entassement : ", i);
        print_tab(tab, size);                         
    }

    textcolor(WHITE);
    printf("\nLe tableau initial est un tas max :");
    print_tab(tab, size);
    printf("\n");

    textcolor(RED);
    for(i = 0; i < size - 1 ; i++)
    {
        push_down(i, size, tab);
        printf("Etape %d du tri croissant : ", i);
        print_tab(tab, size); 
    } 

    free(tab);
    textcolor(WHITE);
}


int main()
{
    //float time;
    //clock_t t1, t2;

    //t1 = clock();

    sorted_tab_tas();  
    sort_in_place();             

    //t2 = clock();
    //time = (float)(t2 - t1) / CLOCKS_PER_SEC;
    //textcolor(YELLOW);
    //printf("Le programme a mit %f secondes, en comptant le temps d'affichage et d'interaction ! \n\n", time);
    textcolor(WHITE);
    printf("\nMerci et aurevoir !\n\n");
    
    return 0;
}

//flexbox