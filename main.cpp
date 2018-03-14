#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail = 0;  // so we know how many segments there are.
enum eDirection{STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void Setup() {
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;  //what if they're the same?
	score = 0;
}

void Draw() {
	system("cls");  // will clear the console window
	for (int i = 0; i <= width+1; i++)
		cout << "# ";
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0)
				cout << "# ";
			if (i == y && j == x)
				cout << "O ";
			else if (i == fruitY && j == fruitX)
				cout << "F ";
			else{
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						cout << "o ";
						print = true;
					}
				}
				if(!print){
				cout << "  ";
				}
			}

			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i <= width+1; i++)
		cout << "# ";
	cout << endl << "Score: " << score << endl;
}

void Input() {
	if (_kbhit()) { //returns number if keyboard key is pressed, else 0.
		switch (_getch()) { //returns last key pressed?
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
		case 'g':
			gameOver = true;
			break;
		}
	}
}

void Tailmove() {
	// moves up the tail position by 1 length.
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++) { //moves the tail up one position
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
}

void Logic() {
	
	if (x == fruitX && y == fruitY) {
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}

	switch (dir) {
	case LEFT:
		if (x > 0) {
			Tailmove();
			x--;
		}
		break;
	case RIGHT:
		if(x<width-1){
			Tailmove();
			x++;
		}
		break;
	case UP:
		if(y>0){
			Tailmove();
			y--;
		}
		break;
	case DOWN:
		if(y<height-1){
			Tailmove();
			y++;
		}
		break;
	default:
		break;
	}
	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y) {
			gameOver = true;
		}
	}
}

void Snake_gameover() {
	system("cls");
	cout << "GAME OVER!" << endl << endl;
	cout << "Final Score: " << score << endl;
	Sleep(2500);
	cout << endl << "Press any key"<<endl;
	Sleep(500);
	_getch();
}

int main() {
	Setup();
	while (!gameOver) {
		Draw();
		Input();
		Logic();
		Sleep(10);  // to slow down the game.
	}
	Snake_gameover();
	return 0;
}
