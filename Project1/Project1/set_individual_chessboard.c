#include"set_individual_chessboard.h"
#include"head_title_library.h"
#include"struct_library.h"
void set_individual_chessboard(SPACE chessboard[15][15]) {
	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			chessboard[i][j].x = i;
			chessboard[i][j].y = j;
			chessboard[i][j].belong = BLANK;
		}
	}
}