#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h>
#include <unistd.h>



#define MAX_FACTORS 64

static pthread_mutex_t mtxCpt;
static pthread_mutex_t affichage;



/**
 * _______________________________structure de données de memoization : arbre binaire___________________________________
 */
 
 
 typedef struct node
 {
    // la valeur du nombre à décomposer
 	uint64_t key;
    // la taleau des diviseurs premiers
 	uint64_t factors[MAX_FACTORS];
    // le nombre de facteurs dans le tableau
 	int nbFactor;
    // les pointeurs pour la structure
 	struct node *left;
 	struct node *right;
 } node ;

/**
 * Ajout d'un noeud correspondant à une valeur de key
 */
 void addNode(node **tree, uint64_t key, uint64_t dest[], int nbFact)
 {
 	node *tmpNode;
 	node *tmpTree = *tree;

 	node *elem = malloc(sizeof(node));
 	elem->key = key;
 	elem->left = NULL;
 	elem->right = NULL;
 	elem->nbFactor = nbFact;
 	int i;
 	for(i=0;i<nbFact;i++)
 	{
 		elem->factors[i] = dest[i];
 	}
    //printf("key = %ju\n", elem->key);
    //printf("trace : nouveau noeud créé \n");
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
    //printf("trace : nouveau noeud ajouté \n");
 }

/**
 * Recherche dans un arbre à partir d'un noeud, la valeur d'une clef
 */
 node* searchNode(node *tree, uint64_t key)
 {
	//printf("trace : nouvelle recherche dans l'arbre \n");
 	while(tree)
 	{
 		if(key == tree->key) return tree;

 		if(key > tree->key ) tree = tree->right;
 		else tree = tree->left;
 	}
 	return NULL;
 }
/**
 * Affiche l'arbre à partir d'un certain noeud
 */
 void printTree(node *tree)
 {
 	
 	if(!tree) return;
//	printf("trace : l'arbre est non vide \n");
 	if(tree->left)  printTree(tree->left);

 	printf("Cle = %ju\n", tree->key);
 	printf("nombre de facteurs = %d\n", tree->nbFactor);
 	int j;
 	for(j=0; j<tree->nbFactor; j++)
 	{
 		printf("%lu ",tree->factors[j]);
 	}
 	printf("\n");

 	if(tree->right) printTree(tree->right);
 	printf(" \n");
 }

 void printNode(node *tree)
 {
 	
 	if(!tree) return;
 	printf("%ju :", tree->key);
    //printf("nombre de facteurs = %d\n", tree->nbFactor);
 	int j;
 	for(j=0; j<tree->nbFactor; j++)
 	{
 		printf("%lu ",tree->factors[j]);
 	}
 	printf("\n");
 }

/**
 * supprime les descendant d'un noeuds
 */
 void clearTree(node **tree)
 {
 	node *tmpTree = *tree;

 	if(!tree) return;

 	if(tmpTree->left)  clearTree(&tmpTree->left);

 	if(tmpTree->right) clearTree(&tmpTree->right);

 	free(tmpTree);	

 	*tree = NULL;
 }





/** _________________________________________________FIN des fonction de structure de données
 * 
 *  -> ajout à l'arbre d'une valeur : addNode(node **tree, unsigned int key, uint64_t* dest)
 *  -> test de présence dans l'arbre: if(searchNode(Arbre, Key)) 
 *  -> supprimer un noeud : clearTree(node **tree)
 *  -> affichage récursif de l'arbre : printTree(node *tree)
 * /





/**
retourne 1 si p est premier
*/
int is_prime(uint64_t p)
{
	uint64_t i;
	for(i= 2;i<(p/2);i++)
	{
		if(!(p%i))
		{
			return 0;
		}
	}
	return 1;
}

/**
 * affiche les facteurs premiers d'un nombre n
 */
 void print_prime_factors(uint64_t n, node **Arbre)
 {
 	uint64_t factors[MAX_FACTORS];
 	int j,k;
 	
 	
 	node* cur=searchNode(*Arbre, n);
	// si le noeud n'existe pas, on le calcule le crée et on stocke le tableau des diviseurs de ce nombre n (key) sinon on l'affiche
 	if(cur!=NULL)
 	{	
 		printNode(cur);
 	}
 	else 
 	{
 		k=get_prime_factors(Arbre,n,factors);
 		addNode(Arbre, n, factors, k);
 		pthread_mutex_lock(&affichage);
 		printf("%ju: ",n);
 		for(j=0; j<k; j++)
 		{
 			printf("%lu ",factors[j]);
 		}
 		printf("\n");
 		pthread_mutex_unlock(&affichage);
 	}
 	
 }

