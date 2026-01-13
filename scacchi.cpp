#include <iostream>
#include "firme.h"
using namespace std;
int pos, npos, x, y, nx, ny, checkFlag, oppCheck, tempColor, oldColor, posbak, nposbak, promotion, pawnPos;
int board[64];
// pawn = 6
// king = 1
// knight = 5
// bishop = 4
// rook = 3

int main() {
	initBoard();
	int color = 0;
	int move, flag;
	int bak, nbak;
	char win = 'x';
	oppCheck = 0;
	do {
		do {
			promotion = 0;
			checkFlag = 0;
			printBoard(color);
			userInput(color);
			if (board[pos] == 5 + 6 * color) {
				move = knight(x - nx, y - ny);
			}
			else if (board[pos] == 6 + 6 * color) {
				move = pawn(color, nx - x, ny - y);
			}
			else if (board[pos] == 3 + 6 * color) {
				move = rook(nx - x, ny - y);
			}
			else if (board[pos] == 4 + 6 * color) {
				move = bishop(nx - x, ny - y);
			}
			else if (board[pos] == 2 + 6 * color) {
				move = queen(nx - x, ny - y);
			}
			else if (board[pos] == 1 + 6 * color) {
				move = king(nx - x, ny - y);
			}
			if (move == 0) {
				posbak = pos;
				nposbak = npos;
				bak = board[pos];
				nbak = board[npos];
				board[npos] = board[pos];
				board[pos] = 0;
			}
			else if (move == 1) {
				cout << "Invalid move\n";
			}
		} while (move == 1);
		if (board[npos] == 6 + 6 * color && npos / 8 == 8 - 8 * color) {
			promotion = 1;
			pawnPos = npos;
		}
		checkFlag = 1;
		tempColor = color + 1;
		tempColor %= 2;
		oldColor = color;
		flag = calcCheck(color);
		if (flag == 1) {
			cout << "Invalid move, results in check\n";
			color--;
			board[posbak] = bak;
			board[nposbak] = nbak;
		}
		else if (flag == 2) {
			oppCheck = 1;
		}
		else {
			oppCheck = 0;
			if (promotion == 1) {
				pawnPromotion();
			}
		}
		color++;
		color %= 2;
	} while (win == 'x');
}

void initBoard() {
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
	// dev testing
//	board[20] = 3;
//	board[39] = 4;
//	board[35] = 2;
//	board[42] = 6;
//	board[45] = 5;
}

