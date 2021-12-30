#include <iostream>
#include <stdlib.h> 	
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include <iomanip>
#include <vector>
#include <utility>
#include <algorithm>
#include <random>
#include <queue>

void mainMenu();
void exit_game();
void scoreBoard();
void round1();
void round2();
void round3();
void countDown();
void makeUseMapStart();
void makeUseMapMap(int,int);
void makeUseMapPacman(int, int, bool);
void makeUseMapMonster(int, int);
void makeUseMapSet(int, int, int);
void useMapStart();
void showMap(int, int);
bool movePacMan(int, int);
bool checkMap(int, int);
bool moveMonster(int, int);

using namespace std;

// 맵
char** roundMap;
// 현재 팩맨 위치
int current_x;
int current_y;
// 몬스터 위치, 수
int** monsterArr;
int monsterNum;
// 맵 시작과 끝
int start_x;
int start_y;
int end_x;
int end_y;
// 팩맨이 가는 방향
char head; 

void gotoxy(int x, int y) {
	COORD Pos = { x , y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void CursorView() {
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
	cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void CursorView2() {
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
	cursorInfo.bVisible = TRUE; //커서 Visible TRUE(보임) FALSE(숨김)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

bool compare(pair<string, int> p1, pair<string, int> p2) {
	return p1.second < p2.second;
}

bool bfsUseMap(int col, int row) {

	char** copyRoundMap = new char* [col];
	for (int i = 0; i < col; i++) {
		copyRoundMap[i] = new char[row];
	}
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			copyRoundMap[i][j] = roundMap[i][j];
		}
	}
	queue <pair<int,int>> q;

	bool flg = true;
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			if (copyRoundMap[i][j] == '0' || copyRoundMap[i][j] == '2' || copyRoundMap[i][j] == '4') {
				q.push({ i,j });
				copyRoundMap[i][j] = '1';
				flg = false;
				break;
			}
		}
		if (!flg) {
			break;
		}
	}
	if (flg) {
		for (int i = 0; i < col; i++) {
			delete[] copyRoundMap[i];
		}
		delete[] copyRoundMap;
		return false;
	}

	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		if (copyRoundMap[x-1][y] == '0' || copyRoundMap[x - 1][y] == '2' || copyRoundMap[x - 1][y] == '4') {
			q.push({ x - 1 ,y });
			copyRoundMap[x - 1][y] = '1';
		}
		if (copyRoundMap[x + 1][y] == '0' || copyRoundMap[x + 1][y] == '2' || copyRoundMap[x + 1][y] == '4') {
			q.push({ x + 1 ,y });
			copyRoundMap[x + 1][y] = '1';
		}
		if (copyRoundMap[x][y - 1] == '0' || copyRoundMap[x][y - 1] == '2' || copyRoundMap[x][y - 1] == '4') {
			q.push({ x,y - 1 });
			copyRoundMap[x][y - 1] = '1';
		}
		if (copyRoundMap[x][y + 1] == '0' || copyRoundMap[x][y + 1] == '2' || copyRoundMap[x][y + 1] == '4') {
			q.push({ x,y + 1 });
			copyRoundMap[x][y + 1] = '1';
		}
	}

	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			if (copyRoundMap[i][j] != '1') {

				for (int i = 0; i < col; i++) {
					delete[] copyRoundMap[i];
				}
				delete[] copyRoundMap;
				return false;

			}
		}
	}

	for (int i = 0; i < col; i++) {
		delete[] copyRoundMap[i];
	}
	delete[] copyRoundMap;

	return true;
}


// round1 settings
const char round1Map[11][21] =  { // 9 * 18 31~69/
	"11111111111111111111",
	"10000100000000100001",
	"10110101111110101101",
	"10100004000400000101",
	"10101101100110110101",
	"10000001000010000001",
	"10101101111110110101",
	"10100000020000000101",
	"10110101111110101101",
	"10000100000000100001",
	"11111111111111111111"
};

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

	//2차원 배열에서의 인덱스 - 팩맨용
	::start_x = 33;
	::start_y = 6;
	::end_x = 67;
	::end_y = 14;
	::current_x = 7;
	::current_y = 9;
	head = 'b';
}

void setRound1Monster(int**& arr) {
	arr = new int* [2];
	for (int i = 0; i < 2; i++) {
		arr[i] = new int[2];
	}
	arr[0][0] = 3;
	arr[0][1] = 7;
	arr[1][0] = 3;
	arr[1][1] = 11;
	monsterNum = 2;
}

// round2 settings
const char round2Map[11][21] = { // 9 * 18 31~69/
	"11111111111111111111",
	"10000100000000100001",
	"10110101111110101101",
	"10100004040400000101",
	"10101101100110110101",
	"10000001000010000001",
	"10101101111110110101",
	"10100000020000000101",
	"10110101111110101101",
	"10000100000000100001",
	"11111111111111111111"
};

void setRound2Map(char**& roundMap) {
	roundMap = new char* [11];
	for (int i = 0; i < 11; i++) {
		roundMap[i] = new char[21];
	}
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 21; j++) {
			roundMap[i][j] = round2Map[i][j];
		}
	}

	//2차원 배열에서의 인덱스 - 팩맨용
	::start_x = 33;
	::start_y = 6;
	::end_x = 67;
	::end_y = 14;
	::current_x = 7;
	::current_y = 9;
	head = 'b';
}

