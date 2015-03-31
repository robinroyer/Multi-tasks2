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
	for(i= (uint64_t)2;i<((int)p)/2;i++)
	{

		if(((int)p)%i==0)
		{
			retour = 0;

		}
	}
	return retour;
}

void print_prime_factors(uint64_t n)
{
	uint64_t i;
	for(i=(uint64_t)2;is_prime(n)==0;i++)
	{
		if(((int)n)%i==0)
		{
			printf("%d\n",i);
			n=(uint64_t)((int)n/(int)i);
			i=(uint64_t)1;
		}
	}
	printf("%d\n",n );
}
int main(int argc, char *argv[])
{
	uint64_t p;
	int retour;
	scanf("%d",&p);
	retour = is_prime(p);
	print_prime_factors(p);
		//printf("%d\n",retour);
	return;
}