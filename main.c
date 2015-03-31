#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

/**
retourne 1 si p est premier
*/
int is_prime(uint64_t p)
{

	uint64_t i;
	int retour= 1;
	for(i= (uint64_t)2;i<=((int)p)/2;i++)
	{

		if(((int)p)%i==0)
		{
			retour = 0;

		}
	}
	return retour;
}
int is_prime_last(uint64_t p)
{

	uint64_t i;
	int retour= 1;
	for(i= (uint64_t)2;i<((int)p)/2;i++)
	{

		if(((int)p)%i==0)
		{
			retour = i;

		}
	}
	return retour;
}
void print_prime_factors(uint64_t n)
{
	uint64_t i;

	for(i= (uint64_t)2;i<=((int)n)/2;i++)
	{


		
		if((((int)n)%i==0)&&(is_prime(i)==0))
		{
			printf("je suis dans le if");
			printf("%d\n",i);		

		}
			
		}
			
		
	}
	int main(int argc, char *argv[])
	{
		uint64_t p;
		int retour;
		scanf("%d",&p);
		retour = is_prime(p);
		printf("%d\n",retour);
		print_prime_factors(p);
		return;
	}
