#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define NO_OF_TRIALS 100000
float actual_prob(int n)
{
	float p=1;
	int i;
	for(i=1;i<n;i++)
	{
		p*=(365.0-i)/365.0;
	}
	return (1-p)*100;
}

//1 lakh trial runs . To improve accuracy increase to 10 lakhs or 1 crore
int main(void)
{
	int hash[365],n,index;
	int j;
	unsigned long long int cnt=0,i=0;
	printf("\nEnter number of people: ");
	scanf("%d",&n);
	srand(time(NULL));
	for(i=0;i<NO_OF_TRIALS;i++)
	{
		for(j=0;j<365;j++)
		hash[j]=-1;
		for(j=0;j<n;j++)
		{
			index=rand()%365;
			if(hash[index]==1)
			{
				cnt++;
				break;
			}
			hash[index]=1;
		}
	}
	printf("\n\nProbability(%%)= %lf%%\n\n",((cnt*1.0)/NO_OF_TRIALS)*100.0);
	printf("\n\nActual probality(%%)=%lf%%\n\n",actual_prob(n));
	return 0;
}