void setRound2Monster(int**& arr) {
	arr = new int* [3];
	for (int i = 0; i < 3; i++) {
		arr[i] = new int[2];
	}
	arr[0][0] = 3;
	arr[0][1] = 7;
	arr[1][0] = 3;
	arr[1][1] = 9;
	arr[2][0] = 3;
	arr[2][1] = 11;
	monsterNum = 3;
}

// round3 settings
const char round3Map[21][29] = {
	"1111111111111111111111111111",
	"1000000000000000000000000001",
	"1011110110111111110110111101",
	"1011110110111111110110111101",
	"1000004110000110000114000001",
	"1110110111110110111110110111",
	"1110110111110110111110110111",
	"1110000110000000000110000111",
	"1111110110110110110110111111",
	"1111110110100000010110111111",
	"1111110000100000010000111111",
	"1111110110100000010110111111",
	"1111110110111111110110111111",
	"1110000110000200000110000111",
	"1110110111110110111110110111",
	"1110110111110110111110110111",
	"1000004110000110000110000001",
	"1011110110111111110110111101",
	"1011110110111111110110111101",
	"1000000000000000000000000001",
	"1111111111111111111111111111"
};

void setRound3Map(char** &roundMap){
	roundMap = new char* [21];
	for (int i = 0; i < 21; i++) {
		roundMap[i] = new char[28];
	}
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 28; j++) {
			roundMap[i][j] = round3Map[i][j];
		}
	}

	//2차원 배열에서의 인덱스 - 팩맨용
	::start_x = 25;
	::start_y = 6;
	::end_x = 75;
	::end_y = 24;
	::current_x = 13;
	::current_y = 13;
	head = 'b';
}

void setRound3Monster(int**& arr) {
	arr = new int* [4];
	for (int i = 0; i < 4; i++) {
		arr[i] = new int[2];
	}
	arr[0][0] = 16;
	arr[0][1] = 6;
	arr[1][0] = 4;
	arr[1][1] = 6;
	arr[2][0] = 4;
	arr[2][1] = 21;
	arr[3][0] = 16;
	arr[3][1] = 21;
	monsterNum = 4;
}

// usemap settings 
char** useMap;

int useMapRow = 0;

int useMapColume = 0;

int useMapMonsterNum = 0;

int** useMapMonsterArr;

int useMapStartX;

int useMapStartY;

int useMapEndX;

int useMapEndY;

int useMapCurrentX;

int useMapCurrentY;

int useMapSpeed = 0;

void useMapStart() {

	roundMap = new char* [useMapColume];
	for (int i = 0; i < useMapColume; i++) {
		roundMap[i] = new char[useMapRow+1];
	}
	for (int i = 0; i < useMapColume; i++) {
		for (int j = 0; j < useMapRow; j++) {
			roundMap[i][j] = useMap[i][j];
		}
	}

	::start_x = useMapStartX;
	::start_y = useMapStartY;
	::end_x = useMapEndX;
	::end_y = useMapEndY;
	::current_x = useMapCurrentX;
	::current_y = useMapCurrentY;
	::monsterNum = useMapMonsterNum;
	head = 'b';

	monsterArr = new int* [useMapMonsterNum];
	for (int i = 0; i < useMapMonsterNum; i++) {
		monsterArr[i] = new int[2];
	}
	
	for (int i = 0; i < useMapMonsterNum; i++) {
		monsterArr[i][0] = useMapMonsterArr[i][0];
		monsterArr[i][1] = useMapMonsterArr[i][1];
	}

	countDown();
	clock_t start_clk = clock();
	system("cls");

	showMap(useMapColume, useMapRow);
	while (1) {
		if (!movePacMan(useMapColume, useMapRow)) {
			for (int i = 0; i < useMapColume; i++) {
				delete[] roundMap[i];
			}
			delete[] roundMap;

			for (int i = 0; i < useMapMonsterNum; i++) {
				delete[] monsterArr[i];
			}
			delete[] monsterArr;

			system("cls");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			gotoxy(48, 3);
			cout << "Fail";
			gotoxy(70, 8);
			cout << "1.Play again";
			gotoxy(70, 9);
			cout << "2.Main menu";
			gotoxy(70, 10);
			cout << "3.Exit";

			bool checkMenu = true;
			while (checkMenu) {
				checkMenu = false;
				int inputNum = _getch();
				switch (inputNum) {
				case 49:
					return useMapStart();
					break;
				case 50:
					return mainMenu();
					break;
				case 51:
					return exit_game();
					break;
				default:
					checkMenu = true;
				}
			}
			break;
		};
		if (!moveMonster(useMapColume, useMapRow)) {
			for (int i = 0; i < useMapColume; i++) {
				delete[] roundMap[i];
			}
			delete[] roundMap;

			for (int i = 0; i < useMapMonsterNum; i++) {
				delete[] monsterArr[i];
			}
			delete[] monsterArr;

			system("cls");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			gotoxy(48, 3);
			cout << "Fail";
			gotoxy(70, 8);
			cout << "1.Play again";
			gotoxy(70, 9);
			cout << "2.Main menu";
			gotoxy(70, 10);
			cout << "3.Exit";

			bool checkMenu = true;
			while (checkMenu) {
				checkMenu = false;
				int inputNum = _getch();
				switch (inputNum) {
				case 49:
					return useMapStart();
					break;
				case 50:
					return mainMenu();
					break;
				case 51:
					return exit_game();
					break;
				default:
					checkMenu = true;
				}
			}
			break;
		}
		showMap(useMapColume, useMapRow);
		if (checkMap(useMapColume, useMapRow)) {

			for (int i = 0; i < useMapColume; i++) {
				delete[] roundMap[i];
			}
			delete[] roundMap;

			for (int i = 0; i < useMapMonsterNum; i++) {
				delete[] monsterArr[i];
			}
			delete[] monsterArr;

			clock_t end_clk = clock();

			system("cls");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			gotoxy(46, 3);
			cout << "Succeess";

			system("cls");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			gotoxy(48, 3);
			cout << "Success";
			gotoxy(70, 8);
			cout << "1.Main menu";
			gotoxy(70, 9);
			cout << "2.Exit";

			bool checkMenu = true;
			while (checkMenu) {
				checkMenu = false;
				int inputNum = _getch();
				switch (inputNum) {
				case 49:
					return mainMenu();
					break;
				case 50:
					return exit_game();
					break;
				default:
					checkMenu = true;
				}
			}
			break;
		}
		Sleep(useMapSpeed);
	}
}

