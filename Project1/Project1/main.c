#include"set_individual_chessboard.h"
#include"head_title_library.h"
#include"struct_library.h"
#include"print_chessboard.h"
#include"before_begin.h"
#include"human_player_play.h"
#include"victory_condition.h"
#include"evaluate_score.h"
#include"AI_player_play.h"
#include"AI_player_DFS_alpha_beta.h"
int main() {
	//TEST_19:DFS策略，alpha-beta剪枝，evaluate_score函数重构升级，用了AI改进很多次，对各个改进版本备案
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
		//printf("%d\n", situation_assessment(chessboard, AI_color));
		//system("pause");
		/*
		if (situation_assessment(chessboard, AI_color) >= 0) {
			AI_player_offense(chessboard, AI_color);
		}
		else {
			AI_player_defense(chessboard, AI_color);
		}
		*/
		AI_player_optimized(chessboard, AI_color);
		print_chessboard(chessboard);
		if (AI_color == victory_condition(chessboard)) {
			printf("AI Win!\n");
			break;
		}
	}
	//*/
	return 0;
}