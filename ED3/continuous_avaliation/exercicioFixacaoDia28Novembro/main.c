#include <stdio.h>

#define NUMBER 20

typedef struct Gmat
{
	int matrix[NUMBER][NUMBER];
	int vertNumber = NUMBER;
} Gmat;

int main()
{

	Gmat G;
	int stop = 0;
	for (int j = 0; j <= NUMBER; j++)
	{
		for (int i = j + 1; i < NUMBER; i++)
		{
			if (G.matrix[i][j] != G.matrix[i][i])
			{
				printf("não é simetrica\n");
				stop = 1;
				break;
			}
			if (stop)
				break;
		}
	}
}