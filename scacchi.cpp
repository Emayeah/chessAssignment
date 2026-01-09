#include <iostream>
#include "firme.h"
using namespace std;

int main() {
	int board[64]; // board, monodimensional array
	initBoard(board);
	int color = 0;
	char win = 'a';
	do {
		printBoard(board, color);
		userInput(board, color);
		
	} while (win == 'x');
}

void initBoard(int board[]) {
	short temp = 3;
	for (int i = 0; i < 8; i++) {
		board[i + 8] = 6;
		board[i + 6*8] = 12;
	}
	for (int i = 0; i < 8; i++) {
		board[i] = temp;
		board[i + 8 * 7] = temp + 6;
		if (i == 0 || i == 6) {
			temp = 5;
		}
		else if (i == 1 || i == 5) {
			temp = 4;
		}
		else if (i == 2) {
			temp = 2;
		}
		else if (i == 3) {
			temp = 1;
		}
		else {
			temp = 3;
		}
	}
	for (int i = 16; i < 48; i++) {
		board[i] = 0;
	}
}

void printBoard(int board[], int color) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[j + 8 * i] == 0) {
				cout << "__|";
			}
			else if (color == 0) {
				cout << '\xe2' << '\x99' << (char)(board[j + 8 * i] + 147);
				cout << " |";
			}
			else {
				cout << '\xe2' << '\x99' << (char)(board[8 - j + (8 * (7 - i))] + 147);
				cout << " |";
			}
		}
		cout << endl;
	}
}

void userInput(int board[], int color) {
	int x, y, nx, ny, flag;
	char input[3];
	do {
		flag = 0;
		if (color) {
			cout << "Black: ";
		}
		else {
			cout << "White: ";
		}
		cout << "Insert piece to move: ";
		cin >> input;
		if (input[0] < 97) {
			input[0] += 32;
		}
		x = input[0] -= 97;
		if (input[1] < 57) {
			y = input[1] -= 49;
//			cout << board[x + 8 * y];
			if ((x >= 0 && x <= 7 && y >= 0) && (board[x + 8 * y] <= 6 + 6 * color && board[x + 8 * y] > 6 * color)) {
				do {
					flag = 1;
					cout << "Insert landing spot: ";
					cin >> input;
					if (input[0] < 97) {
						input[0] += 32;
					}
					nx = input[0] -= 97;
					if (input[1] < 57) {
						color++;
						color %= 2;
						ny = input[1] -= 49;
						if ((nx >= 0 && nx <= 7 && ny >= 0) && (board[nx + 8 * ny] <= 6 + 6 * color && board[nx + 8 * ny] > 6 * color) || board[nx + 8 * ny] == 0) {
							flag = 0;
						}
					}
					if (flag) {
						cout << "Invalid landing spot\n";
						color--;
					}
				} while (flag);
			}
			else {
				flag = 1;
			}
		}
		else {
			flag = 1;
		}
		if (flag) {
			cout << "Invalid piece selection\n";
		}
	} while (flag);
}
