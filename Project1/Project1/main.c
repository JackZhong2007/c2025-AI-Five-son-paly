#include"set_individual_chessboard.h"
#include"head_title_library.h"
#include"struct_library.h"
#include"print_chessboard.h"
#include"before_begin.h"
#include"human_player_play.h"
#include"victory_condition.h"
#include"evaluate_score.h"
int main() {
	//TEST_13:完成evaluate_score,书写过程中发现“冲”类型需要另外来写，涉及到假设落子该点，那么得分变化会如何，之后再另外讨论
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
		printf("%d\n", evaluate_score(chessboard[x][y], chessboard));
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