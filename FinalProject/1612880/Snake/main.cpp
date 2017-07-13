#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <thread>

using namespace std;

#define MAX_SIZE_SNAKE 30
#define MAX_SIZE_FOOD 4
#define MAX_SPEED 6

struct Gate {
	POINT center; //Diem trung tam
	int direct; //Huong 1-tren 2-phai 3-duoi 4-trai
};
POINT snake[MAX_SIZE_SNAKE]; //con ran
POINT food[MAX_SIZE_FOOD];  //Thuc an
Gate G; //cong 
int CHAR_LOCK; //Bien xac dinh huong khong the di chuyen (o mot thoi diem co mot huong ran khong the di chuyen)
int MOVING; //Bien xac dinh huong di chuyen cua snake (snake co 3 huong co the di chuyen)
int SPEED; //Level, toc do ran
int HEIGH_CONSOLE, WIDTH_CONSOLE; //kich co man hinh console
int FOOD_INDEX; //Chi so thuc an dang co tren man hinh
int SIZE_SNAKE; // Kich thuoc cua snake, luc dau co 6 va toi da la 10
int STATE; // Trang thai song hay chet cua ran
char MSSV[7] = { '1', '6', '1', '2', '8', '8', '0' };
int dy[4][5] = { {-1,0,0,0,-1}, {-1,-1,0,1,1}, {1,0,0,0,1}, { -1,-1,0,1,1 } };
int dx[4][5] = { {-1,-1,0,1,1}, {1,0,0,0,1}, {-1,-1,0,1,1}, { -1,0,0,0,-1 } };

void ClearSnakeAndFood(char *str);
void DrawGate(char* str);
void clearInfor();

void ShowConsoleCursor(bool showFlag) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}
void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

bool IsValid(int x, int y) {
	for (int i = 0; i < SIZE_SNAKE; i++) {
		if (snake[i].x == x & snake[i].y == y)
			return false;
	}
	return true;
}


void GenerateFood() {
	int x, y;
	srand(time(NULL));
	for (int i = 0; i < MAX_SIZE_FOOD; i++) {
		do {
			x = rand() % (WIDTH_CONSOLE - 1) + 1;
			y = rand() % (HEIGH_CONSOLE - 1) + 1;
		} while (!IsValid(x, y));
	food[i] = { x,y };
	}
}

bool OkGate(Gate g) {
	for (int k = 0; k < 5; k++) {
		int i = G.center.x + dx[G.direct - 1][k];
		int j = G.center.y + dy[G.direct - 1][k];
		if (!IsValid(i, j))  return false;
	}
	return true;
}

void GenerateGate() {
	int x, y;
	srand(time(NULL));
	G.center.x = rand() % (WIDTH_CONSOLE - 3) + 2;
	G.center.y = rand() % (HEIGH_CONSOLE - 3) + 2;
	do {
		G.direct = rand() % 4 + 1;
	} while (!OkGate(G));
}

void ResetData() {
	CHAR_LOCK = 'A';
	MOVING = 'D';
	SPEED = 1;
	FOOD_INDEX = 0;
	WIDTH_CONSOLE = 70;
	HEIGH_CONSOLE = 20;
	SIZE_SNAKE = 6;
	snake[0] = { 10, 5 }; snake[1] = { 11, 5 }; 
	snake[2] = { 12, 5 }; snake[3] = { 13, 5 };
	snake[4] = { 14, 5 }; snake[5] = { 15, 5 };
	GenerateFood();
	GenerateGate();
}

void DrawBoard(int x, int y, int width, int height, int curPosX = 0, int curPosY = 0) {
	GotoXY(x, y); 
	printf("+");
	for (int i = 1; i < width; i++) printf("_");
	printf("+");
	GotoXY(x, height + y); printf("+");
	for (int i = 1; i < width; i++) printf("_");
	printf("+");
	for (int i = y + 1; i < height + y; i++) {
		GotoXY(x, i); printf("|");
		GotoXY(x + width, i); printf("|");
	}
	GotoXY(curPosX, curPosY);
}


