#include <iostream>
#include <stdlib.h> 	
#include <Windows.h>
#include <conio.h>

using namespace std;

#define round1_start_x 30
#define round1_start_y 6
#define round1_end_x 66
#define round1_end_y 14

void gotoxy(int x, int y) {
	COORD Pos = { x , y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void CursorView(){
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
	cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

//const char round1Map[9][16] = {' ',	' ',	' ',	' ',	'|',	' ',	' ',	' ',	' ',	' ',	' ',	'|',	' ',	' ',	' ',	' ',
//								' ' ,	'-',	'-',	' ',	'|',	' ',	'-',	'-',	'-',	'-',	' ',	'|',	' ',	'-',	'-',	' ',
//								' ',	'|',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	'|',	' ',
//								' ',	'|',	' ',	'-',	'-',	' ',	'-',	'*',	'*',	'-',	' ',	'-',	'-',	' ',	'|',	' ',
//								' ',	' ',	' ',	' ',	' ',	' ',	'|',	'*',	'*',	'|',	' ',	' ',	' ',	' ',	' ',	' ',
//								' ',	'|',	' ',	'-',	'-',	' ',	'-',	'-',	'-',	'-',	' ',	'-',	'-',	' ',	'|',	' ',
//								' ',	'|',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	'|',	' ',
//								' ',	'-',	'-',	' ',	'|',	' ',	'-',	'-',	'-',	'-',	' ',	'|',	' ',	'-',	'-',	' ',
//								' ',	' ',	' ',	' ',	'|',	' ',	' ',	' ',	' ',	' ',	' ',	'|',	' ',	' ',	' ',	' '};

//const char round1Map[9][16] = { ' ',	' ',	' ',	' ',	'#',	' ',	' ',	' ',	' ',	' ',	' ',	'#',	' ',	' ',	' ',	' ',
//								' ' ,	'#',	'#',	' ',	'#',	' ',	'#',	'#',	'#',	'#',	' ',	'#',	' ',	'#',	'#',	' ',
//								' ',	'#',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	'#',	' ',
//								' ',	'#',	' ',	'#',	'#',	' ',	'#',	'*',	'*',	'#',	' ',	'#',	'#',	' ',	'#',	' ',
//								' ',	' ',	' ',	' ',	' ',	' ',	'#',	'*',	'*',	'#',	' ',	' ',	' ',	' ',	' ',	' ',
//								' ',	'#',	' ',	'#',	'#',	' ',	'#',	'#',	'#',	'#',	' ',	'#',	'#',	' ',	'#',	' ',
//								' ',	'#',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	'#',	' ',
//								' ',	'#',	'#',	' ',	'#',	' ',	'#',	'#',	'#',	'#',	' ',	'#',	' ',	'#',	'#',	' ',
//								' ',	' ',	' ',	' ',	'#',	' ',	' ',	' ',	' ',	' ',	' ',	'#',	' ',	' ',	' ',	' ' };
//

char round1Map[11][21];

void setround1Map(char round1Map[11][21]) {
	strcpy_s(round1Map[0], "11111111111111111111");
	strcpy_s(round1Map[1], "10000100000000100001");
	strcpy_s(round1Map[2], "10110101111110101101");
	strcpy_s(round1Map[3], "10100000000000000101");
	strcpy_s(round1Map[4], "10101101100110110101");
	strcpy_s(round1Map[5], "10000001000010000001");
	strcpy_s(round1Map[6], "10101101111110110101");
	strcpy_s(round1Map[7], "10100000000000000101");	
	strcpy_s(round1Map[8], "10110101111110101101");
	strcpy_s(round1Map[9], "10000100000000100001");
	strcpy_s(round1Map[10],"11111111111111111111");
}

void showround1Map() {
	for (int row = 0; row < 11; row++) { 
		gotoxy(round1_start_x-1, round1_start_y-1 + row);
		for (int col = 0; col < 20; col++) {
			if(round1Map[row][col]=='1') {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
				cout << "■";
			}
			else if(round1Map[row][col]=='0') {
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

void checkRound1Map() {

}

void moveRound1(int& x, int& y) {
	char a = _getch();
	switch (a){
	case 'w':
	case 'W':
		if ((y - 1) >= round1_start_y && round1Map[y - round1_start_y][(x - round1_start_x)/2+1] != '1') {

			y--;
			showround1Map();
			gotoxy(x, y);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			cout << "●";
		}
		break;
	case 's':
	case 'S':
		if ((y + 1) <= round1_end_y && round1Map[y - round1_start_y + 2][(x - round1_start_x) / 2 + 1] != '1') {

			y++;
			showround1Map();
			gotoxy(x, y);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			cout << "●";
		}
		break;
	case 'a':
	case 'A':
		if ((x - 2) >= round1_start_x && round1Map[y - round1_start_y + 1][(x - 2 - round1_start_x) / 2 + 1] != '1') {

			x-=2;
			showround1Map();
			gotoxy(x, y);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			cout << "●";
		}
		break;
	case 'd':
	case 'D':
		if ((x + 2) < round1_end_x && round1Map[y - round1_start_y + 1][(x + 2 - round1_start_x) / 2 + 1] != '1') {

			x+=2;
			showround1Map();
			gotoxy(x, y);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			cout << "●";
		}
		break;
	default:
		break;
	}
}

void round1() {
	system("cls");
	setround1Map(round1Map);
	round1Map[7][8] = '2';
	showround1Map();
	
	gotoxy(round1_start_x + 15, round1_start_y+6);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << "●";

	int x = 45;
	int y = 12;
	while (1) {
		moveRound1(x, y);
	}


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
	CursorView();
	system(" mode  con lines=30   cols=100 "); //콘솔창 크키 바꾸기
	startMenu(); //Pac-Man 출력
	mainMenu(); //선택화면 표시

	int a;
	cin >> a;
}

