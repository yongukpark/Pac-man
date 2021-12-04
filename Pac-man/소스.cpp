#include <iostream>
#include <stdlib.h> 	
#include <Windows.h>
#include <conio.h>

using namespace std;

char** roundMap;
//맵 이동가능 범위
int start_x;
int start_y;
int end_x;
int end_y;
//현재 팩맨 위치
int current_x;
int current_y;
char head; //팩맨이 가는 위치

const char round1Map[11][21] =  { // 9 * 18 31~69/
	"11111111111111111111",
	"10000100000000100001",
	"10110101111110101101",
	"10100000000000000101",
	"10101101133110110101",
	"10000001333310000001",
	"10101101111110110101",
	"10100000020000000101",
	"10110101111110101101",
	"10000100000000100001",
	"11111111111111111111"
};

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


void setRound1Map(char** &roundMap) {
	roundMap = new char* [11];
	for (int i = 0; i < 11; i++) {
		roundMap[i] = new char[21];
	}
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 21; j++) {
			roundMap[i][j] = round1Map[i][j];
		}
	}
	//콘솔창에서의 인덱스 - 몬스터용
	::start_x = 33;
	::end_x = 67;
	::start_y = 6;
	::end_y = 14;
	//2차원 배열에서의 인덱스 - 팩맨용
	::current_x = 7;
	::current_y = 9;
}

void setRound2Map(){}
void setRound3Map(){}

void showMap() {
	for (int row = 0; row < 11; row++) { 
		gotoxy(start_x-2, start_y-1 + row);
		for (int col = 0; col < 20; col++) {
			if(roundMap[row][col]=='1') {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
				cout << "■"; //벽
			}
			else if(roundMap[row][col]=='0') {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << "ㆍ"; //동전
			}
			else if(roundMap[row][col]=='2'){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				cout << "●"; //팩맨
			}
			else {
				cout << "  "; //공백
			}
		}
		cout << '\n';
	}
}

bool checkMap(const int x, const int y) {
	for (int i = 1; i < x - 1; i++) {
		for (int j = 1; j < y - 1; j++) {
			roundMap[i][j] = '0';
			return false;
		}
	}
	return true;
}

void moveRound(const int x, const int y) {
	char a;
	if (_kbhit()) {
		a = _getch();
		switch (a) {
		case 'w':
		case 'W':
			if ((current_x - 1) >= 1 && roundMap[current_x - 1][current_y] != '1') {
				roundMap[current_x][current_y] = '3';
				current_x--;
				roundMap[current_x][current_y] = '2';
				head = 'w';
				return;
			}
			break;
		case 's':
		case 'S':
			if ((current_x + 1) <= (x - 1) && roundMap[current_x + 1][current_y] != '1') {
				roundMap[current_x][current_y] = '3';
				current_x++;
				roundMap[current_x][current_y] = '2';
				head = 's';
				return;
			}
			break;
		case 'a':
		case 'A':
			if ((current_y - 1) >= 1 && roundMap[current_x][current_y - 1] != '1') {
				roundMap[current_x][current_y] = '3';
				current_y--;
				roundMap[current_x][current_y] = '2';
				head = 'a';
				return;
			}
			break;
		case 'd':
		case 'D':
			if ((current_y + 1) <= (y - 1) && roundMap[current_x][current_y + 1] != '1') {
				roundMap[current_x][current_y] = '3';
				current_y++;
				roundMap[current_x][current_y] = '2';
				head = 'd';
				return;
			}
			break;
		default:
			break;
		}
	}

	a = head;
	switch (a) {
	case 'w':
	case 'W':
		if ((current_x - 1) >= 1 && roundMap[current_x - 1][current_y] != '1') {
			roundMap[current_x][current_y] = '3';
			current_x--;
			roundMap[current_x][current_y] = '2';
			head = 'w';
		}
		break;
	case 's':
	case 'S':
		if ((current_x + 1) <= (x - 1) && roundMap[current_x + 1][current_y] != '1') {
			roundMap[current_x][current_y] = '3';
			current_x++;
			roundMap[current_x][current_y] = '2';
			head = 's';
		}
		break;
	case 'a':
	case 'A':
		if ((current_y - 1) >= 1 && roundMap[current_x][current_y - 1] != '1') {
			roundMap[current_x][current_y] = '3';
			current_y--;
			roundMap[current_x][current_y] = '2';
			head = 'a';
		}
		break;
	case 'd':
	case 'D':
		if ((current_y + 1) <= (y - 1) && roundMap[current_x][current_y + 1] != '1') {
			roundMap[current_x][current_y] = '3';
			current_y++;
			roundMap[current_x][current_y] = '2';
			head = 'd';
		}
		break;
	default:
		break;
	}

}

void successGame() {
	cout << "성공";
}

void round1() {
	system("cls");
	setRound1Map(roundMap);
	showMap();

	while (1) {
		moveRound(11,20);
		showMap();
		if (checkMap(11, 20)) {
			successGame();
			break;
		}
		Sleep(70);
	}

	for (int i = 0; i < 11; i++) {
		delete[] roundMap[i];
	}
	delete[] roundMap;
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

	int a; cin >> a;
}

