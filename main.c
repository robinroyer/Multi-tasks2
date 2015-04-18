#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h>



//TODO: adapter pointeur reférence etc..

/**
 * _______________________________structure de données de memoization : arbre binaire___________________________________
 */
 
 
 typedef struct node
{
    unsigned int key;
    struct node *left;
    struct node *right;
} node ;

void addNode(node **tree, unsigned int key)
{
    node *tmpNode;
    node *tmpTree = *tree;

    node *elem = malloc(sizeof(node));
    elem->key = key;
    elem->left = NULL;
    elem->right = NULL;

    if(tmpTree)
    do
    {
        tmpNode = tmpTree;
        if(key > tmpTree->key )
        {
            tmpTree = tmpTree->right;
            if(!tmpTree) tmpNode->right = elem;
        }
        else
        {
            tmpTree = tmpTree->left;
            if(!tmpTree) tmpNode->left = elem;
        }
    }
    while(tmpTree);
    else  *tree = elem;
}

int searchNode(node *tree, unsigned int key)
{
    while(tree)
    {
        if(key == tree->key) return 1;

        if(key > tree->key ) tree = tree->right;
        else tree = tree->left;
    }
    return 0;
}

void printTree(node *tree)
{
    if(!tree) return;

    if(tree->left)  printTree(tree->left);

    printf("Cle = %d\n", tree->key);

    if(tree->right) printTree(tree->right);
}

void clearTree(node **tree)
{
    node *tmpTree = *tree;

    if(!tree) return;

    if(tmpTree->left)  clearTree(&tmpTree->left);

    if(tmpTree->right) clearTree(&tmpTree->right);

    free(tmpTree);	

    *tree = NULL;
}





/** _________________________________________________FIN des fonction de structure de donnée
 * 
 *  -> ajout à l'arbre d'une valeur : addNode(&Arbre, 30);
 *  ->   test de présence dans l'arbre: if(searchNode(Arbre, Key)) 
 * 
 * /














/**
retourne 1 si p est premier
*/
int is_prime(uint64_t p)
{

	uint64_t i;
	int retour= 1;
	for(i= (uint64_t)2;i<((int)p)/2;i++)
	{

		if(((int)p)%i==0)
		{
			retour = 0;

		}
	}
	return retour;
}

void *print_prime_factors(void *p)
{
	uint64_t n = (uint64_t)p;
	printf("%d:",n);
	uint64_t i;
	for(i=(uint64_t)2;is_prime(n)==0;i++)
	{
		if(((int)n)%i==0)
		{
			printf(" %d",i);
			n=(uint64_t)((int)n/(int)i);
			i=(uint64_t)1;
		}
	}
	printf(" %d\n",n );
}


/* void *print_prime_factors(void *p)
{
	uint64_t n = (uint64_t)p;
	printf(" %d :",n);
	uint64_t i;
	int pas=4;
	

	for(i=(uint64_t)7;is_prime(n)==0;i+=(pas=6-pas))
	{


		if(i==7)
		{

			if(((int)n)%2==0)
			{
				printf(" 2 ");
				n=(uint64_t)((int)n/2);
				i=(uint64_t)5;
				pas=4;
			}
			if(((int)n)%3==0)
			{
				printf("3  ");
				n=(uint64_t)((int)n/3);
				i=(uint64_t)5;
				pas=4;
			}
			if(((int)n)%5==0)
			{
				printf("5");
				n=(uint64_t)((int)n/5);
				i=(uint64_t)5;
				pas=4;
			}
			
		}

		if(((int)n)%i==0)
		{
			printf(" %d",i);
			n=(uint64_t)((int)n/(int)i);
			i=(uint64_t)5;
			pas=4;
		}
	}
	printf(" %d\n",n );
}*/




int main(int argc, char *argv[])
{
	//le premier noeud: la racine de l'arbre
	node *Arbre = NULL;
	
	uint64_t p;
	int retour;
	pthread_t tid1,tid2;
	int crdu;

	FILE *fichier = NULL;

	fichier = fopen ("number.txt", "r");
	while (fscanf(fichier, "%d",&p) != EOF) 
	{
		printf("création de thread 1\n");
		crdu = pthread_create( &tid1, NULL, print_prime_factors, (void *) p);
		if(crdu!=0)
		{
			printf("Erreur de création de thread\n");
		}
		//print_prime_factors(p);
		if(fscanf(fichier, "%d",&p) != EOF)
		{
			printf("création de thread 2\n");
			crdu = pthread_create( &tid2, NULL, print_prime_factors, (void *) p);
		}
		if(crdu!=0)
		{
			printf("Erreur de création de thread\n");
		}

		crdu = pthread_join(tid1,NULL);
		if(crdu!=0)
		{
			printf("Erreur de joins de thread 1\n");
		}
		crdu = pthread_join(tid2,NULL);
		if(crdu!=0)
		{
			printf("Erreur de joins de thread 2\n");
		}
		//print_prime_factors((void *) p);

	}
	fclose(fichier);
	pthread_exit(NULL);
	return 0;
}
