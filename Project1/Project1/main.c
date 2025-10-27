#include"set_individual_chessboard.h"
#include"head_title_library.h"
#include"struct_library.h"
#include"print_chessboard.h"
#include"before_begin.h"
#include"human_player_play.h"
#include"victory_condition.h"
int main() {
	//TEST_9:对set_individual_chessboard产生疑惑，于是测试
	
	srand((unsigned int)time(NULL));
	int color = before_begin();
	SPACE chessboard[LENGTH][LENGTH];
	set_individual_chessboard(chessboard);
	printf("%d\n", chessboard[0][0].score);
	printf("%d\n", chessboard[4][8].y);
	printf("%d\n", chessboard[5][7].belong);
	system("pause");
	print_chessboard(chessboard);
	return 0;
}