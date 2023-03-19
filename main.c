#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <unistd.h>
#include <time.h>

#define N 40
#define M 20

int i, j;

char border = '#';
char head = 'O';
char tail = 'o';
char empty = ' ';
char food = '$';
int borderValue = 0;
int headValue = 5;
int tailValue = 4;
int emptyValue = 1;
int foodValue = 2;

int field[M][N];
int x = N / 2;
int y = M / 2;
int score = 0;
int tailArr[M][N];

int flag = 0;
int gameOver = 0;

int foodX = -1;
int foodY = -1;
int isThereFood = 0;

void displayScene();
void initialization();
void displayPoint();
void resetScreen();
void input();
void logic();
void spawnFood();
void updateTail();

int main()
{
	srand(time(NULL));
	system("cls");
	initialization();
	while(!gameOver)
	{
		spawnFood();
		displayScene();
		logic();
		initialization();
		resetScreen();
	}
	system("cls");
	//printf("%d %d", foodX, foodY);
	return 0;
}

void displayPoint()
{
	if(field[i][j] == borderValue)
	{
		printf("%c", border);
	}else if(field[i][j] == emptyValue)
	{
		printf("%c", empty);
	}else if(field[i][j] == headValue)
	{
		printf("%c", head);
	}else if(field[i][j] == tailValue)
	{
		printf("%c", tail);
	}else if(field[i][j] == foodValue)
	{
		printf("%c", food);
	}
}

void displayScene()
{
	for(i = 0; i < M; ++i)
	{
		printf("  ");
		for(j = 0; j < N; j++)
		{
			displayPoint();
			input();
		}
		printf("\n");
	}
	printf("  score = %d\n", score);
	printf("\n Press Q to quit.\n W - up\n S - down\n A - left\n D - right");
}

void initialization()
{
	for(i = 0; i < M; ++i)
	{
		for(j = 0; j < N; ++j)
		{
			if(i == 0 || i == M - 1) // first and last row
			{
				field[i][j] = 0;
			}else // other rows
			{
				if(j == 0 || j == N - 1) // first and last column
				{
					field[i][j] = 0;
				}else
				{
					if(foodX != j || foodY != i)
					{
						field[i][j] = 1;
					}
				}
			}
		}
	}
	//for(i = 0; i < M; ++i)
	//{
	//	for(j = 0; j < N; ++j)
	//	{
	//		if(tailArr[i][j] == 1)
	//		{
	//			field[i][j] = tailValue;
	//		}
	//	}
	//}

	//field[foodY][foodX] = foodValue;
	field[y][x] = headValue;
}

void resetScreen()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

void input()
{
	if(kbhit())
	{
		switch(getch())
		{
		case 'a':
			flag = 1;
			break;
		case 's':
			flag = 2;
			break;
		case 'd':
			flag = 3;
			break;
		case 'w':
			flag = 4;
			break;
		case 'q':
			gameOver = 1;
			break;
		}
	}
}

void logic()
{
	double frame = 0.01;
	sleep(frame);
	switch(flag)
	{
	case 1:
		--x;
		break;
	case 2:
		++y;
		break;
	case 3:
		++x;
		break;
	case 4:
		--y;
		break;
	default:
		break;
	}

	//tailArr[y][x] = 1;

	if(x <= 0 || x >= N - 1 || y <= 0 || y >= M - 1)
	{
		gameOver = 1;
	}

	if(x == foodX && y == foodY)
	{
		isThereFood = 0;
		++score;
	}
}

void spawnFood()
{
	if(isThereFood == 0)
	{
		foodX = 1 + rand() % (N - 2);
		foodY = 1 + rand() % (M - 2);
		field[foodY][foodX] = foodValue;
	}
	isThereFood = 1;
}

void updateTail()
{
	
}