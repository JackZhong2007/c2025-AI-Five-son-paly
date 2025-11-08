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
}
void AI_player_defense(SPACE space[LENGTH][LENGTH], int color) {
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
}
int situation_assessment(SPACE chessboard[LENGTH][LENGTH], int color) {
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
	if (color == BLACK) {
		situation_score += 100;
	}
	return situation_score;
}








/*
void roulette_wheel_selection(SPACE*x1,SPACE*x2,SPACE*x3, SPACE space[LENGTH][LENGTH],int color) {
	int sum = evaluate_score(*x1, space)+ evaluate_score(*x2, space) + evaluate_score(*x3, space);
	int num = rand() % sum;
	if (0 <= num && num < evaluate_score(*x1, space)) {
		space[x1->x][x1->y].belong = color;
	}
	else if (evaluate_score(*x1, space) <= num && num < evaluate_score(*x2, space)+ evaluate_score(*x1, space)) {
		space[x2->x][x2->y].belong = color;
	}
	else {
		space[x3->x][x3->y].belong = color;
	}
}
void exchange(SPACE*a, SPACE*b) {
	if (a->score < b->score) {
		SPACE c = *a;
		*a = *b;
		*b = c;
	}
}

void AI_player_offense(SPACE space[LENGTH][LENGTH], int color) {
	SPACE EVA[3] = { {-1,-1,BLANK,-97} ,{-1,-1,BLANK,-98} ,{-1,-1,BLANK,-99} };
	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			if (space[i][j].belong == BLANK) {
				space[i][j].belong = color;
				space[i][j].score = evaluate_score(space[i][j], space);
				exchange(&EVA[2], &space[i][j]);
				exchange(&EVA[1], &EVA[2]);
				exchange(&EVA[0], &EVA[1]);
				space[i][j].belong = BLANK;
			}
		}
	}
	if (EVA[0].score < 250) {
		roulette_wheel_selection(&EVA[0], &EVA[1], &EVA[2], space, color);
	}
	else {
		space[EVA[0].x][EVA[0].y].belong = color;
	}
}

void AI_player_defense(SPACE space[LENGTH][LENGTH], int color){
	SPACE EVA[3] = { {-1,-1,BLANK,-97} ,{-1,-1,BLANK,-98} ,{-1,-1,BLANK,-99} };
	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			if (space[i][j].belong == BLANK) {
				space[i][j].belong = (color == BLACK ? WHITE : BLACK);
				space[i][j].score = evaluate_score(space[i][j], space);
				exchange(&EVA[2], &space[i][j]);
				exchange(&EVA[1], &EVA[2]);
				exchange(&EVA[0], &EVA[1]);
				space[i][j].belong = BLANK;
			}
		}
	}
	if (EVA[0].score < 250) {
		roulette_wheel_selection(&EVA[0], &EVA[1], &EVA[2], space, color);
	}
	else {
		space[EVA[0].x][EVA[0].y].belong = color;
	}
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
	if (color == BLACK) {
		situation_score += 100;
	}
	return situation_score;
}
/*
void AI_player_offense(SPACE space[LENGTH][LENGTH], int color) {
	SPACE EVA[3] = { {-1,-1,BLANK,-1000}, {-1,-1,BLANK,-1000}, {-1,-1,BLANK,-1000} };

	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			if (space[i][j].belong == BLANK) {
				space[i][j].belong = color;
				int current_score = evaluate_score(space[i][j], space);
				space[i][j].belong = BLANK;

				// Î¬»¤top3
				if (current_score > EVA[0].score) {
					EVA[2] = EVA[1];
					EVA[1] = EVA[0];
					EVA[0] = space[i][j];
					EVA[0].score = current_score;
				}
				else if (current_score > EVA[1].score) {
					EVA[2] = EVA[1];
					EVA[1] = space[i][j];
					EVA[1].score = current_score;
				}
				else if (current_score > EVA[2].score) {
					EVA[2] = space[i][j];
					EVA[2].score = current_score;
				}
			}
		}
	}
	roulette_wheel_selection(&EVA[0], &EVA[1], &EVA[2], space, color);
}
*/
