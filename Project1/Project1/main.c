#include"head_title_library.h"
#include"print_chessboard.h"
#include"before_begin.h"
#include"human_player_play.h"
#include"victory_condition.h"
#include"evaluate_score.h"
#include"AI_player_DFS_alpha_beta.h"
int main() {
	//TEST_23:合并struct_library和head_title_library,将前者并入后者
	// 删去贪心算法——AI_player_play的c和h文件
	//将console_individual并入before_begin
	//修改了before_begin中执黑与执白时等待时间不同的问题
	//优化了.c文件与.h文件中重复调用头文件的小问题
	//将set_indicidual_chessboard并入before_begin
	//修复了alpha-beta函数中未引用evaluate_score.h的问题
	//优化了print_chessboard函数中不断重置console隐藏的累余
	//优化了evaluate部分函数，减少些许重复的味道
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