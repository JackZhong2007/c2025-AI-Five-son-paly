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
	//TEST_20:重新简化调整alpha_beta函数，各棋形分值回归原来值，evaluate.c回归原先
	//增加了一个输入保护机制：避免输入落子位置时故意或者有意输入了棋盘外的点位导致栈溢出
	//将搜索深度设置为4后，并且修改了一些棋类的分值，可以避免很多情况下AI下棋的弱智行为，但并未完全杜绝其发生。
	//发现在将搜索深度设置为4后，直接删去危机棋形应急应对策略，发现反而不会出现弱智行为了
	//尝试将原先AI执黑时在中心九格随机落子删去，同质化使用AIalpha-beta函数，但发现AI会稳定的落子在（6，6），于是取消此想法，并将范围扩大到中心25格
	//新增AI落子后告知玩家落子位置，并提示玩家走棋
	//用Release模式代替Debug模式运行速度会提升多倍，甚至一个数量级
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
			break;
		}
		SPACE AI=AI_player_optimized(chessboard, AI_color);
		print_chessboard(chessboard);
		if (AI_color == victory_condition(chessboard)) {
			printf("AI Win!\n");
			break;
		}
		printf("AI choose stone place(%d,%d).\n", AI.x, AI.y);
		printf("It's your turn!\n");
	}
	//*/
	return 0;
}