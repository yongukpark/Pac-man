#include "Internet.h"
#include <fcntl.h>
#include <io.h>
using namespace std;




const char round1Arr[9][16] = { ' ',	' ',	' ',	' ',	'|',	' ',	' ',	' ',	' ',	' ',	' ',	'|',	' ',	' ',	' ',	' ',
								' ' ,	'-',	'-',	' ',	'|',	' ',	'-',	'-',	'-',	'-',	' ',	'|',	' ',	'-',	'-',	' ',
								' ',	'|',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	'|',	' ',
								' ',	'|',	' ',	'-',	'-',	' ',	'-',	'*',	'*',	'-',	' ',	'-',	'-',	' ',	'|',	' ',
								' ',	' ',	' ',	' ',	' ',	' ',	'|',	'*',	'*',	'|',	' ',	' ',	' ',	' ',	' ',	' ',
								' ',	'|',	' ',	'-',	'-',	' ',	'-',	'-',	'-',	'-',	' ',	'-',	'-',	' ',	'|',	' ',
								' ',	'|',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	' ',	'|',	' ',
								' ',	'-',	'-',	' ',	'|',	' ',	'-',	'-',	'-',	'-',	' ',	'|',	' ',	'-',	'-',	' ',
								' ',	' ',	' ',	' ',	'|',	' ',	' ',	' ',	' ',	' ',	' ',	'|',	' ',	' ',	' ',	' '};



void round1Map() {
	for (int row = 0; row < 9; row++) {
		gotoxy(42, 12 + row);
		for (int col = 0; col < 16; col++) {

			if(round1Arr[row][col]=='*') {
				cout << ' ';
			}
			else if (round1Arr[row][col] != ' ') {
				cout << round1Arr[row][col];
			}
			else {
				cout << "*";
			}
		}
	}
	int a;
	cin >> a;
}

void universialMap(int a,int b) { 
	gotoxy(50 - a / 2, 15 - b / 2); 
	for (int i = 0; i < a/2; i++) { 
		cout << "■";
	}
	for (int i = 1 ; i <= b; i++) { 
		gotoxy(50 - a / 2, 15 - b / 2 + i); 
		cout << "■";
		gotoxy(50 + a / 2 - 2, 15 - b / 2 + i); 
		cout << "■";
	}
	gotoxy(50 - a / 2, 15 + b / 2 + 2); 
	for (int i = 0; i < a/2; i++) {
		cout << "■";
	}
	// 일반화시켜서
	//Y : 15-b/2+1 ~ 15+b/2 사용가능
	//X : 50-a/2+2 ~ 50+a/2-1 사용가능
}

void round1() {
	system("cls");
	universialMap(20,9);
	round1Map();

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
}

