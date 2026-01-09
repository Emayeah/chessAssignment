
#include <iostream>
#include "firme.h"
using namespace std;
int pos, npos, x, y, nx, ny;
// pawn = 6
// king = 1
// knight = 5
// bishop = 4
// rook = 3

int main() {
	int board[64]; // board, monodimensional array, i could make it global and bidimensional but monodimensional is just easier with less breaking potential
	initBoard(board);
	int color = 0;
	int move;
	char win = 'x';
	do {
		do {
			printBoard(board, color);
			userInput(board, color);
			if (board[pos] == 5 + 6 * color) {
				move = knight(x - nx, y - ny);
			}
			else if (board[pos] == 6 + 6 * color) {
				move = pawn(board, color, nx - x, ny - y);
			}
			else if (board[pos] == 3 + 6 * color) {
				move = rook(board, nx - x, ny - y);
			}
			else if (board[pos] == 4 + 6 * color) {
				move = bishop(board, nx - x, ny - y);
			}
			else if (board[pos] == 2 + 6 * color) {
				move = queen(board, nx - x, ny - y);
			}
			if (move == 0) {
				board[npos] = board[pos];
				board[pos] = 0;
			}
			else if (move == 1) {
				cout << "Invalid move\n";
			}
		} while (move == 1);
		color++;
		color %= 2;
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
		if (i == 0 || i == 5) {
			temp = 5;
		}
		else if (i == 1 || i == 4) {
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
		if (color == 0) {
			cout << 8 - i;
		}
		else {
			cout << i + 1;
		}
		cout << "  ";
		for (int j = 7; j >= 0; j--) {
			if (color == 1) {
				if (board[j + 8 * i] == 0) {
					cout << "__|";
				}
				else {
					cout << '\xe2' << '\x99' << (char)(board[j + 8 * i] + 147);
					cout << " |";
				}
			}
			else {
				if (board[63 - (j + 8 * i)] == 0) {
					cout << "__|";
				}
				else {
					cout << '\xe2' << '\x99' << (char)(board[63 - (j + 8 * i)] + 147);
					cout << " |";
				}
			}
		}
		cout << endl;
	}
	cout << "   ";
	for (int i = 0; i < 8; i++) {
		if (color == 0) {
			cout << (char)('a' + i) << " |";
		}
		else {
			cout << (char)('a' + (7 - i)) << " |";
		}
	}
	cout << endl;
}

void userInput(int board[], int color) {
	int flag;
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
			pos = x + 8 * y;
			if ((x >= 0 && x <= 7 && y >= 0) && (board[pos] <= 6 + 6 * color && board[pos] > 6 * color)) {
				do {
					flag = 1;
					cout << "Insert landing spot (x to cancel): ";
					cin >> input;
					if (input[0] != 'x') {
						if (input[0] < 97) {
							input[0] += 32;
						}
						nx = input[0] -= 97;
						if (input[1] < 57) {
							ny = input[1] -= 49;
							npos = nx + 8 * ny;
							if ((nx >= 0 && nx <= 7 && ny >= 0) && ((board[npos] <= 12 - 6 * color && board[npos] > 6 - 6 * color) || board[npos] == 0)) {
								flag = 0;
							}
						}
						if (flag) {
							cout << "Invalid landing spot\n";
						}
					}
					else {
						flag = 2;
					}
				} while (flag == 1);
			}
			else {
				flag = 1;
			}
		}
		else {
			flag = 1;
		}
		if (flag == 1) {
			cout << "Invalid piece selection\n";
		}
	} while (flag == 1 || flag == 2);
}

int knight(int x2, int y2) {
	if (x2 < 0) {
		x2 *= -1;
	}
	if (y2 < 0) {
		y2 *= -1;
	}
	if (x2 == 1 && y2 == 2) {
		return 0;
	}
	if (x2 == 2 && y2 == 1) {
		return 0;
	}
	return 1;
}

int pawn(int board[], int color, int x2, int y2) {
	if (x2 == 0 && board[npos] == 0) {
		if (y2 == 1 + -2 * color) { // classic one forward
			return 0;
		}
		else if (y2 == 2 + -4 * color && y == 1 + 5 * color && board[npos - 8 + 8 * (2 * color)] == 0) { // 2 forward
			return 0;
		}
	}
	else if ((x2 == 1 || x2 == -1) && (board[npos] <= 12 - 6 * color && board[npos] > 6 - 6 * color)) {
		if (y2 == 1 + -2 * color) {
			if (pos + 8 - 8 * (2 * color) + y2 - (2 * y2 * color) == npos) {
				return 0;
			}
		}
	}
	return 1;
}

int rook(int board[], int x2, int y2) {
	int flag = 1;
	if (x2 == 0) {
		if (y2 < 0) {
			flag = -1;
			y2 *= -1;
		}
		for (int i = 1; i < y2; i++) {
			if (board[pos + (8 * i * flag)] != 0) {
				return 1;
			}
		}
		return 0;
	}
	else if (y2 == 0) {
		if (x2 < 0) {
			flag = -1;
			x2 *= -1;
		}

		for (int i = 1; i < x2; i++) {
			if (board[pos + (i * flag)] != 0) {
				return 1;
			}
		}
		return 0;
	}
	return 1;
}

int bishop(int board[], int x2, int y2) {
	int flag = 1, flag2 = 1;
	if (x2 < 0) {
		flag = -1;
		x2 *= -1;
	}
	if (y2 < 0) {
		flag2 = -1;
		y2 *= -1;
	}
	if (x2 == y2) {
		for (int i = 1; i < x2; i++) {
			if (board[pos + (i * flag) + (8 * i * flag2)] != 0) {
				return 1;
			}
		}
		return 0;
	}
	return 1;
}

int queen(int board[], int x2, int y2) {
	int move = rook(board, x2, y2);
	if (move == 1) {
		move = bishop(board, x2, y2);
	}
	return move;
}
