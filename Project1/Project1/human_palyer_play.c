#include"human_player_play.h"
#include"head_title_library.h"
#include"struct_library.h"
void human_player_play(int x,int y,SPACE space[LENGTH][LENGTH]) {
	if (BLANK == space[x][y].belong) {
		space[x][y].belong = BLACK;
	}
	else {
		int new_x, new_y;
		scanf_s("%d%d", &new_x, &new_y);
		human_player_play(new_x, new_y, space);
	}
}