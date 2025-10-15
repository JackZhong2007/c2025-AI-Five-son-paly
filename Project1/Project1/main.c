#include"set_individual_chessboard.h"
#include"head_title_library.h"
#include"struct_library.h"
#include"print_chessboard.h"
#include"before_begin.h"
int main() {
	//TEST_5:人类开局随机获得先后手并告知，并直接进行一次落子(未进行无法落子情况检验）
	///*
	srand((unsigned int)time(NULL));
	int color = before_begin();
	SPACE chessboard[LENGTH][LENGTH];
	set_individual_chessboard(chessboard);
	print_chessboard(chessboard);
	int x, y;
	scanf_s("%d%d", &x, &y);
	human_player_play(x, y, chessboard,color);
	print_chessboard(chessboard);
	//*/
	return 0;
}