void makeUseMapStart() {
	system("cls");
	int col, row;
	gotoxy(46, 5);
	cout << "Map Size";
	gotoxy(43, 7);
	cout << "Column(4~20) : ";
	cin >> col;
	gotoxy(43, 8);
	cout << "Row(4~30) : ";
	cin >> row;

	system("cls");
	::start_x = 53 - row;
	::start_y = 6;
	::end_x = 47 + row;
	::end_y = col + 3;

	roundMap = new char* [col];
	for (int i = 0; i < col; i++) {
		roundMap[i] = new char[row + 1];
		for (int j = 0; j < row; j++) {
			roundMap[i][j] = '1';
		}
	}

	return makeUseMapMap(col, row);
}

void makeUseMapMap(int col, int row) {
	system("cls");
	int x, y;
	x = 1;
	y = 1;
	int a;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	gotoxy(10, 0);
	cout << "블럭 설치";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(10, 1);
	cout << "방향키로 이동";
	gotoxy(10, 2);
	cout << "스페이스바로 블럭 설치 / 삭제";
	gotoxy(10, 3);
	cout << "블럭 설치 끝나면 Next / mainmenu로 나가면 저장 안됨";
	gotoxy(85, 8);
	cout << "1.Next";
	gotoxy(85, 9);
	cout << "2.Main menu";

	while (1) {
		showMap(col, row);
		gotoxy(x + 52 - row, y + 5);
		CursorView2();
		a = _getch();
		CursorView();
		gotoxy(10, 4);
		cout << "                                ";
		if (a == 87 || a == 119) {
			if (y + 4 >= start_y) {
				y--;
			}
		}
		else if (a == 83 || a == 115) {
			if (y + 6 <= end_y) {
				y++;
			}
		}
		else if (a == 65 || a == 97) {
			if (x + 50 - row >= start_x) {
				x = x - 2;
			}
		}
		else if (a == 68 || a == 100) {
			if (x + 54 - row <= end_x) {
				x = x + 2;
			}
		}
		else if (a == 32) {
			if (roundMap[y][x / 2 + 1] == '1') {
				roundMap[y][x / 2 + 1] = '0';
			}
			else {
				roundMap[y][x / 2 + 1] = '1';
			}
		}
		else if (a == 50) {
			for (int i = 0; i < col; i++) {
				delete[] roundMap[i];
			}
			delete[] roundMap;

			return mainMenu();
		}
		else if (a == 49) {
			if (bfsUseMap(col, row)) {
				return makeUseMapPacman(col, row, false);
			}
			else {
				gotoxy(10, 4);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout << "유효하지 않은 맵입니다.";

			}
		}

	}
}

void makeUseMapPacman(int col, int row, bool check) {
	system("cls");
	int x, y;
	x = 1;
	y = 1;
	int a;
	bool flg = check;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	gotoxy(10, 0);
	cout << "팩맨 위치 지정";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(10, 1);
	cout << "방향키로 이동";
	gotoxy(10, 2);
	cout << "스페이스바로 팩맨 설치 / 삭제";
	gotoxy(10, 3);
	cout << "팩맨 설치 끝나면 Next / 이전으로 가려면 Back";
	gotoxy(85, 8);
	cout << "1.Back";
	gotoxy(85, 9);
	cout << "2.Next";
	gotoxy(85, 10);
	cout << "3.Main menu";
	while (1) {
		showMap(col, row);
		gotoxy(x + 52 - row, y + 5);
		CursorView2();
		a = _getch();
		CursorView();
		gotoxy(10, 4);
		cout << "                                              ";
		if (a == 87 || a == 119) {
			if (y + 4 >= start_y) {
				y--;
			}
		}
		else if (a == 83 || a == 115) {
			if (y + 6 <= end_y) {
				y++;
			}
		}
		else if (a == 65 || a == 97) {
			if (x + 50 - row >= start_x) {
				x = x - 2;
			}
		}
		else if (a == 68 || a == 100) {
			if (x + 54 - row <= end_x) {
				x = x + 2;
			}
		}
		else if (a == 32) {
			if (roundMap[y][x / 2 + 1] == '0' && flg == false) {
				roundMap[y][x / 2 + 1] = '2';
				::current_x = y;
				::current_y = x / 2 + 1;
				flg = true;
			}
			else if (roundMap[y][x / 2 + 1] == '2') {
				roundMap[y][x / 2 + 1] = '0';
				flg = false;
			}
		}
		else if (a == 51) {
			for (int i = 0; i < col; i++) {
				delete[] roundMap[i];
			}
			delete[] roundMap;

			return mainMenu();
		}
		else if (a == 50) {

			if (!flg) {
				gotoxy(10, 4);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout << "팩맨 위치를 지정하여 주세요";
			}
			else {
				return makeUseMapMonster(col, row);
			}
		}
		else if (a == 49) {
			if (flg) {
				roundMap[current_x][current_y] = '0';
			}
			return makeUseMapMap(col, row);
		}

	}
}

