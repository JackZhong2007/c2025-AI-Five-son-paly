#include"head_title_library.h"
#include"print_chessboard.h"
#include"before_begin.h"
#include"human_player_play.h"
#include"victory_condition.h"
#include"evaluate_score.h"
#include"AI_player_DFS_alpha_beta.h"
int main() {
	//TEST_24:优化了UI，新增落子规范示例，新增按'b'确定启动游戏，而不是短暂的暂停然后自动启动游戏
///*
	srand((unsigned int)time(NULL));
	int color = before_begin();
	SPACE chessboard[LENGTH][LENGTH];
	set_individual_chessboard(chessboard);
	print_chessboard(chessboard);
	int x, y;
	if (color == WHITE) {
		int x_rand = rand() % 5 + 4, y_rand = rand() % 5 + 4;
		chessboard[x_rand][y_rand].belong = BLACK;
		print_chessboard(chessboard);
		printf("AI choose stone place(%d,%d).\n", x_rand, y_rand);
		printf("It's your turn!\n");
	}
	int AI_color = (color == WHITE) ? BLACK : WHITE;
	while (1) {
		scanf_s("%d%d", &x, &y);
		human_player_play(x, y, chessboard, color);
		print_chessboard(chessboard);
		if (color == victory_condition(chessboard)) {
			printf("You Win!\n");
			MessageBox(0, TEXT("You win! Congratulations!"), TEXT("GameOver"), NULL);
			break;
		}
		SPACE AI=AI_player_optimized(chessboard, AI_color);
		print_chessboard(chessboard);
		if (AI_color == victory_condition(chessboard)) {
			printf("AI Win!\n");
			MessageBox(0, TEXT("You lost! What a pity!"), TEXT("GameOver"), NULL);
			break;
		}
		printf("AI choose stone place(%d,%d).\n", AI.x, AI.y);
		printf("It's your turn!\n");
	}
	//*/
	return 0;
}