﻿#include <stdio.h>
#include <string.h>
#include <sstream>
#include <time.h>
#include <Windows.h>
#include <queue>
using namespace std;

void DistanceBFS(int num, int** G, int* visited, int N);
void printmatrix(int** source, int size);
void printdistance(int* visited, int N);

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	if (argc >= 1)
	{
		int** G;
		int* visited;
		int num;
		int N = 10;
		int flagtype = 0, flagorient = 0;

		for (int i = 1; i < argc; i++)
		{
			if ((strcmp(argv[i], "размер:") == 0))
			{
				std::stringstream convert(argv[i + 1]);
				if (!(convert >> N))
					N = 10;
			}
			if ((strcmp(argv[i], "взвешенность:") == 0))
				if ((strcmp(argv[i + 1], "да") == 0))
					flagtype = 1;
				else if ((strcmp(argv[i + 1], "нет") == 0))
					flagtype = 0;
			if ((strcmp(argv[i], "ориентированность:") == 0))
				if ((strcmp(argv[i + 1], "да") == 0))
					flagorient = 1;
				else if ((strcmp(argv[i + 1], "нет") == 0))
					flagorient = 0;
		}

		G = (int**)malloc(N * sizeof(int*));
		for (int i = 0; i < N; i++)
			G[i] = (int*)malloc(N * sizeof(int));

		visited = (int*)malloc(N * sizeof(int));
		for (int i = 0; i < N; i++)
			visited[i] = MAXINT;

		srand(time(NULL));

		//printf("\nN = %d, flagtype = %d, flagorient = %d", N, flagtype, flagorient);
		if (flagtype == 1 && flagorient == 1)
		{
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
					if (i == j)
						G[i][j] = 0;
					else
					{
						if (rand() % 10 < 4)
							G[i][j] = rand() % 9 + 1;
						else
							G[i][j] = 0;
					}
		}
		else if (flagtype == 1 && flagorient == 0)
		{

			for (int i = 0; i < N; i++)
				for (int j = i; j < N; j++)
					if (i == j)
						G[i][j] = 0;
					else
					{
						if (rand() % 10 < 4)
							G[i][j] = rand() % 9 + 1;
						else
							G[i][j] = 0;
						G[j][i] = G[i][j];
					}
		}
		else if (flagtype == 0 && flagorient == 1)
		{
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
					if (i == j)
						G[i][j] = 0;
					else
					{
						if (rand() % 10 < 3)
							G[i][j] = 1;
						else
							G[i][j] = 0;
					}
		}
		else if (flagtype == 0 && flagorient == 0)
		{
			for (int i = 0; i < N; i++)
				for (int j = i; j < N; j++)
					if (i == j)
						G[i][j] = 0;
					else
					{
						if (rand() % 10 < 3)
							G[i][j] = 1;
						else
							G[i][j] = 0;
						G[j][i] = G[i][j];
					}
		}

		printf("\nМатрица смежности графа G:\n");
		printmatrix(G, N);

		printf("\nПоиск расстояний на основе обхода в ширину ориентированного графа, представленного матрицей смежности");
		printf("\nВведите номер вершины, с которой следует начать: ");
		scanf_s("%d", &num);
		while (num > N)
		{
			printf("Такой вершины не существует! Нужно ввести другой номер!\nНомер вершины старта: ");
			scanf_s("%d", &num);
		}

		printf("\n\nВершина старта: %d", num);
		
		DistanceBFS(num - 1, G, visited, N);
		printdistance(visited, N);

		int check = 0;
		while (check != -1)
		{
			for (int i = 0; i < N; i++)
				visited[i] = MAXINT;

			printf("\n\nДля выхода из программы введите -1");
			printf("\nДля проверки другой вершины введите её номер: ");
			scanf_s("%d", &check);
			while (check > N)
			{
				printf("Такой вершины не существует! Нужно ввести другой номер!\nНомер вершины старта: ");
				scanf_s("%d", &check);
			}

			if (check == -1)
				break;
			else
			{
				printf("Вершина старта: %d", check);
				DistanceBFS(check - 1, G, visited, N);
				printdistance(visited, N);
			}
		}
	}
	return 0;
}

/*Поиск расстояний во взвешенном графе, представленном матрицей смежности, на основе обхода в ширину*/
void DistanceBFS(int num, int** G, int* visited, int N)
{
	queue <int> q;

	q.push(num);
	visited[num] = 0;
	while (!q.empty())
	{
		num = q.front();
		q.pop();
		for (int i = 0; i < N; i++)
			if (visited[i] > visited[num] + G[num][i] && G[num][i] > 0)
			{
				q.push(i);
				visited[i] = visited[num] + G[num][i];
			}
	}
}

/*Функция выводит на экран квадратную матрицу*/
void printmatrix(int** source, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			printf("%3d ", source[i][j]);
		printf("\n");
	}
}

void printdistance(int* visited, int N)
{
	for (int i = 0; i < N; i++)
	{
		if (visited[i] == MAXINT)
			printf("\nПути до вершины %d не существует", i + 1);
		else if (visited[i] != 0)
			printf("\nКратчайший путь до вершины %d: %d", i + 1, visited[i]);
	}
}