void makeUseMapMonster(int col, int row) {
	system("cls");
	gotoxy(46, 5);
	int num;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "몬스터 수 : ";
	cin >> num;
	system("cls");
	int x, y;
	x = 1;
	y = 1;
	int a;

	monsterArr = new int* [num];
	for (int i = 0; i < num; i++) {
		monsterArr[i] = new int[2];
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	gotoxy(10, 0);
	cout << "몬스터 위치 지정";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(10, 1);
	cout << "방향키로 이동";
	gotoxy(10, 2);
	cout << "스페이스바로 팩맨 설치 / 삭제";
	gotoxy(10, 3);
	cout << "몬스터 설치 끝나면 Next / 이전으로 가려면 Back";
	gotoxy(85, 8);
	cout << "1.Back";
	gotoxy(85, 9);
	cout << "2.Next";
	gotoxy(85, 10);
	cout << "3.Main menu";
	int count = 0;
	while (1) {
		showMap(col, row);
		gotoxy(x + 52 - row, y + 5);
		CursorView2();
		a = _getch();
		CursorView();
		gotoxy(10, 4);
		cout << "                                              ";
		if (a == 87 || a == 119) {
			if (y + 4 >= start_y) {
				y--;
			}
		}
		else if (a == 83 || a == 115) {
			if (y + 6 <= end_y) {
				y++;
			}
		}
		else if (a == 65 || a == 97) {
			if (x + 50 - row >= start_x) {
				x = x - 2;
			}
		}
		else if (a == 68 || a == 100) {
			if (x + 54 - row <= end_x) {
				x = x + 2;
			}
		}
		else if (a == 32) {
			if (roundMap[y][x / 2 + 1] == '0' && count != num) {
				roundMap[y][x / 2 + 1] = '4';
				monsterArr[count][0] = y;
				monsterArr[count][1] = x / 2 + 1;
				count++;
			}
			else if (roundMap[y][x / 2 + 1] == '4') {
				roundMap[y][x / 2 + 1] = '0';
				count--;
			}
		}
		else if (a == 51) {
			for (int i = 0; i < col; i++) {
				delete[] roundMap[i];
			}
			delete[] roundMap;

			for (int i = 0; i < num; i++) {
				delete[] monsterArr[i];
			}
			delete[] monsterArr;

			return mainMenu();
		}
		else if (a == 50) {
			if (count != num) {
				gotoxy(10, 4);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout << "몬스터 개수가 부족합니다";
			}
			else {
				return makeUseMapSet(col, row, num);
			}
		}
		else if (a == 49) {
			for (int i = 0; i < count; i++) {
				roundMap[monsterArr[i][0]][monsterArr[i][1]] = '0';
			}
			for (int i = 0; i < num; i++) {
				delete[] monsterArr[i];
			}
			delete[] monsterArr;
			return makeUseMapPacman(col, row, true);
		}
	}
}

void makeUseMapSet(int col, int row, int num) {
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	int speed;
	gotoxy(26, 2);
	cout << "참고 : round1의 속도 130, round2의 속도 90, round3의 속도 60";
	gotoxy(26, 3);
	cout << "숫자가 낮을수록 빠름";
	gotoxy(46, 5);
	cout << "Speed(1~500): ";
	cin >> speed;



	for (int i = 0; i < useMapColume; i++) {
		delete[] useMap[i];
	}

	delete[] useMap;

	for (int i = 0; i < useMapMonsterNum; i++) {
		delete[] useMapMonsterArr[i];
	}
	delete[] useMapMonsterArr;

	::useMapRow = row;
	::useMapColume = col;
	::useMapMonsterNum = num;

	::useMapStartX = start_x;
	::useMapStartY = start_y;
	::useMapEndX = end_x;
	::useMapEndY = end_y;

	::useMapCurrentX = current_x;
	::useMapCurrentY = current_y;

	::useMapSpeed = speed;

	useMap = new char* [useMapColume];
	for (int i = 0; i < useMapColume; i++) {
		useMap[i] = new char[useMapRow + 1];
	}

	for (int i = 0; i < useMapColume; i++) {
		for (int j = 0; j < useMapRow; j++) {
			useMap[i][j] = roundMap[i][j];
		}
	}


	useMapMonsterArr = new int* [useMapMonsterNum];
	for (int i = 0; i < useMapMonsterNum; i++) {
		useMapMonsterArr[i] = new int[2];
	}
	for (int i = 0; i < useMapMonsterNum; i++) {
		useMapMonsterArr[i][0] = monsterArr[i][0];
		useMapMonsterArr[i][1] = monsterArr[i][1];
	}

	for (int i = 0; i < useMapColume; i++) {
		delete[] roundMap[i];
	}

	delete[] roundMap;

	for (int i = 0; i < useMapMonsterNum; i++) {
		delete[] monsterArr[i];
	}
	delete[] monsterArr;

	return mainMenu();
}


// 게임 플레이 요소
void showMap(const int x, const int y) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(80, 4);
	cout << "방향키 : Q W E R";
	for (int row = 0; row < x; row++) { 
		gotoxy(start_x-2, start_y-1 + row);
		for (int col = 0; col < y; col++) {
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
			else if(roundMap[row][col] == '9'){
				cout << "  "; //공백
			}
			else if (roundMap[row][col] == '3') {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout << "★"; //몬스터 -> 공백
			}
			else if (roundMap[row][col] == '4') {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout << "★"; //몬스터  -> 코인
			}
		}
		cout << '\n';
	}
}

