#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <unistd.h>
#include <time.h>

#define WIDTH 40
#define HEIGHT 20

#define EMPTY 0
#define BORDER 1
#define TAIL 2
#define FOOD 3

typedef struct node
{
    int x;
    int y;
} node;

int gameOver = 0;
int isThereFood = 0;
int score = 0;

node food;
void displayScene(int field[HEIGHT][WIDTH]);
void initialazingGrid(int field[HEIGHT][WIDTH]);
void resetScreen();
void inputFlag(int field[HEIGHT][WIDTH], node* tail, const int usedSize, const int flag);
void inputKyeabord();
void snakeGrid(int field[HEIGHT][WIDTH], node* tail, const int usedSize);
void spawnFood(int field[HEIGHT][WIDTH]);
void updateSnake(node* snake, int* usedSize, int* size);

int main()
{
    srand(time(NULL));

    int grid[HEIGHT][WIDTH];
    initialazingGrid(grid);

    // INITIALIZING SNAKE
    node head = {WIDTH / 2, HEIGHT / 2};
    int size = 18*18;
    int usedSize = 1;
    //node* snake = (node*)malloc(size * sizeof(node));
    node snake[size];
    snake[0] = head;
    // ---------- //

    int flag;
    //int gameOver = 0;
    //int isThereFood = 0;
    system("cls");
    while(gameOver == 0)
    {   
        displayScene(grid);
        resetScreen();
        inputKyeabord(&flag);
        //snakeGrid(grid, snake, usedSize);
        inputFlag(grid, snake, usedSize, flag);
        updateSnake(snake, &usedSize, &size);
        //printf("%d", flag);
    }
    system("cls");
    printf("================Game Over!================\n");
    //int i;
    //for(i = 0; i < usedSize; i++)
    //{
    //    printf("[%d %d] ", snake[i].x, snake[i].y);
    //}
    free(snake);
    return 0;
}

void displayScene(int field[HEIGHT][WIDTH])
{
    int i, j;
    for(i = 0; i < HEIGHT; i++)
    {
        for(j = 0; j < WIDTH; j++)
        {
            switch(field[i][j])
            {
                case EMPTY:
                    printf(" ");
                    break;
                case BORDER:
                    printf("#");
                    break; 
                case TAIL:
                    printf("O");
                    break;
                case FOOD:
                    printf("&");
                    break; 
                default:
                    printf("Wrong value in grid\n");
                    break;             
            } 
        }
        printf("\n");
    }

    printf("  score = %d\n", score + 1);
	printf(" W - up\n S - down\n A - left\n D - right");
}

void initialazingGrid(int field[HEIGHT][WIDTH])
{   

    int i, j;
    for(i = 0; i < WIDTH; i++)
    {
        field[0][i] = BORDER;
    }

    for(i = 1; i < HEIGHT - 1; i++)
    {
        for(j = 0; j < WIDTH; j++)
        {
            if(j == 0 || j == WIDTH - 1)
            {
                field[i][j] = BORDER;
            }else
            {
                field[i][j] = EMPTY;
            }
        }
    }
    
    for(i = 0; i < WIDTH; i++)
    {
        field[HEIGHT - 1][i] = BORDER;
    }
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

void inputFlag(int field[HEIGHT][WIDTH], node* tail, const int usedSize, const int flag)
{
	double frame = 0.01;
	sleep(frame);

    node head = tail[0];
	switch(flag)
	{
	    case 1:
	    	--head.x;
	    	break;
	    case 2:
	    	++head.y;
	    	break;
	    case 3:
	    	++head.x;
	    	break;
	    case 4:
	    	--head.y;
	    	break;
	    default:
	    	break;
	}
	if(head.x <= 0 || head.x >= WIDTH - 1 || head.y <= 0 || head.y >= HEIGHT - 1)
	{
		gameOver = 1;
	}
    tail[0] = head;

    initialazingGrid(field);
    snakeGrid(field, tail, usedSize);
    spawnFood(field);
}

void inputKyeabord(int* flag)
{
	if(kbhit())
	{
		switch(getch())
		{
		    case 'a':
		    	*flag = 1;
		    	break;
		    case 's':
		    	*flag = 2;
		    	break;
		    case 'd':
		    	*flag = 3;
		    	break;
		    case 'w':
		    	*flag = 4;
		    	break;
            default:
                break;
		}
	}
}

void snakeGrid(int field[HEIGHT][WIDTH], node* tail, const int usedSize)
{
    int i;
    int x, y;
    for(i = 0; i < usedSize; i++)
    {  
        x = tail[i].x;
        y = tail[i].y;
        field[y][x] = TAIL;
    }
}

void spawnFood(int field[HEIGHT][WIDTH])
{
    int foodX, foodY;
    if(isThereFood == 0)
    {   
        food.x = 1 + rand() % (WIDTH - 2);
        food.y = 1 + rand() % (HEIGHT - 2);
        isThereFood = 1;
    }
    field[food.y][food.x] = FOOD;
}

void updateSnake(node* snake, int* usedSize, int* size) // treba da popravim ovoa
{
    int i, j;
    //node* oldTail = (node*)malloc((*usedSize) * sizeof(node));
    //node oldTail[(*usedSize)];
    //for(i = 0; i < (*usedSize); i++)
    //{
    //    oldTail[i] = snake[i];
    //}



    //if(snake[0].x == food.x && snake[0].y == food.y)
    //{
    //    score++;
    //    isThereFood = 0;
    //    if(*usedSize >= *size)
    //    {
    //        node* temp = (node*)realloc(snake, ((*size) + 3) * sizeof(node));
    //        if(temp == NULL)
    //        {
    //            gameOver = 1;
    //            //system("cls");
    //            //printf("Something went wrong");
    //            //exit(1);
    //        }else
    //        {
    //            snake = temp;
    //            (*size) += 3;
    //            //snake[*usedSize].x = food.x;
    //            //snake[*usedSize].y = food.y;
    //            //gameOver = 1;
    //            //printf("%p %p\n", oldTail, snake);
    //            printf("%d %d\n", *usedSize, *size);
//
    //        }
    //    }
    //    (*usedSize)++;
    //}
    //int i;

    //for(i = 0; i < *usedSize - 1; i++)
    //{
    //    printf("[%d %d] ", oldTail[i].x, oldTail[i].y);
    //}
//
    //    
    //for(i = 1; i < *usedSize; i++)
    //{
    //    snake[i] = oldTail[i - 1];
    //}
//
//
    //printf("\n");
    //for(i = 0; i < *usedSize; i++)
    //{
    //    printf("[%d %d] ", snake[i].x, snake[i].y);
    //}

    node oldTail[(*usedSize)];
    for(i = 0; i < (*usedSize); i++)
    {
        oldTail[i] = snake[i];
    }

    if(snake[0].x == food.x && snake[0].y == food.y)
    {
        score++;
        isThereFood = 0;
        (*usedSize)++;
    }

    for(i = 1; i < *usedSize; i++)
    {
        snake[i] = oldTail[i - 1];
    }
}
