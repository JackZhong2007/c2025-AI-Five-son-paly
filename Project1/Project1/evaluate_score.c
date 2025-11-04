#include"evaluate_score.h"
NUM_LIVE check_continue_heng(SPACE stone_place, SPACE chessboard[LENGTH][LENGTH]) {
	const int X = stone_place.x, Y = stone_place.y;
	NUM_LIVE num_live = {1,true,true};
	for (int i = 1; i <= 4; i++) {
		if (Y - i < 0) {
			break;
		}
		if (chessboard[X][Y - i].belong == stone_place.belong) {
			num_live.num++;
		}
		else if(chessboard[X][Y - i].belong != BLANK){
			num_live.live_1 = false;
			break;
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
			num_live.num++;
		}
		else if (chessboard[X][Y + i].belong != BLANK) {
			num_live.live_2 = false;
			break;
		}
		else {
			break;
		}
	}
	return num_live;
}
NUM_LIVE check_continue_shu(SPACE stone_place, SPACE chessboard[LENGTH][LENGTH]) {
	const int X = stone_place.x, Y = stone_place.y;
	NUM_LIVE num_live = { 1,true,true };
	for (int i = 1; i <= 4; i++) {
		if (X - i < 0) {
			break;
		}
		if (chessboard[X-i][Y].belong == stone_place.belong) {
			num_live.num++;
		}
		else if (chessboard[X - i][Y].belong != BLANK) {
			num_live.live_1 = false;
			break;
		}
		else {
			break;
		}
	}
	for (int i = 1; i <= 4; i++) {
		if (X + i > LENGTH - 1) {
			break;
		}
		if (chessboard[X+i][Y].belong == stone_place.belong) {
			num_live.num++;
		}
		else if (chessboard[X + i][Y].belong != BLANK) {
			num_live.live_2 = false;
			break;
		}
		else {
			break;
		}
	}
	return num_live;
}
NUM_LIVE check_continue_pie(SPACE stone_place, SPACE chessboard[LENGTH][LENGTH]) {
	const int X = stone_place.x, Y = stone_place.y;
	NUM_LIVE num_live = { 1,true,true };
	for (int i = 1; i <= 4; i++) {
		if (Y - i < 0) {
			break;
		}
		if (X + i > LENGTH - 1) {
			break;
		}
		if (chessboard[X - i][Y+i].belong == stone_place.belong) {
			num_live.num++;
		}
		else if (chessboard[X - i][Y + i].belong != BLANK) {
			num_live.live_1 = false;
			break;
		}
		else {
			break;
		}
	}
	for (int i = 1; i <= 4; i++) {
		if (Y - i < 0) {
			break;
		}
		if (X + i > LENGTH - 1) {
			break;
		}
		if (chessboard[X + i][Y-i].belong == stone_place.belong) {
			num_live.num++;
		}
		else if (chessboard[X + i][Y - i].belong != BLANK) {
			num_live.live_2 = false;
			break;
		}
		else {
			break;
		}
	}
	return num_live;
}
NUM_LIVE check_continue_na(SPACE stone_place, SPACE chessboard[LENGTH][LENGTH]) {
	const int X = stone_place.x, Y = stone_place.y;
	NUM_LIVE num_live = { 1,true,true };
	for (int i = 1; i <= 4; i++) {
		if (Y - i < 0) {
			break;
		}
		if (X - i < 0) {
			break;
		}
		if (chessboard[X - i][Y - i].belong == stone_place.belong) {
			num_live.num++;
		}
		else if (chessboard[X - i][Y - i].belong != BLANK) {
			num_live.live_1 = false;
			break;
		}
		else {
			break;
		}
	}
	for (int i = 1; i <= 4; i++) {
		if (X + i > LENGTH - 1) {
			break;
		}
		if (Y + i > LENGTH - 1) {
			break;
		}
		if (chessboard[X + i][Y + i].belong == stone_place.belong) {
			num_live.num++;
		}
		else if (chessboard[X + i][Y + i].belong != BLANK) {
			num_live.live_2 = false;
			break;
		}
	}
	return num_live;
}
void evaluate_score(SPACE stone_place,SPACE chessboard[LENGTH][LENGTH]) {
	//感觉可以以落子处为基准的一块区域内检验活三是否生成，活四是否生成，冲四是否生成
	//d博士那咨询了，记得看看
	stone_place.score = 0;
	const int sign = stone_place.belong == BLACK ? 1 : -1;
	const int X = stone_place.x, Y = stone_place.y;
	int HENG = check_continue_heng(stone_place, chessboard).num;
	int SHU = check_continue_shu(stone_place, chessboard).num;
	int PIE = check_continue_pie(stone_place, chessboard).num;
	int	NA = check_continue_na(stone_place, chessboard).num;
	
}
