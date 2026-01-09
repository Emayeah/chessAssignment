#include <iostream>
#include "firme.h"
using namespace std;

int main() {
	int board[64]; // board, monodimensional array
	int color = 0;
	initBoard(board);
	printBoard(board, color);
}

void initBoard(int board[]) {
	short temp = 3;
	for (int i = 0; i < 8; i++) {
		board[i + 8] = 6;
		board[i + 6*8] = 12;
	}
	for (int i = 0; i < 8; i++) {
		board[i] = temp;
		board[i + 8*7] = temp + 6;
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
			}
			else {
				cout << '\xe2' << '\x99' << (char)(board[8 - j + (8 * (7 - i))] + 147);
			}
		}
		cout << endl;
	}
}
