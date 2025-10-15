#include"AI_player_play.h"
#include"head_title_library.h"
#include"struct_library.h"
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