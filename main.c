#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h>



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