/**
 * Renvoit un tableau contenant les facteurs premiers du nombre n
 * L'algorithme effectue des tests qui ne sont effectués que au premier tour ( divisible par 2, 3, 5)
 * puis les test lors des autres tours sont par itération du pas de 2, 4, 2, 4, 2
 */
 int get_prime_factors(node **tree,uint64_t n,uint64_t* dest)
 {
 	
 	uint64_t i;
 	uint64_t pas=2;

	int compteur=0; // le curseur sur le tableau
	for(i=7;i*i<= n;i+=(pas=6-pas))
	{	
		//les tests au premier tour
		if(i==7)
		{
			node* cur=searchNode(*tree, n);
			if(cur != NULL)
			{
				int z;
				for (z=0;z<cur->nbFactor-1;z++){
					dest[compteur]=cur->factors[i];
					compteur++;
				}
				n = cur->factors[compteur+1];
				
			}
			if((n)%2==0)
			{
				dest[compteur]=2;
				compteur++;
				n=n/2;
				i=5;
				pas=4;
			}
			else if((n)%3==0)
			{
				dest[compteur]=3;
				compteur++;
				n=n/3;
				i=5;
				pas=4;
			}
			else if((n)%5==0)
			{
				dest[compteur]=5;
				compteur++;
				n=n/5;
				i=5;
				pas=4;
			}

		}
		// les tests des autres tours
		if((n)%i==0)
		{
			dest[compteur]=i;
			compteur++;
			n=n/i;
			i=5;
			pas=4;
		}
	}
	dest[compteur]=n;
	compteur++;
	return compteur;
} 

/**
 * Permet de lancer une procedure qui créé des ptreads 
 * qui vont eux même lancer la décomposition en nombre entier. 
 */
 void *procedure_ptread(void *file)
 {
	//le premier noeud: la racine de l'arbre
 	node *Arbre = NULL;

 	uint64_t p;
 	FILE *fichier = (FILE*)file;
 	int finish = 0;
	//test de fin de lecture du fichier
 	while (finish==0) 
 	{
 		pthread_mutex_lock(&mtxCpt);
 		if(fscanf(fichier, "%lu",&p) != EOF)
 		{
 			pthread_mutex_unlock(&mtxCpt);
 			print_prime_factors(p, &Arbre);
 		}
 		else
 		{
 			pthread_mutex_unlock(&mtxCpt);
 			finish = 1;
 		}
 	}
 }

/**
 * Le main lit dans un fichier chaque ligne et affiche les facteurs premiers
 * du nombre lu sur chaque ligne en utilisant le multi-threading
 */
 int main(int argc, char *argv[])
 {


	// un nombre 64 bit pivot pour ranger la ligne lue du fichier
 	uint64_t p;
 	int result=0;
	//création et ouverture en lecture du fichier
 	FILE *fichier;
 	fichier = fopen ("number.txt", "r");

	//création mutex
 	pthread_t tid1,tid2,tid3,tid4,tid5,tid6;
	//initialisation mutex
 	pthread_mutex_init(&mtxCpt,NULL);
 	pthread_mutex_init(&affichage,NULL);
	//creation
 	if(pthread_create(&tid1, NULL, procedure_ptread, (void *) fichier)!=0)
 	{
 		printf("Erreur de création de thread\n");
 	}
 	if(pthread_create(&tid2, NULL, procedure_ptread, (void *) fichier)!=0)
 	{
 		printf("Erreur de création de thread\n");
 	}
 	if(pthread_create(&tid3, NULL, procedure_ptread, (void *) fichier)!=0)
 	{
 		printf("Erreur de création de thread\n");
 	}
 	if(pthread_create(&tid4, NULL, procedure_ptread, (void *) fichier)!=0)
 	{
 		printf("Erreur de création de thread\n");
 	}
 	if(pthread_create(&tid5, NULL, procedure_ptread, (void *) fichier)!=0)
 	{
 		printf("Erreur de création de thread\n");
 	}
 	if(pthread_create(&tid6, NULL, procedure_ptread, (void *) fichier)!=0)
 	{
 		printf("Erreur de création de thread\n");
 	}

	//attente
 	if(pthread_join(tid1,NULL)!=0)
 	{
 		printf("Erreur de joins de thread 1\n");
 	}
 	if(pthread_join(tid2,NULL)!=0)
 	{
 		printf("Erreur de joins de thread 2\n");
 	}
 	if(pthread_join(tid3,NULL)!=0)
 	{
 		printf("Erreur de joins de thread 3\n");
 	}
 	if(pthread_join(tid4,NULL)!=0)
 	{
 		printf("Erreur de joins de thread 4\n");
 	}
 	if(pthread_join(tid5,NULL)!=0)
 	{
 		printf("Erreur de joins de thread 3\n");
 	}
 	if(pthread_join(tid6,NULL)!=0)
 	{
 		printf("Erreur de joins de thread 4\n");
 	}


 	fclose(fichier);
 	pthread_mutex_destroy(&affichage);
 	pthread_mutex_destroy(&mtxCpt);
 	pthread_exit(NULL);

	//affichage de l'arbre binaire ___TEST

	//printf(" \n --- affichage de l'arbre --- \n");
	//printTree(Arbre); 
 	return 0;
 }
