#include"before_begin.h"
void console_individual() {
	HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorinfo;
	GetConsoleCursorInfo(hconsole, &cursorinfo);
	cursorinfo.bVisible = false;
	SetConsoleCursorInfo(hconsole, &cursorinfo);
}
int before_begin() {
	console_individual();
	printf("Welcome to Gobang Game!\n");
	printf("Rules:\n");
	printf("1. The game is played on a 15x15 grid.\n");
	printf("2. Players take turns placing their pieces (Black and White) on the intersections of the grid.\n");
	printf("3. The first player to align five of their pieces horizontally, vertically, or diagonally wins the game.\n");
	printf("4. If the board is filled without any player aligning five pieces, the game ends in a draw.\n");
	printf("5. To place a piece, enter the coordinates in the format: x y (e.g., 7 7 for the center of the board).\n");
	printf("Enjoy the game!\n");
	printf("Now,you will get your chess color randomly!\n");
	int random = rand() % 2;
	if (random == BLACK) {
		printf("You are Black! You go first!\n");
		Sleep(5000);
		return BLACK;
	}
	else {
		printf("You are White! You go second!\n");
		Sleep(5000);
		return WHITE;
	}
}
void set_individual_chessboard(SPACE chessboard[LENGTH][LENGTH]) {
	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			chessboard[i][j].x = i;
			chessboard[i][j].y = j;
			chessboard[i][j].belong = BLANK;
			chessboard[i][j].score = 0;
		}
	}
}