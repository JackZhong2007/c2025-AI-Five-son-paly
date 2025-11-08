#include"set_individual_chessboard.h"
#include"head_title_library.h"
#include"struct_library.h"
#include"print_chessboard.h"
#include"before_begin.h"
#include"human_player_play.h"
#include"victory_condition.h"
#include"evaluate_score.h"
#include"AI_player_play.h"
int main() {
	//TEST_18:当AI执黑时，将落子位置从7，7改为在以7，7为中心的3*3空间内随机落子
	//同时，为了增加AI落子的随机性，将选取当前局面最优的三个落子位置，按照轮盘赌随机落子,但是此方案最终取消，以避免必应落子由于随机数而未应答
	//贪心算法策略完成
///*
	srand((unsigned int)time(NULL));
	int color = before_begin();
	SPACE chessboard[LENGTH][LENGTH];
	set_individual_chessboard(chessboard);
	print_chessboard(chessboard);
	int x, y;
	if (color == WHITE) {
		int x_rand = rand() % 3 + 6, y_rand = rand() % 3 + 6;
		chessboard[x_rand][y_rand].belong = BLACK;
		print_chessboard(chessboard);
	}
	int AI_color = (color == WHITE) ? BLACK : WHITE;
	while (1) {
		scanf_s("%d%d", &x, &y);
		human_player_play(x, y, chessboard, color);
		print_chessboard(chessboard);
		
		if (color == victory_condition(chessboard)) {
			printf("You Win!\n");
			break;
		}
		printf("%d\n", situation_assessment(chessboard, AI_color));
		system("pause");
		if (situation_assessment(chessboard, AI_color) >= 0) {
			AI_player_offense(chessboard, AI_color);
		}
		else {
			AI_player_defense(chessboard, AI_color);
		}
		print_chessboard(chessboard);
		if (AI_color == victory_condition(chessboard)) {
			printf("AI Win!\n");
			break;
		}
	}
	//*/
	return 0;
}