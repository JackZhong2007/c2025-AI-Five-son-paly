#include"AI_player_play.h"
#include"head_title_library.h"
#include"struct_library.h"
#include"evaluate_score.h"
/*
void AI_player_play(SPACE space[LENGTH][LENGTH], int color) {
	int x = rand() % LENGTH;
	int y = rand() % LENGTH;
	if (BLANK == space[x][y].belong) {
		space[x][y].belong = color;
	}
	else {
		AI_player_play(space, color);
	}
}
*/
void AI_player_offense(SPACE space[LENGTH][LENGTH], int color) {
	int X = -1, Y = -1, EVALUATION = -99;
	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			if (space[i][j].belong == BLANK) {
				space[i][j].belong = color;
				int temp_eva = evaluate_score(space[i][j], space);
				if (temp_eva > EVALUATION) {
					EVALUATION = temp_eva;
					X = i;
					Y = j;
				}
				space[i][j].belong = BLANK;
			}
		}
	}
	space[X][Y].belong = color; 
	/*
	printf("%d\n", EVALUATION);
	printf("%d\n", check_continue_heng(space[X][Y], space).num);
	printf("%d\n", check_continue_shu(space[X][Y], space).num);
	printf("%d\n", check_continue_pie(space[X][Y], space).num);
	printf("%d\n", check_continue_na(space[X][Y], space).num);
	printf("%d\n", check_continue_na(space[X][Y], space).live_1);
	printf("%d\n", check_continue_na(space[X][Y], space).live_2);
	system("pause");
	*/
}
void AI_player_defense(SPACE space[LENGTH][LENGTH], int color){
	int X = -1, Y = -1, EVALUATION = -99;
	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			if (space[i][j].belong == BLANK) {
				space[i][j].belong = (color == BLACK ? WHITE : BLACK);
				int temp_eva = evaluate_score(space[i][j], space);
				if (temp_eva > EVALUATION) {
					EVALUATION = temp_eva;
					X = i;
					Y = j;
				}
				space[i][j].belong = BLANK;
			}
		}
	}
	space[X][Y].belong = color;
	/*
	printf("%d\n", EVALUATION);
	printf("%d\n", check_continue_heng(space[X][Y], space).num);
	printf("%d\n", check_continue_shu(space[X][Y], space).num);
	printf("%d\n", check_continue_pie(space[X][Y], space).num);
	printf("%d\n", check_continue_na(space[X][Y], space).num);
	printf("%d\n", check_continue_na(space[X][Y], space).live_1);
	printf("%d\n", check_continue_na(space[X][Y], space).live_2);
	system("pause");
	*/
}
int situation_assessment(SPACE chessboard[LENGTH][LENGTH],int color) {
	int situation_score = 0;
	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			if (chessboard[i][j].belong == color) {
				situation_score += evaluate_score(chessboard[i][j], chessboard);
			}
			else if (chessboard[i][j].belong == BLANK) {
				continue;
			}
			else {
				situation_score -= evaluate_score(chessboard[i][j], chessboard);
			}
		}
	}
	return situation_score;
}