#include"set_individual_chessboard.h"
#include"head_title_library.h"
#include"struct_library.h"
#include"print_chessboard.h"
#include"before_begin.h"
#include"human_player_play.h"
#include"victory_condition.h"
#include"evaluate_score.h"
int main() {
	//TEST_12:讲四个价值评估附属函数从Int类型改为同时返回数和是否是活的(返回三个值，
	// 一个表示连续数，两个表示左右两端是否被赌，
	//补充了棋的类型，新增“冲”，“死”两个类型
///*
	srand((unsigned int)time(NULL));
	int color = before_begin();
	SPACE chessboard[LENGTH][LENGTH];
	set_individual_chessboard(chessboard);
	print_chessboard(chessboard);
	int x, y;
	if (color == WHITE) {
		AI_player_play(chessboard, BLACK);
		print_chessboard(chessboard);
	}
	int AI_color = (color == WHITE) ? BLACK : WHITE;
	while (1) {
		scanf_s("%d%d", &x, &y);
		human_player_play(x, y, chessboard, color);
		printf("%d\t%d\t%d\n", check_continue_heng(chessboard[x][y], chessboard).num, check_continue_heng(chessboard[x][y], chessboard).live_1, check_continue_heng(chessboard[x][y], chessboard).live_2);
		printf("%d\t%d\t%d\n", check_continue_shu(chessboard[x][y], chessboard).num, check_continue_shu(chessboard[x][y], chessboard).live_1, check_continue_shu(chessboard[x][y], chessboard).live_2);
		printf("%d\t%d\t%d\n", check_continue_pie(chessboard[x][y], chessboard).num, check_continue_pie(chessboard[x][y], chessboard).live_1, check_continue_pie(chessboard[x][y], chessboard).live_2);
		printf("%d\t%d\t%d\n", check_continue_na(chessboard[x][y], chessboard).num, check_continue_na(chessboard[x][y], chessboard).live_1, check_continue_na(chessboard[x][y], chessboard).live_2);
		system("pause");
		print_chessboard(chessboard);
		
		if (color == victory_condition(chessboard)) {
			printf("You Win!\n");
			break;
		}
		AI_player_play(chessboard, AI_color);
		print_chessboard(chessboard);
		if (AI_color == victory_condition(chessboard)) {
			printf("AI Win!\n");
			break;
		}
	}
	//*/
	return 0;
}