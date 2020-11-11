#include <iostream>
#include <ctime>
#include "cnumericrow.h"


//#include <unistd.h>
//#include <ncurses.h>

#include <conio.h>
#include <windows.h>
using namespace std;

bool gameover;
int height;
int wight;
int x, y;
int foodX, foodY;
int Score;
int Speed;
int Tlength = 1;
int prev2X, prev2Y;
int prevX;
int prevY;
int flag;
CNumericRow TailX(1);
CNumericRow TailY(1);
enum Directions
{
	Left, Right, Up, Down, Stop
}; 
Directions dir;

void Setup_game()
{
	gameover = 0;
	height = 32;
	wight = 32;
	x = 15;
	y = 15;
	dir = Stop;
	srand(time(NULL));
	foodX = 1 + rand() % (wight - 2);
	foodY = 1 + rand() % (height - 2);
	Speed = 25;
}
void Controls()
{
	if (_kbhit())
	{
		switch (_getch ())
		{
		case 'w':
			if (dir != Down)
				dir = Up;
			break;
		case 'a':
			if (dir != Right)
				dir = Left;
			break;
		case 's':
			if (dir != Up)
				dir = Down;
			break;
		case 'd':
			if (dir != Left)
				dir = Right;
			break;
		}
	}
}
void Changes()
{	
	if (Tlength > 0)
	{
		prevX = TailX[0];
		prevY = TailY[0];
		TailX[0] = x;
		TailY[0] = y;
	}
	for (int i = 0; i < Tlength; i++)
	{
		prev2X = TailX[i];
		prev2Y = TailY[i];
		TailX[i] = prevX;
		TailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case Left:
		x--;
		break;
	case Right:
		x++;
		break;
	case Up:
		y--;
		break;
	case Down:
		y++;
		break;
	}
	if (x == foodX && y == foodY)
	{
		Score += 10;
		srand(time(NULL));
		foodX = 1 + rand() % (wight - 2);
		foodY = 1 + rand() % (height - 2);
		Tlength += 1;
		TailX.resize((TailX.getSize()+1), 'f');
		TailY.resize((TailY.getSize() + 1), 'f');
	}
	for (int k = 0; k < Tlength; k++)
	{
		if (TailX[k] == x && TailY[k] == y)
		{
			gameover = 1;
		}
	}
	if (x > 31 || x < 1 || y < 1 || y>31)
	{
		gameover = 1;
	}
}
void Display()
{
	system("cls");
	//system("clear");
	cout << "\n";
	for (int j = 0; j < wight; j++)
	{
		for (int i = 0; i < height; i++)
		{
			if (i == 0 || j == 0 || i == wight - 1 || j == height-1)
			{
				cout << "#";
			}
			else if (i == x && j == y)
			{
				cout << "@";
			}
			else if (i == foodX && foodY == j)
			{
				cout << "F";
			}
			else
			{
				flag = 0;
				for (int k = 0; k < Tlength; k++)
				{
					if (TailX[k] == i && TailY[k] == j)
					{
						flag = 1;
					}
				}
				if (flag)
				{
					cout << 's';
				}
				else
				{
					cout << " ";
				}
			}
		}
		cout << "\n";

	}
	cout << "\n";
	cout << "Score: ";
	cout << Score;
	//usleep(Speed);
	Sleep(Speed);
}

int main()
{
	Setup_game();
	while (!gameover)
	{
		Controls();
		Changes();
		Display();
	}

	return 0;
}