bool checkMap(const int x, const int y) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			if (roundMap[i][j] == '0') {
				return false;
			}
		}
	}
	return true;
}

bool movePacMan(const int x, const int y) {
	char a;
	if (_kbhit()) {
		a = _getch();
	}
	else {
		a = head;
	}

	switch (a) {
	case 'w':
	case 'W':
		if ((current_x - 1) >= 1) {
			if (roundMap[current_x - 1][current_y] == '0' || roundMap[current_x - 1][current_y] == '9') {
				roundMap[current_x][current_y] = '9';
				current_x--;
				roundMap[current_x][current_y] = '2';
				head = 'w';
			}
			else if (roundMap[current_x - 1][current_y] == '3' || roundMap[current_x - 1][current_y] == '4') {
				return false;
			}
		}
		break;
	case 's':
	case 'S':
		if ((current_x + 1) <= (x - 1)) {
			if (roundMap[current_x + 1][current_y] == '0' || roundMap[current_x + 1][current_y] == '9') {
				roundMap[current_x][current_y] = '9';
				current_x++;
				roundMap[current_x][current_y] = '2';
				head = 's';
			}
			else if (roundMap[current_x + 1][current_y] == '3' || roundMap[current_x + 1][current_y] == '4') {
				return false;
			}
		}
		break;
	case 'a':
	case 'A':
		if ((current_y - 1) >= 1) {
			if (roundMap[current_x][current_y - 1] == '0' || roundMap[current_x][current_y - 1] == '9') {
				roundMap[current_x][current_y] = '9';
				current_y--;
				roundMap[current_x][current_y] = '2';
				head = 'a';
			}
			else if (roundMap[current_x][current_y - 1] == '3' || roundMap[current_x][current_y - 1] == '4') {
				return false;
			}
		}
		break;
	case 'd':
	case 'D':
		if ((current_y + 1) <= (y - 1)) {
			if (roundMap[current_x][current_y + 1] == '0' || roundMap[current_x][current_y + 1] == '9') {
				roundMap[current_x][current_y] = '9';
				current_y++;
				roundMap[current_x][current_y] = '2';
				head = 'd';
			}
			else if (roundMap[current_x][current_y + 1] == '3' || roundMap[current_x][current_y + 1] == '4') {
				return false;
			}
		}
		break;
	default:
		break;
	}
	return true;
}

bool moveMonster(const int x, const int y) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 3);
	for (int i = 0; i < monsterNum; i++) {
		int repeatCount = 0;
		while (1) {
			repeatCount++;
			if (repeatCount == 50) {
				break;
			}
			int a = dis(gen);
			if (a == 0) {
				if ((monsterArr[i][0] - 1) >= 1) {
					if (roundMap[monsterArr[i][0] - 1][monsterArr[i][1]] == '0' || roundMap[monsterArr[i][0] - 1][monsterArr[i][1]] == '9') {
						if (roundMap[monsterArr[i][0]][monsterArr[i][1]] == '3') {
							roundMap[monsterArr[i][0]][monsterArr[i][1]] = '9';
							monsterArr[i][0]--;
							if (roundMap[monsterArr[i][0]][monsterArr[i][1]] == '0') {
								roundMap[monsterArr[i][0]][monsterArr[i][1]] = '4';
							}
							else {
								roundMap[monsterArr[i][0]][monsterArr[i][1]] = '3';
							}

						}
						else {
							roundMap[monsterArr[i][0]][monsterArr[i][1]] = '0';
							monsterArr[i][0]--;
							if (roundMap[monsterArr[i][0]][monsterArr[i][1]] == '0') {
								roundMap[monsterArr[i][0]][monsterArr[i][1]] = '4';
							}
							else {
								roundMap[monsterArr[i][0]][monsterArr[i][1]] = '3';
							}
						}
						break;
					}
					else if (roundMap[monsterArr[i][0] - 1][monsterArr[i][1]] == '2') {
						return false;
					}
				}
			}
			else if (a == 1) {
				if ((monsterArr[i][0] + 1) <= (x - 1)) {
					if (roundMap[monsterArr[i][0] + 1][monsterArr[i][1]] == '0' || roundMap[monsterArr[i][0] + 1][monsterArr[i][1]] == '9') {
						if (roundMap[monsterArr[i][0]][monsterArr[i][1]] == '3') {
							roundMap[monsterArr[i][0]][monsterArr[i][1]] = '9';
							monsterArr[i][0]++;
							if (roundMap[monsterArr[i][0]][monsterArr[i][1]] == '0') {
								roundMap[monsterArr[i][0]][monsterArr[i][1]] = '4';
							}
							else {
								roundMap[monsterArr[i][0]][monsterArr[i][1]] = '3';
							}

						}
						else {
							roundMap[monsterArr[i][0]][monsterArr[i][1]] = '0';
							monsterArr[i][0]++;
							if (roundMap[monsterArr[i][0]][monsterArr[i][1]] == '0') {
								roundMap[monsterArr[i][0]][monsterArr[i][1]] = '4';
							}
							else {
								roundMap[monsterArr[i][0]][monsterArr[i][1]] = '3';
							}
						}
						break;
					}
					else if (roundMap[monsterArr[i][0] + 1][monsterArr[i][1]] == '2') {
						return false;
					}
				}
			}
			else if (a == 2) {
				if ((monsterArr[i][1] - 1) >= 1) {
					if (roundMap[monsterArr[i][0]][monsterArr[i][1] - 1] == '0' || roundMap[monsterArr[i][0]][monsterArr[i][1] - 1] == '9') {
						if (roundMap[monsterArr[i][0]][monsterArr[i][1]] == '3') {
							roundMap[monsterArr[i][0]][monsterArr[i][1]] = '9';
							monsterArr[i][1]--;
							if (roundMap[monsterArr[i][0]][monsterArr[i][1]] == '0') {
								roundMap[monsterArr[i][0]][monsterArr[i][1]] = '4';
							}
							else {
								roundMap[monsterArr[i][0]][monsterArr[i][1]] = '3';
							}

						}
						else {
							roundMap[monsterArr[i][0]][monsterArr[i][1]] = '0';
							monsterArr[i][1]--;
							if (roundMap[monsterArr[i][0]][monsterArr[i][1]] == '0') {
								roundMap[monsterArr[i][0]][monsterArr[i][1]] = '4';
							}
							else {
								roundMap[monsterArr[i][0]][monsterArr[i][1]] = '3';
							}
						}
						break;
					}
					else if (roundMap[monsterArr[i][0]][monsterArr[i][1] - 1] == '2') {
						return false;
					}
				}
			}
			else if (a == 3) {
				if ((monsterArr[i][1] + 1) <= (y - 1)) {
					if (roundMap[monsterArr[i][0]][monsterArr[i][1] + 1] == '0' || roundMap[monsterArr[i][0]][monsterArr[i][1] + 1] == '9') {
						if (roundMap[monsterArr[i][0]][monsterArr[i][1]] == '3') {
							roundMap[monsterArr[i][0]][monsterArr[i][1]] = '9';
							monsterArr[i][1]++;
							if (roundMap[monsterArr[i][0]][monsterArr[i][1]] == '0') {
								roundMap[monsterArr[i][0]][monsterArr[i][1]] = '4';
							}
							else {
								roundMap[monsterArr[i][0]][monsterArr[i][1]] = '3';
							}
						}
						else {
							roundMap[monsterArr[i][0]][monsterArr[i][1]] = '0';
							monsterArr[i][1]++;
							if (roundMap[monsterArr[i][0]][monsterArr[i][1]] == '0') {
								roundMap[monsterArr[i][0]][monsterArr[i][1]] = '4';
							}
							else {
								roundMap[monsterArr[i][0]][monsterArr[i][1]] = '3';
							}
						}
						break;
					}
					else if (roundMap[monsterArr[i][0]][monsterArr[i][1] - 1] == '2') {
						return false;
					}
				}
			}

		}
	}
	return true;
}

