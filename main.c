#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "time.h"
#include "string.h"
#include "math.h"

int main()
{
	int iteretion = 100;
	int popSize = 20;
	float Pc = 0.75;
	float Pm = 0.05;
	int kromozonLength = 33;
	int minX1 = -3;
	float maxX1 = 12.1;
	float minX2 = -4.1;
	float maxX2 = 5.8;

    int a,b,c,d,e,f,g,h,k,i,j,l,m,n,o,p,r,s,v,t;
	int populasyon[kromozonLength];
	int kromozonArray[popSize][kromozonLength];

	float decimalValue[popSize];
	float decimalValue_x2[popSize];

	float costFunction[popSize];
	float totalCostFunction=0;

	float naturalSelectionProbability[popSize];
	float cumulativeProba[popSize];
	float randomNumberRulet[popSize];
	int newKromozonArray[popSize][kromozonLength];
	int newKro=0;
	float randomCrossNumber[popSize];
	int crossList[popSize];
	int crosCount=0;
	srand((unsigned)time(NULL));

	// Try to create the log file
	/*
	  FILE* fp = fopen("gaExample.txt", "w");
	  if(fp == NULL)
	  {
	    printf("File create problem!\n");
	    return -1;
	  }*/

	// Rastgele kromozonların üretilmesi		
	for ( a = 0; a < popSize; a++)
	{
		for ( b = 0; b < kromozonLength; b++)
		{
			int r = rand() % 2;
			//populasyon[i]= r;
			kromozonArray[a][b]=r;
			//fprintf(fp, "%d",kromozonArray[a][b]);
			printf("%d",kromozonArray[a][b]);
		}
		printf("\n");
		//fprintf(fp,"\n");
	}

	// Bütün kromozomların binary to dec dönüşümü
	for ( c = 0; c < popSize; ++c)
	{
		int value=0;
		for ( d = 0; d < 18; ++d)
		{
			value += kromozonArray[c][d] * pow(2,d);
		}
		decimalValue[c] = minX1 + ((value) * ((maxX1-(minX1))/(pow(2,18)-1)));
		value=0;
	}

	for ( e = 0; e < popSize; ++e)
	{
		int value=0;
		for ( f = 0; f < 15; ++f)
		{
			value += kromozonArray[e][f] * pow(2,f);
		}
		decimalValue_x2[e] = minX2 + ((value) * ((maxX2-(minX2))/(pow(2,15)-1)));
		value=0;
	}

	for (int i = 0; i < popSize; ++i)
	{
		printf("%f\n", decimalValue[i]);
	}

	printf("\n");

	for (int i = 0; i < popSize; ++i)
	{
		printf("%f\n", decimalValue_x2[i]);
	}

	//Amaç fonksiyonlarının hesaplanması
	for ( g = 0; g < popSize; ++g)
	{
		costFunction[g] = 21.5 + (decimalValue[g]*sin(4*3.14*decimalValue[g])) + (decimalValue_x2[g]*sin(20*3.14*decimalValue_x2[g]));
	}

	printf("\n");

	for ( h = 0; h < popSize; ++h)
	{
		printf("%f\n", costFunction[h]);
		totalCostFunction += costFunction[h];
	}
	printf("%f\n",totalCostFunction);
	printf("\n");

	//Doğal seçim ihtimalinin hesaplanması
	for ( i = 0; i < popSize; ++i)
	{
		naturalSelectionProbability[i] = costFunction[i] / totalCostFunction;
		printf("%f\n", naturalSelectionProbability[i]);
	}
	printf("\n");

	//Kümülatif ihtimallerin hesaplanması

	for ( j = 0; j < popSize; ++j)
	{
		if (j==0)
		{
			cumulativeProba[j] = naturalSelectionProbability[j];
		}
		else
		{
			for ( k = 0; k <= j; ++k)
			{
				cumulativeProba[j] += naturalSelectionProbability[k];
			}
		}
		printf("%f\n",cumulativeProba[j]);
	}
	printf("\n");

	// Seleksiyon için rulet tekerleğinin 20 kez döndürülmesi
	for ( l = 0; l < popSize; ++l)
	{
		randomNumberRulet[l] = (float)rand()/RAND_MAX;
		printf("%f\n", randomNumberRulet[l]);
	}


	for ( m = 0; m < popSize; ++m)
	{
		for ( n = 0; n < popSize; ++n)
		{
			if (randomNumberRulet[m] <= cumulativeProba[n])
			{
				for ( o = 0; o < kromozonLength; ++o)
				{
					newKromozonArray[newKro][o] = kromozonArray[n][o];
				}
				break;
			}
		}
		newKro++;
	}
	newKro = 0;
	printf("\n");

	for ( p = 0; p < popSize; ++p)
	{
		for (r = 0; r < kromozonLength; ++r)
		{
			printf("%d", newKromozonArray[p][r]);
		}
		printf("\n");
	}

	//Tek nokta çaprazlama operatörünün uygulanması
	for ( s = 0; s < popSize; s++)
	{
		randomCrossNumber[s] = (float)rand()/RAND_MAX;
		printf("%f\n", randomCrossNumber[s]);
	}
/*
	for (t = 0; t < popSize; ++t)
	{
		if (randomCrossNumber[t] < Pc)
		{
			crossList[crosCount] = t;
			crosCount++;
		}
	}*/
/*
	if (crosCount %2 == 0)
	{

	}
	else
	{

	}

	for (v = 0; v < crosCount; ++v)
	{
		printf("%d\n",crossList[v]);
	}

	crosCount = 0;*/

	//fclose(fp);
	return 0;
}