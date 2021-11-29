#ifndef INTERNET_H
#define	INTERNET_H

#include <iostream>
#include <stdlib.h> 	
#include <Windows.h>
#include <conio.h>

void gotoxy(int x, int y) {
	COORD Pos = { x , y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

#endif // !BRINTERNET_H
