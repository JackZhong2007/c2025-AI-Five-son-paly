#include"set_individual_chessboard.h"
#include"head_title_library.h"
#include"struct_library.h"
#include"print_chessboard.h"
#include"before_begin.h"
#include"human_player_play.h"
#include"victory_condition.h"
#include"evaluate_score.h"
int main() {
	//TEST_15:将test14中完成的ai落子策略命名为进攻策略，并完成防守落子策略
///*
	srand((unsigned int)time(NULL));
	int color = before_begin();
	SPACE chessboard[LENGTH][LENGTH];
	set_individual_chessboard(chessboard);
	print_chessboard(chessboard);
	int x, y;
	if (color == WHITE) {
		chessboard[7][7].belong = BLACK;
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
		AI_player_defense(chessboard, AI_color);
		print_chessboard(chessboard);
		if (AI_color == victory_condition(chessboard)) {
			printf("AI Win!\n");
			break;
		}
	}
	//*/
	return 0;
}