void StartGame() {
	system("cls");
	ResetData();
	DrawBoard(0, 0, WIDTH_CONSOLE, HEIGH_CONSOLE);
	STATE = 1;
}

void ExitGame(HANDLE t) {
	system("cls");
	TerminateThread(t, NULL);
}

void PauseGame(HANDLE t) {
	SuspendThread(t);
}

void Eat() {
	if (FOOD_INDEX == MAX_SIZE_FOOD) snake[SIZE_SNAKE] = G.center;
	else snake[SIZE_SNAKE] = food[FOOD_INDEX];

	if (FOOD_INDEX == MAX_SIZE_FOOD - 1) {
		GenerateGate();
		FOOD_INDEX++;
	} else if (FOOD_INDEX == MAX_SIZE_FOOD) {
		DrawGate(" ");
		FOOD_INDEX = 0;
		if (SPEED == MAX_SPEED) {
			SPEED = 1;
			SIZE_SNAKE = 6;
		}
		else SPEED++;
		GenerateFood();
	}
	else {
		FOOD_INDEX++; 
		SIZE_SNAKE++;
	}
}

void DrawSnakeAndFood(char *str) {
	if (FOOD_INDEX < MAX_SIZE_FOOD) {
		GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);
		printf(str);
	}
	for (int i = 0; i < SIZE_SNAKE; i++) {
		GotoXY(snake[i].x, snake[i].y);
		printf("%c", MSSV[i % 7]);
	}
}
void DrawGate(char *str) {
	for (int k = 0; k < 5; k++) {
		int i = G.center.x + dx[G.direct - 1][k];
		int j = G.center.y + dy[G.direct - 1][k];
		GotoXY(i, j);
		printf(str);
	}
}

void ClearSnakeAndFood(char *str) {
	GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);
	printf(str);
	for (int i = 0; i < SIZE_SNAKE; i++) {
		GotoXY(snake[i].x, snake[i].y);
		printf(str);
	}
}

bool isClash(int x, int y) {
	for (int i = 0; i < SIZE_SNAKE; i++)
		if (snake[i].x == x && snake[i].y == y) return true;
	return false;
}


void ProcessDead() {
	STATE = 0;
	clearInfor();
	ClearSnakeAndFood(" ");
	ClearSnakeAndFood("x");
	GotoXY(0, HEIGH_CONSOLE + 2);
	printf("You lose! Type 'Y' to continue or anykey to exit\nType 'T' to load game");
}

bool CollideGate(int x, int y) {
	for (int k = 0; k < 5; k++) {
		int i = G.center.x + dx[G.direct - 1][k];
		int j = G.center.y + dy[G.direct - 1][k];
		if (x == i && y == j) return true;
	}
	return false;
}

//Cac ham di chuyen
void MoveRight() {
	if (snake[SIZE_SNAKE - 1].x + 1 >= WIDTH_CONSOLE) {
		ProcessDead();
	}
	else if (isClash(snake[SIZE_SNAKE - 1].x + 1, snake[SIZE_SNAKE - 1].y)) {
		ProcessDead();
	}
	else if (FOOD_INDEX == MAX_SIZE_FOOD) {
		if (snake[SIZE_SNAKE - 1].x + 1 == G.center.x && snake[SIZE_SNAKE - 1].y == G.center.y && G.direct == 4) Eat();
		else if (CollideGate(snake[SIZE_SNAKE - 1].x + 1, snake[SIZE_SNAKE - 1].y)) ProcessDead();
	}
	else if (snake[SIZE_SNAKE - 1].x + 1 == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y) {
		Eat();
	}
	//Chinh lai toa do
	for (int i = 0; i < SIZE_SNAKE - 1; i++) {
		snake[i].x = snake[i + 1].x;
		snake[i].y = snake[i + 1].y;
	}

	snake[SIZE_SNAKE - 1].x++;
}

