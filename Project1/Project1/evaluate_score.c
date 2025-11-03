#include"evaluate_score.h"
int check_continue_heng(SPACE stone_place, SPACE chessboard[LENGTH][LENGTH]) {
	const int X = stone_place.x, Y = stone_place.y;
	int num=1;
	for (int i = 1; i <= 4; i++) {
		if (Y - i < 0) {
			break;
		}
		if (chessboard[X][Y - i].belong == stone_place.belong) {
			num++;
		}
		else {
			break;
		}
	}
	for (int i = 1; i <= 4; i++) {
		if (Y + i > LENGTH - 1) {
			break;
		}
		if (chessboard[X][Y + i].belong == stone_place.belong) {
			num++;
		}
		else {
			break;
		}
	}
	return num;
}
void evaluate_score(SPACE stone_place,SPACE chessboard[LENGTH][LENGTH]) {
	//感觉可以以落子处为基准的一块区域内检验活三是否生成，活四是否生成，冲四是否生成
	//d博士那咨询了，记得看看
	stone_place.score = 0;
	const int sign = stone_place.belong == BLACK ? 1 : -1;
	const int X = stone_place.x, Y = stone_place.y;
	for (int i = X - 4; i <= i + 4; i++) {

	}
}
