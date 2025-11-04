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
void AI_player_play(SPACE space[LENGTH][LENGTH], int color) {
	int X = -1, Y = -1, EVALUATION = -99;
	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			if (space[i][j].belong == BLANK) {
				space[i][j].belong = color;
				int temp_eva = evaluate_score(space[i][j], space);
				//printf("%d\n", temp_eva);
				//system("pause");
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
	printf("%d\n", EVALUATION);
	printf("%d\n", check_continue_heng(space[X][Y], space).num);
	printf("%d\n", check_continue_shu(space[X][Y], space).num);
	printf("%d\n", check_continue_pie(space[X][Y], space).num);
	printf("%d\n", check_continue_na(space[X][Y], space).num);
	printf("%d\n", check_continue_na(space[X][Y], space).live_1);
	printf("%d\n", check_continue_na(space[X][Y], space).live_2);
	system("pause");
}