void countDown() {
	system("cls");

	gotoxy(80, 4);
	cout << "방향키 : Q W E R";
	gotoxy(47, 10);
	cout << " _____ ";
	gotoxy(47, 11);
	cout << "|____ |";
	gotoxy(47, 12);
	cout << "    / /";
	gotoxy(47, 13);
	cout << "    ＼＼";
	gotoxy(47, 14);
	cout << ".___/  /";
	gotoxy(47, 15);
	cout << "＼____/ ";
	Sleep(1000);

	system("cls");

	gotoxy(80, 4);
	cout << "방향키 : Q W E R";
	gotoxy(47, 10);
	cout << "  _____ ";
	gotoxy(47, 11);
	cout << " / __ ＼";
	gotoxy(47, 12);
	cout << " `' / /'";
	gotoxy(47, 13);
	cout << "   / /  ";
	gotoxy(47, 14);
	cout << " ./ /___";
	gotoxy(47, 15);
	cout << "＼_____/";
	Sleep(1000);
	system("cls");

	gotoxy(80, 4);
	cout << "방향키 : Q W E R";
	gotoxy(47, 10);
	cout << "  __  ";
	gotoxy(47, 11);
	cout << " /  | ";
	gotoxy(47, 12);
	cout << " `| | ";
	gotoxy(47, 13);
	cout << "  | | ";
	gotoxy(47, 14);
	cout << " _| |_";
	gotoxy(47, 15);
	cout << "＼___/";
	Sleep(1000);
}

int successGame() {
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(46, 3);
	cout << "Succeess";
	gotoxy(70, 8);
	cout << "1.Next level";
	gotoxy(70, 9);
	cout << "2.Main menu";
	gotoxy(70, 10);
	cout << "3.Scoreboad";
	gotoxy(70, 11);
	cout << "4.Exit";

	bool checkMenu = true;
	while (checkMenu) {
		checkMenu = false;
		int inputNum = _getch();
		switch (inputNum) {
		case 49:
			return 1;
			break;
		case 50:
			return 2;
			break;
		case 51:
			return 3;
			break;
		case 52:
			return 4;
			break;
		default:
			checkMenu = true;
		}
	}
	return 1;
}

int failGame() {
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(48, 3);
	cout << "Fail";
	gotoxy(70, 8);
	cout << "1.Play again";
	gotoxy(70, 9);
	cout << "2.Main menu";
	gotoxy(70, 10);
	cout << "3.Scoreboad";
	gotoxy(70, 11);
	cout << "4.Exit";

	bool checkMenu = true;
	while (checkMenu) {
		checkMenu = false;
		int inputNum = _getch();
		switch (inputNum) {
		case 49:
			return 1;
			break;
		case 50:
			return 2;
			break;
		case 51:
			return 3;
			break;
		case 52:
			return 4;
			break;
		default:
			checkMenu = true;
		}
	}
	return 1;
}

