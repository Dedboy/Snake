#include <iostream>
#include <conio.h>
#include <windows.h>
#include "snake.h"
#include <fstream>
using namespace std;
//Define what ends the program
bool gameOver;
// Coordinate system
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score, cust;
int tailX[100], tailY[100];
int nTail;
//Changing the direction of the snake
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;






void Difficulty()
{

	diff snake;

	// sleepo controls 1-3 for difficulty settings and is directly tied to skrrt which holds the sleep values for how fast the game should run. 
	// the else if stops any input that isn't one of the three. cust takes the value out of the struct and allows me to use it with the sleep function.4

		printf("Choose your difficulty.\n");
		cout << "1. Easy\n 2.Medium\n 3.Hard\n";
		cin >> snake.sleepo;

		if (snake.sleepo == 1)
		{
			snake.skrrt = 50;
		}
		else if (snake.sleepo == 2)
		{
			snake.skrrt = 30;
		}
		else if (snake.sleepo == 3)
		{
			snake.skrrt = 10;
		}
		else if (snake.sleepo > 3 || snake.sleepo < 1)
		{
			cout << "Try again.";
			gameOver = true;

		}

		cout << "Difficulty set!\n";

		cust = snake.skrrt;

}

void fileWrite()
{
	ofstream file("fyle.txt");

	file << "\nThanks for playing my snake game!\n";
	file << "\nHere are your scores!\n";
	
	
	file.close();

}
void fileAdd()
{
	ofstream file("fyle.txt", ios::app);
	file << "- - - - - - - - - - - - -";
	file << "\n";
	file << score;
	file << "\n";
}
void Setup()
{
	//Startup - Direction set to stop immediately until moved. Start point set to middle of map x/y. Fruit randomly placed around map. 

	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}
void Draw()
{
	system("cls");
	for (int i = 0; i < width+1; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		// Telling it what to draw for characters.

		for (int j = 0; j < width; j++)
		{
			if (j == 0)  
				cout << "#";
			if (i == y && j == x)
				cout << "0";
			else if (i == fruitY && j == fruitX)
				cout << "$";
			else
			{
				//Displaying and growing the tail

				bool print = false;
				for (int k = 0; k < nTail; k++)
				{

					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}

				}
				if (!print)
					cout << " ";


			}

			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}
	//Displaying the score
	for (int i = 0; i < width+1; i++)
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;

}
	// Using Conio to map out movement inputs.

	void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;

		}
	}
}
void Logic()
{

	//Making sure the tail functions and follows the head.

	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	//Mapping out how to move the snake.

	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;

	case DOWN:
		y++;
		break;

	case UP:
		y--;
		break;
	
	default:
		break;


	}

	//old gameover but I thought itd be cooler to go through walls like PacMan
	//if (x > width || x < 0 || y > height || y < 0)
		//gameOver = true;
	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= height) y = 0; else if (y < 0) y = height - 1;
	
	//If you hit yourself, you die. 

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;

	//Collecting fruits to grow.
	if (x == fruitX && y == fruitY)
	{
		
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}

}
int main()
{

	Difficulty();
	Setup();
	while (!gameOver)
	{
	
		Draw();
		Input();
		Logic();
		Sleep(cust);
	}

	fileWrite();
	fileAdd();

	return 0;
}