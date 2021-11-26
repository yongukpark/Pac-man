#include "Internet.h"
using namespace std;

void round1() {
	system("cls");
	cout << "ROUND1";
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
	cout << "EXIT";
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

void map() {
	system("cls");
}

int main() {
	system(" mode  con lines=30   cols=100 "); //콘솔창 크키 바꾸기
	startMenu(); //Pac-Man 출력
	mainMenu(); //선택화면 표시
}