// select menu
void round1() {
	countDown();
	clock_t start_clk = clock();
	system("cls");
	setRound1Map(roundMap);
	setRound1Monster(monsterArr);
	showMap(11, 20);
	while (1) {
		if (!movePacMan(11, 20)) {
			for (int i = 0; i < 11; i++) {
				delete[] roundMap[i];
			}
			delete[] roundMap;

			for (int i = 0; i < 2; i++) {
				delete[] monsterArr[i];
			}
			delete[] monsterArr;

			int a = failGame();
			if (a == 1) {
				return round1();
			}
			else if (a == 2) {
				return mainMenu();
			}
			else if (a == 3) {
				return scoreBoard();
			}
			else {
				return exit_game();
			}
			break;
		};
		if (!moveMonster(11, 20)) {

			for (int i = 0; i < 11; i++) {
				delete[] roundMap[i];
			}
			delete[] roundMap;

			for (int i = 0; i < 2; i++) {
				delete[] monsterArr[i];
			}
			delete[] monsterArr;

			int a = failGame();
			if (a == 1) {
				return round1();
			}
			else if (a == 2) {
				return mainMenu();
			}
			else if (a == 3) {
				return scoreBoard();
			}
			else {
				return exit_game();
			}
			break;
		}
		showMap(11, 20);
		if (checkMap(11, 20)) {

			for (int i = 0; i < 11; i++) {
				delete[] roundMap[i];
			}
			delete[] roundMap;

			for (int i = 0; i < 2; i++) {
				delete[] monsterArr[i];
			}
			delete[] monsterArr;

			clock_t end_clk = clock();

			system("cls");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			gotoxy(46, 3);
			cout << "Succeess";
			gotoxy(40, 6);
			cout << "Write your name! : ";
			string s;
			cin >> s;

			ofstream os;
			os.open("scoresheet1.txt", ios::app);
			double interval = (end_clk - start_clk) / CLOCKS_PER_SEC;
			os << s << ' ' << interval << '\n';
			os.close();

			int a = successGame();
			if (a == 1) {
				return round2();
			}
			else if (a == 2) {
				return mainMenu();
			}
			else if (a == 3) {
				return scoreBoard();
			}
			else {
				return exit_game();
			}
			break;
		}
		Sleep(130);
	}
}

void round2() {
	countDown();
	clock_t start_clk = clock();
	system("cls");
	setRound2Map(roundMap);
	setRound2Monster(monsterArr);
	showMap(11, 20);
	while (1) {
		if (!movePacMan(11, 20)) {
			for (int i = 0; i < 11; i++) {
				delete[] roundMap[i];
			}
			delete[] roundMap;

			for (int i = 0; i < 3; i++) {
				delete[] monsterArr[i];
			}
			delete[] monsterArr;

			int a = failGame();
			if (a == 1) {
				return round2();
			}
			else if (a == 2) {
				return mainMenu();
			}
			else if (a == 3) {
				return scoreBoard();
			}
			else {
				return exit_game();
			}
			break;
		};
		if (!moveMonster(11, 20)) {

			for (int i = 0; i < 11; i++) {
				delete[] roundMap[i];
			}
			delete[] roundMap;

			for (int i = 0; i < 3; i++) {
				delete[] monsterArr[i];
			}
			delete[] monsterArr;

			int a = failGame();
			if (a == 1) {
				return round2();
			}
			else if (a == 2) {
				return mainMenu();
			}
			else if (a == 3) {
				return scoreBoard();
			}
			else {
				return exit_game();
			}
			break;
		}
		showMap(11, 20);
		if (checkMap(11, 20)) {

			for (int i = 0; i < 11; i++) {
				delete[] roundMap[i];
			}
			delete[] roundMap;

			for (int i = 0; i < 3; i++) {
				delete[] monsterArr[i];
			}
			delete[] monsterArr;

			clock_t end_clk = clock();

			system("cls");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			gotoxy(46, 3);
			cout << "Succeess";
			gotoxy(40, 6);
			cout << "Write your name! : ";
			string s;
			cin >> s;

			ofstream os;
			os.open("scoresheet2.txt", ios::app);
			double interval = (end_clk - start_clk) / CLOCKS_PER_SEC;
			os << s << ' ' << interval << '\n';
			os.close();

			int a = successGame();
			if (a == 1) {
				return round3();
			}
			else if (a == 2) {
				return mainMenu();
			}
			else if (a == 3) {
				return scoreBoard();
			}
			else {
				return exit_game();
			}
			break;
		}
		Sleep(90);
	}
}

