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
	//TEST_21:“冲字模型有点问题——冲也应该有死活之分，对于威胁程度不同
	//改进方案为利用live_1,live_2,但发现有问题，遂想增添结构体内含变量
	//对evaluate函数进行了较多改动，以减少“重复的味道”，但是这个.c文件的重复味道应该还是很浓郁的
	//新增游戏结束时弹出提框的功能
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