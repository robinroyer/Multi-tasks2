#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_FACTORS 64


/**
retourne 1 si p est premier
*/
int is_prime(uint64_t p)
{

	uint64_t i;
	int retour= 1;
	for(i= 2;i<(p/2)&&retour==1;i++)
	{

		if((p)%i==0)
		{
			retour = 0;

		}
	}
	return retour;
}
void print_prime_factors(uint64_t n)
{
	uint64_t factors[MAX_FACTORS];
	int j,k;
	k=get_prime_factors(n,factors);
	printf("%lu: ",n);
	for(j=0; j<k; j++)
	{
		printf("%lu ",factors[j]);
	}
	printf("\n");
}


int get_prime_factors(uint64_t n,uint64_t* dest)
{
	
	uint64_t i;
	uint64_t pas=4;
	printf("%lu: ",n);
	int compteur=0; // le curseur sur le tableau
	for(i=7;is_prime(n)==0;i+=(pas=6-pas))
	{
		if(i==7)
		{
			if((n)%2==0)
			{
				dest[compteur]=2;
				compteur++;
				n=n/2;
				i=5;
				pas=4;
			}
			if((n)%3==0)
			{
				dest[compteur]=3;
				compteur++;
				n=n/3;
				i=5;
				pas=4;
			}
			if((n)%5==0)
			{
				dest[compteur]=5;
				compteur++;
				n=n/5;
				i=5;
				pas=4;
			}

		}
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

int main(int argc, char *argv[])
{

	
	uint64_t p;
	int result=0;
	FILE *fichier;
	fichier = fopen ("number.txt", "r");
	int finish = 0;
	while (finish==0) 
	{
		if(fscanf(fichier, "%ju",&p) != EOF)
		{
			print_prime_factors(p);
		}
		else
		{
			finish = 1;
		}
	}
	return 0;
}