void round3() {
	countDown();
	clock_t start_clk = clock();
	system("cls");
	setRound3Map(roundMap);
	setRound3Monster(monsterArr);
	showMap(21, 28);
	while (1) {
		if (!movePacMan(21, 28)) {
			for (int i = 0; i < 21; i++) {
				delete[] roundMap[i];
			}
			delete[] roundMap;

			for (int i = 0; i < 4; i++) {
				delete[] monsterArr[i];
			}
			delete[] monsterArr;

			int a = failGame();
			if (a == 1) {
				return round3();
			}
			else if (a == 2) {
				return mainMenu();
			}
			else if (a == 3) {
				return scoreBoard();
			}
			else {
				return exit_game();
			}
			break;
		};
		if (!moveMonster(21, 28)) {

			for (int i = 0; i < 21; i++) {
				delete[] roundMap[i];
			}
			delete[] roundMap;

			for (int i = 0; i < 4; i++) {
				delete[] monsterArr[i];
			}
			delete[] monsterArr;

			int a = failGame();
			if (a == 1) {
				return round3();
			}
			else if (a == 2) {
				return mainMenu();
			}
			else if (a == 3) {
				return scoreBoard();
			}
			else {
				return exit_game();
			}
			break;
		}
		showMap(21, 28);
		if (checkMap(21, 28)) {

			for (int i = 0; i < 21; i++) {
				delete[] roundMap[i];
			}
			delete[] roundMap;

			for (int i = 0; i < 4; i++) {
				delete[] monsterArr[i];
			}
			delete[] monsterArr;

			clock_t end_clk = clock();

			system("cls");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			gotoxy(46, 3);
			cout << "Succeess";
			gotoxy(40, 6);
			cout << "Write your name! : ";
			string s;
			cin >> s;

			ofstream os;
			os.open("scoresheet3.txt", ios::app);
			double interval = (end_clk - start_clk) / CLOCKS_PER_SEC;
			os << s << ' ' << interval << '\n';
			os.close();

			int a = successGame();
			if (a == 1) {
				return mainMenu();
			}
			else if (a == 2) {
				return mainMenu();
			}
			else if (a == 3) {
				return scoreBoard();
			}
			else {
				return exit_game();
			}
			break;
		}
		Sleep(60);
	}
}

void scoreBoard() {
	system("cls");
	ifstream is;

	gotoxy(45, 3);
	cout << "Scoreboard";
	gotoxy(24, 7);
	cout << "1st";
	gotoxy(24, 8);
	cout << "2nd";
	gotoxy(24, 9);
	cout << "3rd";
	gotoxy(24, 10);
	cout << "4th";
	gotoxy(24, 11);
	cout << "5th";

	is.open("scoresheet1.txt");
	string s;
	int a;
	vector<pair<string,int>> v;
	int count = 0;
	while (!is.eof()) {
		count++;
		is >> s >> a;
		v.push_back({ s,a });
	}
	is.close();
	sort(v.begin(), v.end(), compare);
	int len = min(count - 1, 5);
	
	ofstream os;
	os.open("scoresheet1.txt");
	gotoxy(33, 5);
	cout << "Round1";
	for (int i = 0; i < len; i++) {
		gotoxy(30, 7 + i);
		os << v[i].first << ' ' << v[i].second << '\n';
		
		cout << setw(5) << v[i].first << ' ' << v[i].second;
	}
	os.close();

	v.clear();

	is.open("scoresheet2.txt");
	count = 0;
	while (!is.eof()) {
		count++;
		is >> s >> a;
		v.push_back({ s,a });

	}
	is.close();
	sort(v.begin(), v.end(), compare);
	len = min(count - 1, 5);

	os.open("scoresheet2.txt");
	gotoxy(47, 5);
	cout << "Round2";
	for (int i = 0; i < len; i++) {
		gotoxy(45, 7 + i);
		os << v[i].first << ' ' << v[i].second << '\n';
		cout << setw(5) << v[i].first << ' ' << v[i].second;
	}
	os.close();

	v.clear();

	is.open("scoresheet3.txt");
	count = 0;
	while (!is.eof()) {
		count++;
		is >> s >> a;
		v.push_back({ s,a });
	}
	is.close();
	sort(v.begin(), v.end(), compare);
	len = min(count - 1, 5);

	os.open("scoresheet3.txt");
	gotoxy(62, 5);
	cout << "Round3";
	for (int i = 0; i < len; i++) {
		gotoxy(60, 7 + i);
		os << v[i].first << ' ' << v[i].second << '\n';
		cout << setw(5) << v[i].first << ' ' << v[i].second;
	}
	os.close();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(80, 11);
	cout << "1.Main menu";
	gotoxy(80, 12);
	cout << "2.Exit";

	bool checkMenu = true;
	while (checkMenu) {
		checkMenu = false;
		int inputNum = _getch();
		switch (inputNum) {
		case 49:
			return mainMenu();
			break;
		case 50:
			return exit_game();
			break;

		default:
			checkMenu = true;
		}
	}
}

void exit_game() {
	exit(0);
}

void mainMenu() {
	CursorView();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	system("cls");
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

	if (useMapColume == 0) {
		gotoxy(70, 12);
		cout << "5.Make use map";
		gotoxy(70, 13);
		cout << "6.Exit";
		bool checkMenu = true;
		while (checkMenu) {
			checkMenu = false;
			int inputNum = _getch();
			switch (inputNum) {
			case 49:
				return round1();
				break;
			case 50:
				return round2();
				break;
			case 51:
				return round3();
				break;
			case 52:
				return scoreBoard();
			case 53:
				return makeUseMapStart();
			case 54:
				return exit_game();
				break;
			default:
				checkMenu = true;
			}
		}
	}
	else {
		gotoxy(70, 12);
		cout << "5.Change use map";
		gotoxy(70, 13);
		cout << "6.Play use map";
		gotoxy(70, 14);
		cout << "7.Exit";
		bool checkMenu = true;
		while (checkMenu) {
			checkMenu = false;
			int inputNum = _getch();
			switch (inputNum) {
			case 49:
				return round1();
				break;
			case 50:
				return round2();
				break;
			case 51:
				return round3();
				break;
			case 52:
				return scoreBoard();
			case 53:
				return makeUseMapStart();
			case 54:
				return useMapStart();
				break;
			case 55:
				return exit_game();
				break;
			default:
				checkMenu = true;
			}
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
		return;
	}
}

int main() {
	CursorView();
	system(" mode  con lines=30   cols=100 "); //콘솔창 크키 바꾸기
	startMenu(); //Pac-Man 출력
	mainMenu(); //선택화면 표시
}

