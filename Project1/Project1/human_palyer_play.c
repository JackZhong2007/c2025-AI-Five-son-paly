#include"human_player_play.h"
void human_player_play(int x,int y,SPACE space[LENGTH][LENGTH],int color) {
	if (x > LENGTH - 1 || x<0 || y>LENGTH || y < 0) {
		printf("please follow the rule,your stone place is not in the chessboard.\n");
		int a, b;
		scanf_s("%d%d", &a,&b);
		human_player_play(a, b, space, color);
		return;
	}
	if (space[x][y].belong==BLANK) {
		space[x][y].belong = color;
	}
	else {
		int new_x, new_y;
		printf("This position is already occupied. Please choose another position:\n");
		scanf_s("%d%d", &new_x, &new_y);
		human_player_play(new_x, new_y, space,color);
	} 
}