void MoveLeft() {

	if (snake[SIZE_SNAKE - 1].x - 1 <= 0) {
		ProcessDead();
	}
	else if (isClash(snake[SIZE_SNAKE - 1].x - 1, snake[SIZE_SNAKE - 1].y)) {
		ProcessDead();
	}
	else if (FOOD_INDEX == MAX_SIZE_FOOD) {
		if (snake[SIZE_SNAKE - 1].x - 1 == G.center.x && snake[SIZE_SNAKE - 1].y == G.center.y && G.direct == 2) Eat();
		else if (CollideGate(snake[SIZE_SNAKE - 1].x - 1, snake[SIZE_SNAKE - 1].y)) ProcessDead();
	}
	else if (snake[SIZE_SNAKE - 1].x - 1 == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y) {
		Eat();
	}
	//Chinh lai toa do
	for (int i = 0; i < SIZE_SNAKE - 1; i++) {
		snake[i].x = snake[i + 1].x;
		snake[i].y = snake[i + 1].y;
	}

	snake[SIZE_SNAKE - 1].x--;
}

void MoveDown() {
	if (snake[SIZE_SNAKE - 1].y + 1 >= HEIGH_CONSOLE) {
		ProcessDead();
	}
	else if (isClash(snake[SIZE_SNAKE - 1].x, snake[SIZE_SNAKE - 1].y + 1)) {
		ProcessDead();
	}
	else if (FOOD_INDEX == MAX_SIZE_FOOD) {
		if (snake[SIZE_SNAKE - 1].x == G.center.x && snake[SIZE_SNAKE - 1].y + 1 == G.center.y && G.direct == 1) Eat();
		 else if (CollideGate(snake[SIZE_SNAKE - 1].x, snake[SIZE_SNAKE - 1].y + 1)) ProcessDead();
	}
	else if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y + 1== food[FOOD_INDEX].y) {
		Eat();
	}

	//Chinh lai toa do 

	for (int i = 0; i < SIZE_SNAKE - 1; i++) {
		snake[i].x = snake[i + 1].x;
		snake[i].y = snake[i + 1].y;
	}

	snake[SIZE_SNAKE - 1].y++;
}

void MoveUp() {

	if (snake[SIZE_SNAKE - 1].y - 1 <= 0) {
		ProcessDead();
	}
	else if (isClash(snake[SIZE_SNAKE - 1].x, snake[SIZE_SNAKE - 1].y - 1)) {
		ProcessDead();
	}
	else if (FOOD_INDEX == MAX_SIZE_FOOD) {
		if (snake[SIZE_SNAKE - 1].x == G.center.x && snake[SIZE_SNAKE - 1].y - 1 == G.center.y && G.direct == 3) Eat();
		else if (CollideGate(snake[SIZE_SNAKE - 1].x, snake[SIZE_SNAKE - 1].y - 1)) ProcessDead();
	}
	else if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y - 1 == food[FOOD_INDEX].y) {
		Eat();
	}

	//Chinh lai toa do 

	for (int i = 0; i < SIZE_SNAKE - 1; i++) {
		snake[i].x = snake[i + 1].x;
		snake[i].y = snake[i + 1].y;
	}

	snake[SIZE_SNAKE - 1].y--;
}

void printInfor() {
	GotoXY(WIDTH_CONSOLE/2, HEIGH_CONSOLE + 3);
	printf("LEVEL:  %d", SPEED);
}

void clearInfor() {
	GotoXY(WIDTH_CONSOLE / 2, HEIGH_CONSOLE + 3);
	printf("               ");
}

void SaveGame(char* filename) {
	FILE *f = fopen(filename, "wb");
	fwrite(&SIZE_SNAKE, 1, sizeof(int), f);
	fwrite(&snake, SIZE_SNAKE, sizeof(POINT), f);
	fwrite(&FOOD_INDEX, 1, sizeof(int), f);
	fwrite(&food, MAX_SIZE_FOOD, sizeof(POINT), f);
	fwrite(&G, 1, sizeof(Gate), f);
	fwrite(&SPEED, 1, sizeof(int), f);
	fwrite(&CHAR_LOCK, 1, sizeof(char), f);
	fwrite(&MOVING, 1, sizeof(char), f);
	fclose(f);
}

