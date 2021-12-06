#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#define HEADER ("Лабораторная работа №7\nВыполнили: Шмелёв Д. и Пантюшов Е.\n\n")

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <queue>

using namespace std;

void BFSD(int** M, int n, int* dist, int x)
{
	queue <int> Q;
	Q.push(x);
	dist[x] = 0;
	while (!Q.empty())
	{
		x = Q.front();
		Q.pop();
		printf(" %d ", x);
		for (int i = 0; i < n; i++)
		{
			if (M[x][i] > 0 && dist[i] > dist[x] + M[x][i])
			{
				Q.push(i);
				dist[i] = dist[x] + M[x][i];
			}
		}
	}

}

int** createMatrix(char* argv[], int n)
{
	int** M = (int**)(malloc(n * sizeof(int*)));
	for (int i = 0; i < n; i++)
	{
		M[i] = (int*)(malloc(n * sizeof(int)));
		for (int j = 0; j < n; j++)
		{
			if (rand() % 100 < 40 || i == j)
			{
				M[i][j] = 0;
			}
			else
			{
				if (!strcmp(argv[1], "-0"))
				{
					M[i][j] = 1;
				}
				else
				{
					M[i][j] = rand() % n;
				}
			}
		}
	}
	if (!strcmp(argv[2], "-0"))
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (M[i][j] > 0)
				{
					M[j][i] = M[i][j];
				}
			}
		}
	}
	return M;
}

void printMatrix(int** M, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf(" %d ", M[i][j]);
		}
		printf("\n");
	}
}

void func(int** M, int n)
{
	printf("\nМатрица смежности:\n");
	printMatrix(M, n);
	int* dist = (int*)(malloc(n * sizeof(int)));
	int x;
	printf("\nВведите номер вершины: ");
	scanf("%d", &x);
	for (int i = 0; i < n; i++)
	{
		dist[i] = INT_MAX;
	}
	BFSD(M, n, dist, x);
	printf("\nРезультат работы алгоритма поиска расстояний: \n");
	for (int i = 0; i < n; i++)
	{
		if (dist[i] == INT_MAX)
		{
			dist[i] = 0;
		}
		printf("%d: %d\n", i, dist[i]);
	}
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "RUS");
	srand(time(NULL));
	printf(HEADER);
	if (argc > 1)
	{
		int n;
		sscanf(strtok(argv[3], "-"), "%d", &n);
		int** M = createMatrix(argv, n);
		func(M, n);
	}
	else
	{
		printf("Введите аргументы!\n");
	}
	system("PAUSE");
	return 0;
}
