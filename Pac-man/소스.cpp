#include <iostream>
#include <stdlib.h> 	
#include <Windows.h>
#include <conio.h>

using namespace std;

#define round1_start_x 30
#define round1_start_y 6
#define round1_end_x 68
#define round1_end_y 16

void gotoxy(int x, int y) {
	COORD Pos = { x , y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//const char round1Arr[9][16] = {' ',	' ',	' ',	' ',	'|',	' ',	' ',	' ',	' ',	' ',	' ',	'|',	' ',	' ',	' ',	' ',
//								' ' ,	'-',	'-',	' ',	'|',	' ',	'-',	'-',	'-',	'-',	' ',	'|',	' ',	'-',	'-',	' ',
//								' ',	'|',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	'|',	' ',
//								' ',	'|',	' ',	'-',	'-',	' ',	'-',	'*',	'*',	'-',	' ',	'-',	'-',	' ',	'|',	' ',
//								' ',	' ',	' ',	' ',	' ',	' ',	'|',	'*',	'*',	'|',	' ',	' ',	' ',	' ',	' ',	' ',
//								' ',	'|',	' ',	'-',	'-',	' ',	'-',	'-',	'-',	'-',	' ',	'-',	'-',	' ',	'|',	' ',
//								' ',	'|',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	'|',	' ',
//								' ',	'-',	'-',	' ',	'|',	' ',	'-',	'-',	'-',	'-',	' ',	'|',	' ',	'-',	'-',	' ',
//								' ',	' ',	' ',	' ',	'|',	' ',	' ',	' ',	' ',	' ',	' ',	'|',	' ',	' ',	' ',	' '};

//const char round1Arr[9][16] = { ' ',	' ',	' ',	' ',	'#',	' ',	' ',	' ',	' ',	' ',	' ',	'#',	' ',	' ',	' ',	' ',
//								' ' ,	'#',	'#',	' ',	'#',	' ',	'#',	'#',	'#',	'#',	' ',	'#',	' ',	'#',	'#',	' ',
//								' ',	'#',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	'#',	' ',
//								' ',	'#',	' ',	'#',	'#',	' ',	'#',	'*',	'*',	'#',	' ',	'#',	'#',	' ',	'#',	' ',
//								' ',	' ',	' ',	' ',	' ',	' ',	'#',	'*',	'*',	'#',	' ',	' ',	' ',	' ',	' ',	' ',
//								' ',	'#',	' ',	'#',	'#',	' ',	'#',	'#',	'#',	'#',	' ',	'#',	'#',	' ',	'#',	' ',
//								' ',	'#',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	'#',	' ',
//								' ',	'#',	'#',	' ',	'#',	' ',	'#',	'#',	'#',	'#',	' ',	'#',	' ',	'#',	'#',	' ',
//								' ',	' ',	' ',	' ',	'#',	' ',	' ',	' ',	' ',	' ',	' ',	'#',	' ',	' ',	' ',	' ' };
//

char round1Arr[11][21];

void setRound1Arr(char round1Arr[11][21]) {
	strcpy_s(round1Arr[0], "11111111111111111111");
	strcpy_s(round1Arr[1], "10000100000000100001");
	strcpy_s(round1Arr[2], "10110101111110101101");
	strcpy_s(round1Arr[3], "10100000000000000101");
	strcpy_s(round1Arr[4], "10101101100110110101");
	strcpy_s(round1Arr[5], "10000001000010000001");
	strcpy_s(round1Arr[6], "10101101111110110101");
	strcpy_s(round1Arr[7], "10100000000000000101");	
	strcpy_s(round1Arr[8], "10110101111110101101");
	strcpy_s(round1Arr[9], "10000100000000100001");
	strcpy_s(round1Arr[10],"11111111111111111111");
}

void round1Map() {
	for (int row = 0; row < 11; row++) { 
		gotoxy(round1_start_x-1, round1_start_y-1 + row);
		for (int col = 0; col < 20; col++) {
			if(round1Arr[row][col]=='1') {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
				cout << "■";
			}
			else if(round1Arr[row][col]=='0') {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << "ㆍ";
			}
			else {
				cout << "  ";
			}
		}
		cout << '\n';
	}
}



void round1() {
	system("cls");
	setRound1Arr(round1Arr);
	round1Map();

	round1Arr[7][8] = '2';
	round1Map();
	gotoxy(round1_start_x + 15, round1_start_y+6);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << "●";
	Sleep(300);

	round1Arr[7][7] = '2';
	round1Map();
	gotoxy(round1_start_x + 13, round1_start_y + 6);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << "●";
	Sleep(300);

	round1Arr[7][6] = '2';
	round1Map();
	gotoxy(round1_start_x + 11, round1_start_y + 6);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << "●";
	Sleep(300);
}

void round2() {
	cout << "ROUND2";
}

void round3() {
	cout << "ROUND3";
}

void scoreBoard() {

}

void exit_game() {

	exit(0);
}

void mainMenu() {
	gotoxy(38, 3);
	cout << "Welcome to Pacman World!";
	gotoxy(70, 8);
	cout << "1.Round 1";
	gotoxy(70, 9);
	cout << "2.Round 2";
	gotoxy(70, 10);
	cout << "3.Round 3";
	gotoxy(70, 11);
	cout << "4.Scoreboard";
	gotoxy(70, 12);
	cout << "5.Exit";

	bool checkMenu = true;
	while (checkMenu) {
		checkMenu = false;
		int inputNum = _getch();
		switch (inputNum) {
		case 49:
			round1();
			break;
		case 50:
			round2();
			break;
		case 51:
			round3();
			break;
		case 52:
			scoreBoard();
		case 53:
			exit_game();
			break;
		default:
			checkMenu = true;
		}
	}

}

void startMenu() {
	
	gotoxy(29, 5);
	cout << "______               ___  ___";
	gotoxy(30, 6);
	cout << "| ___＼             |  ＼/  |";
	gotoxy(30, 7);
	cout << "| |_/ / __ _   ___  | .   . |  __ _  _ __";
	gotoxy(30, 8);
	cout << "| __/  / _` | / __| | |＼/| | / _` || '_ ＼ ";
	gotoxy(30, 9);
	cout << "| |   | (_| || (__  | |   | || (_| || | | |";
	gotoxy(30, 10);
	cout << "＼_|   ＼___|＼___| ＼_|  |_/＼__,_||_| |_|";

	gotoxy(39,15);
	cout << "Press any key to start";
	if (_getch()) {
		system("cls");
		return;
	}
}

int main() {
	system(" mode  con lines=30   cols=100 "); //콘솔창 크키 바꾸기
	startMenu(); //Pac-Man 출력
	mainMenu(); //선택화면 표시

	int a;
	cin >> a;
}