void printBoard(int color) {
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

void userInput(int color) {
	int flag;
	char input[3];
	do {
		flag = 0;
		if (oppCheck == 1) {
			cout << "CHECK! ";
		}
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

int pawn(int color, int x2, int y2) {
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
			if (pos + 8 - 8 * (2 * color) + x2 == npos) {
				return 0;
			}
		}
	}
	return 1;
}

int rook(int x2, int y2) {
	int flag = 1;
	if (x2 == 0) {
		if (y2 < 0) {
			flag = -1;
			y2 *= -1;
		}
		for (int i = 1; i < y2 + checkFlag; i++) {
			if (checkFlag == 1 && board[pos + i * 8 * flag] == 1 + 6 * oldColor) {
				return 2;
			}
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
		for (int i = 1; i < x2 + checkFlag; i++) {
			if (checkFlag == 1 && board[pos + i * flag] == 1 + 6 * oldColor) {
				return 2;
			}
			if (board[pos + (i * flag)] != 0) {
				return 1;
			}
		}
		return 0;
	}
	return 1;
}

int bishop(int x2, int y2) {
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
		for (int i = 1; i < x2 + checkFlag; i++) {
			if (checkFlag == 1 && board[pos + (i * flag) + (8 * i * flag2)] == 1 + 6 * oldColor) {
				return 2;
			}
			if (board[pos + (i * flag) + (8 * i * flag2)] != 0) {
				return 1;
			}
		}
		return 0;
	}
	return 1;
}

int queen(int x2, int y2) {
	int move = rook(x2, y2);
	if (move == 1) {
		move = bishop(x2, y2);
	}
	return move;
}

int king(int x2, int y2) {
	if ((x2 == 0 || x2 == 1 || x2 == -1) && (y2 == 0 || y2 == 1 || y2 == -1)) {
		return queen(x2, y2);
	}
	return 0;
}

int calcCheck(int color) {
	int x2, y2, tempx, tempy, move, temp;
	temp = 1;
	for (int _ = 0; _ < 2 && move != 2; _++) {
		for (int i = 0; i < 64; i++) {
			pos = i;
			move = 0;
			x2 = i % 8;
			y2 = i / 8;
			if (board[pos] == 5 + 6 * tempColor) {
				move = knightCheck();
			}
			else if (board[pos] == 6 + 6 * tempColor) {
				move = pawnCheck();
			}
			else if (board[i] == 3 + 6 * tempColor) {
					//move = rook(board, tempx, tempy);
//					cout << i << endl;
				move = rookCheck();
			}
			else if (board[i] == 4 + 6 * tempColor) {
				move = bishopCheck();
/*				for (int j = 0; j < 4 && move != 2; j++) {
					if (j == 0) {
						tempx = 7 - x2;
						tempy = tempx;
					}
					else if (j == 1) {
						tempx = -7 + x2;
						tempy = tempx;
					}
					else if (j == 2) {
						tempy = 7 - y2;
						tempx = tempy;
					}
					else if (j == 3) {
						tempy = -7 + y2;
						tempx = tempy;
					}*/
					//move = bishop(board, tempx, tempy);
//					cout << i << endl;
				//}
//				move = bishop(board, nx - x, ny - y);
			}
			else if (board[pos] == 2 + 6 * tempColor) {
				move = queenCheck();
			}
			else if (board[pos] == 1 + 6 * tempColor) {
				move = kingCheck();
			}
			if (move == 2) {
				return temp;
			}
		}
		if (oppCheck != 1) {
			temp++;
			oldColor = tempColor;
			tempColor++;
			tempColor %= 2;
		}
	}
	return 0;
}

int bishopCheck() {
	int flag = 0, i;
	int temp, temp2;
	temp = pos % 8;
	temp2 = pos / 8;
	i = 1;
	while (temp + i < 7 && temp2 + i < 7 && board[pos + i + 8 * i] == 0) {
		i++;
		if (board[pos + i + 8 * i] == 1 + 6 * oldColor) {
			return 2;
		}
	}
	//board[pos + i + 8 * i] = 20;
	i = 1;
	while (temp + i < 7 && temp2 - i > 0 && board[pos + i - 8 * i] == 0) {
		i++;
		if (board[pos + i - 8 * i] == 1 + 6 * oldColor) {
			return 2;
		}
	}
	i = 1;
	while (temp - i > 0 && temp2 + i < 7 && board[pos - i + 8 * i] == 0) {
		i++;
		if (board[pos - i + 8 * i] == 1 + 6 * oldColor) {
			return 2;
		}
	}
	i = 1;
	while (temp - i > 0 && temp2 - i > 0 && board[pos - i - 8 * i] == 0) {
		i++;
		if (board[pos - i - 8 * i] == 1 + 6 * oldColor) {
			return 2;
		}
	}
	return 0;
}

int rookCheck() {
	int tempx, tempy, x2, y2, move;
	x2 = pos % 8;
	y2 = pos / 8;
	for (int j = 0; j < 4 && move != 2; j++) {
		if (j == 0) {
			tempx = 7 - x2;
			tempy = 0;
		}
		else if (j == 1) {
			tempx = -7 + x2;
		}
		else if (j == 2) {
			tempy = 7 - y2;
			tempx = 0;
		}
		else if (j == 3) {
			tempy = -7 + y2;
		}
		move = rook(tempx, tempy);
	}
	return move;
}

int queenCheck() {
	int move = 0;
	move = rookCheck();
	if (move != 2) {
		move = bishopCheck();
	}
	return move;
}

int pawnCheck() {
	int x2, y2;
	x2 = pos % 8;
	y2 = pos / 8;
	if (y2 != 7 - 7 * tempColor) {
		if (x2 != 7) {
			if (board[pos +1 + (8 - (16 * tempColor))] == 1 + 6 * oldColor) {
				return 2;
			}
		}
		if (x2 != 0) {
			if (board[pos - 1 + (8 - (16 * tempColor))] == 1 + 6 * oldColor) {
				return 2;
			}
		}
	}
	return 0;
}

int kingCheck() {
	int x2, y2;
	x2 = pos % 8;
	y2 = pos / 8;
	for (int i = -1; i < 1; i++) {
		for (int j = -1; j < 1; j++) {
			if (x2 + i > 0 && x2 + i < 7 && y2 + i > 0 && y2 + i < 7 && board[pos + i + 8 * j] == 1 + 6 * oldColor) {
				return 2;
			}
		}
	}
	return 0;
}

int knightCheck() {
	int x2, y2;
	x2 = pos % 8;
	y2 = pos / 8;
	for (int j = -2; j <= 2; j++) {
		if (j == 0) {
			j++;
		}
		for (int k = -2; k <= 2; k++) {
			if (k == 0) {
				k++;
			}
			if (x2 - j >= 0 && x2 + j < 8 && y2 - k >= 0 && y2 + k < 8) {
				if (board[pos + j + k * 8] == 1 + 6 * oldColor) {
					return 2;
				}
			}
		}
	}
	return 0;
}

void pawnPromotion() {
	int color = pawnPos / 8 + 1;
	color %= 2;
	int temp;
	do {
		cout	<< "Promotion!\n"
			<< "1) Queen\n"
			<< "2) Rook\n"
			<< "3) Bishop"
			<< "4) Knight";
		cin >> temp;
		if (temp > 4 || temp < 1) {
			cout << "Invalid option!\n";
		}
	} while (temp >= 1 && temp <= 4);
	temp++;
	board[pawnPos] = temp + 6 * color;
}