bool LoadGame(char *filename) {
	FILE *f = fopen(filename, "rb");
	if (f == NULL) {
		return false;
	}
	StartGame();
	fread(&SIZE_SNAKE, 1, sizeof(int), f);
	fread(&snake, SIZE_SNAKE, sizeof(POINT), f);
	fread(&FOOD_INDEX, 1, sizeof(int), f);
	fread(&food, MAX_SIZE_FOOD, sizeof(POINT), f);
	fread(&G, 1, sizeof(Gate), f);
	fread(&SPEED, 1, sizeof(int), f);
	fread(&CHAR_LOCK, 1, sizeof(char), f);
	fread(&MOVING, 1, sizeof(char), f);
	fclose(f);
	return true;
}

void ThreadFunc() {
	while (1) {
		if (STATE == 1) {
			ClearSnakeAndFood(" ");
			printInfor();
			switch (MOVING) {
			case 'A': {
				CHAR_LOCK = 'D';
				MoveLeft();
				break;
			}
			case 'D': {
				CHAR_LOCK = 'A';
				MoveRight();
				break;
			}
			case 'S': {
				CHAR_LOCK = 'W';
				MoveDown();
				break;
			}
			case 'W': {
				CHAR_LOCK = 'S';
				MoveUp();
				break;
			}
			}
			if (STATE == 1) {
				if (FOOD_INDEX == MAX_SIZE_FOOD) {
					DrawGate("x");
					DrawSnakeAndFood(" ");
				}
				else DrawSnakeAndFood("o");
			}
		Sleep(180/ (SPEED));
		}
	}
}


void main() {
	int temp;
	char filename[50];
	FixConsoleWindow();
	printf("SNAKE GAME\n");
	printf("Type 'T' to load game \nAnother key to start new game!");
	int s = toupper(_getch());
	//game
	ShowConsoleCursor(false);
	StartGame();
	thread t1(ThreadFunc);
	HANDLE handle_t1 = t1.native_handle();
	if (s == 'T') goto LoadGame;
	while (1) {
		temp = toupper(_getch());
		GotoXY(0, 23);
		if (STATE == 1) {
			if (temp == 'P') {
				PauseGame(handle_t1);
				continue;
			}
			if (temp == 'L') {
				PauseGame(handle_t1);
				clearInfor();
				ShowConsoleCursor(true);
				GotoXY(0, HEIGH_CONSOLE + 3);
				printf("Nhap duong dan link: "); gets_s(filename);
				SaveGame(filename);
				GotoXY(0, HEIGH_CONSOLE + 3);
				printf("                                           ");
				ShowConsoleCursor(false);
				ResumeThread(handle_t1);
			}
			else if (temp == 'T') {
			LoadGame:
				PauseGame(handle_t1);
				system("cls");
				ShowConsoleCursor(true);
				printf("Nhap duong dan link: "); gets_s(filename);
				while (!LoadGame(filename)) {
					printf("File not Found!\nNhap lai link: "); 
					gets_s(filename);
				}
				ShowConsoleCursor(false);
				ResumeThread(handle_t1);
			}
			else if (temp == 27) {
				ExitGame(handle_t1);
				exit(0);
			}
			else {
				ResumeThread(handle_t1);
				if ((temp != CHAR_LOCK) && (temp == 'D' || temp == 'A' || temp == 'W' || temp == 'S')) {
					MOVING = temp;
				}
			}
		}
		else {
			if (temp == 89) {
				StartGame();
			}
			else if (temp == 'T') {
				goto LoadGame;
			}
			else {
				ExitGame(handle_t1);
				exit(0);
			}
		}
	}
}