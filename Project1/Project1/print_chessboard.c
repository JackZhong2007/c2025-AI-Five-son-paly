#include"print_chessboard.h"
#include"head_title_library.h"
#include"struct_library.h"
void print_chessboard(SPACE chessboard[15][15]) {
	system("cls");
	printf("   ");
	for (int i = 0; i < LENGTH; i++) {
		if (i < 10) {
			printf(" %d ", i);
		}
		else {
			printf("%d ", i);
		}
	}
	printf("\n");
	for (int i = 0; i < LENGTH; i++) {
		if (i < 10) {
			printf(" %d ", i);
		}
		else {
			printf("%d ", i);
		}
		for (int j = 0; j < LENGTH; j++) {
			if (chessboard[i][j].belong == BLACK) {
				printf(" ¡ñ ");
			}
			else if (chessboard[i][j].belong == WHITE) {
				printf(" ¡ð ");
			}
			else {
				printf(" + ");
			}
		}
		printf("\n");
	}
}