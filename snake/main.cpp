#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <imapi.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#define MAX_SNAKE_LENGTH 1000
#define SIZE 20
IMAGE SNAKE_HEAD_UP, SNAKE_HEAD_DOWN, SNAKE_HEAD_LEFT, SNAKE_HEAD_RIGHT, SNAKE_BODY, SNAKE_FOOD;
struct COOR
{
	int x, y;
};
enum CH
{
	up=72,down=80,left=75,right=77
};
struct SNAKE
{
	int n;
	COOR scr[MAX_SNAKE_LENGTH];
	CH ch;
}snake;
struct FOOD
{
	COOR fcr;
	int flag;
}food;
void initGame()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTitle(L"Soviet Snake");
    initgraph(640, 480);
	setbkcolor(WHITE);
	cleardevice();
	//loadimage
	loadimage(&SNAKE_HEAD_UP, L"SNAKE_HEAD_UP.jpg", SIZE, SIZE);
	loadimage(&SNAKE_HEAD_DOWN, L"SNAKE_HEAD_DOWN.jpg", SIZE, SIZE);
	loadimage(&SNAKE_HEAD_LEFT, L"SNAKE_HEAD_LEFT.jpg", SIZE, SIZE);
	loadimage(&SNAKE_HEAD_RIGHT, L"SNAKE_HEAD_RIGHT.jpg", SIZE, SIZE);
	loadimage(&SNAKE_BODY, L"SNAKE_BODY.jpg", SIZE, SIZE);
	loadimage(&SNAKE_FOOD, L"SNAKE_FOOD.jpg", SIZE, SIZE);
	snake.n = 1;
	snake.scr[0].x = 0;
	snake.scr[0].y = 0;
	snake.ch = right;
	food.flag = 0;
}
void SnakePaint()
{
	switch (snake.ch)
	{
		case up:
			putimage(snake.scr[0].x, snake.scr[0].y, &SNAKE_HEAD_UP);
			break;
		case down:
			putimage(snake.scr[0].x, snake.scr[0].y, &SNAKE_HEAD_DOWN);
			break;
		case left:
			putimage(snake.scr[0].x, snake.scr[0].y, &SNAKE_HEAD_LEFT);
			break;
		case right:
			putimage(snake.scr[0].x, snake.scr[0].y, &SNAKE_HEAD_RIGHT);
			break;
	}
	for (int i = snake.n - 1; i > 0; i--)
	{
		putimage(snake.scr[i].x, snake.scr[i].y, &SNAKE_BODY);
	}
}
void SnakeMove()
{
    for (int i = snake.n - 1; i > 0; i--)
    {
        snake.scr[i].x = snake.scr[i - 1].x;
        snake.scr[i].y = snake.scr[i - 1].y;
    }
    switch (snake.ch)
    {
    case up:
        snake.scr[0].y -= SIZE;
        break;
    case down:
        snake.scr[0].y += SIZE;
        break;
    case left:
        snake.scr[0].x -= SIZE;
        break;
    case right:
        snake.scr[0].x += SIZE;
        break;
    default:
        break;
    }
}
void ChangeSnakech()
{
    switch (_getch())
    {
    case 72:
        if (snake.ch != down)
            snake.ch = up;
        break;
    case 80:
        if (snake.ch != up)
            snake.ch = down;
        break;
    case 75:
        if (snake.ch != right)
            snake.ch = left;
        break;
    case 77:
        if (snake.ch != left)
            snake.ch = right;
        break;
    default:
        break;
    }
}
void FoodCoor()
{
    srand((unsigned)time(NULL));
    food.fcr.x = rand() % 32 * SIZE;
    food.fcr.y = rand() % 24 * SIZE;
    food.flag = 1;
}
void FoodPaint()
{
    putimage(food.fcr.x, food.fcr.y, &SNAKE_FOOD);
}
void EatFood()
{
    if (snake.scr[0].x == food.fcr.x && snake.scr[0].y == food.fcr.y)
    {
        snake.n++;
        food.flag = 0;
    }
}
void judge()
{
    cleardevice();
    settextcolor(LIGHTRED);
    settextstyle(50, 0, L"ø¨ÃÂ");
    outtextxy(250, 200, L"Ω‚ÃÂ£°");
    Sleep(3000);
    exit(0);
}
void GameOver()
{
    if (snake.scr[0].x < 0 || snake.scr[0].x>620 || snake.scr[0].y < 0 || snake.scr[0].y>460)judge();
    for (int i = snake.n - 1; i > 0; i--)
    {
        if (snake.scr[0].x == snake.scr[i].x\
            && snake.scr[0].y == snake.scr[i].y)
        {
            judge();
        }
    }
}
int main()
{
    initGame();
    PlaySound(L"BGM.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    while (1)
    {
        while (!_kbhit())
        {
            if (food.flag == 0)
                FoodCoor();
            cleardevice();
            FoodPaint();
            SnakeMove();
            SnakePaint();
            Sleep(300);
            EatFood();
            GameOver();
        }
        ChangeSnakech();
    }
    return 0;
}