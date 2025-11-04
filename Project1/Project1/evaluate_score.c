#include"evaluate_score.h"
NUM_LIVE check_continue_heng(SPACE stone_place, SPACE chessboard[LENGTH][LENGTH]) {
	const int X = stone_place.x, Y = stone_place.y;
	NUM_LIVE num_live = {1,true,true};
	for (int i = 1; i <= 4; i++) {
		if (Y - i < 0) {
			num_live.live_1 = false;
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
			num_live.live_2 = false;
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
			num_live.live_1 = false;
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
			num_live.live_2 = false;
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
		if (X- i < 0) {
			num_live.live_1 = false;
			break;
		}
		if (Y+i > LENGTH - 1) {
			num_live.live_1 = false;
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
			num_live.live_2 = false;
			break;
		}
		if (X + i > LENGTH - 1) {
			num_live.live_2 = false;
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
			num_live.live_1 = false;
			break;
		}
		if (X - i < 0) {
			num_live.live_1 = false;
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
			num_live.live_2 = false;
			break;
		}
		if (Y + i > LENGTH - 1) {
			num_live.live_2 = false;
			break;
		}
		if (chessboard[X + i][Y + i].belong == stone_place.belong) {
			num_live.num++;
		}
		else if (chessboard[X + i][Y + i].belong != BLANK) {
			num_live.live_2 = false;
			break;
		}
		else {
			break;
		}
	}
	return num_live;
}
int evaluate_score(SPACE stone_place,SPACE chessboard[LENGTH][LENGTH]) {
	//感觉可以以落子处为基准的一块区域内检验活三是否生成，活四是否生成，冲四是否生成
	//d博士那咨询了，记得看看
	int evaluation = 0;
	const int sign = stone_place.belong == BLACK ? 1 : -1;
	const int X = stone_place.x, Y = stone_place.y;
	NUM_LIVE HENG = check_continue_heng(stone_place, chessboard);
	NUM_LIVE SHU = check_continue_shu(stone_place, chessboard);
	NUM_LIVE PIE = check_continue_pie(stone_place, chessboard);
	NUM_LIVE NA = check_continue_na(stone_place, chessboard);
	switch (HENG.num) {
		case 1:
			if (!(HENG.live_1) && !(HENG.live_2)) {
				evaluation += DEAD_1;
			}
			else if (HENG.live_1 && HENG.live_2) {
				evaluation += LIVE_1;
			}
			break;
		case 2:
			if (!(HENG.live_1) && !(HENG.live_2)) {
				evaluation += DEAD_2;
			}
			else if (HENG.live_1 && HENG.live_2) {
				evaluation += LIVE_2;
			}
			else {
				evaluation += SLEEP_2;
			}
			break;
		case 3:
			if (!(HENG.live_1) && !(HENG.live_2)) {
				evaluation += DEAD_3;
			}
			else if (HENG.live_1 && HENG.live_2) {
				evaluation += LIVE_3;
			}
			else {
				evaluation += SLEEP_3;
			}
			break;
		case 4:
			if (!(HENG.live_1) && !(HENG.live_2)) {
				evaluation += DEAD_4;
			}
			else if (HENG.live_1 && HENG.live_2) {
				evaluation += LIVE_4;
			}
			else {
				evaluation += SLEEP_4;
			}
			break;
		case 5:
			evaluation += LIVE_5;
			break;
	}
	switch (SHU.num) {
	case 1:
		if (!(SHU.live_1) && !(SHU.live_2)) {
			evaluation += DEAD_1;
		}
		else if (SHU.live_1 && SHU.live_2) {
			evaluation += LIVE_1;
		}
		break;
	case 2:
		if (!(SHU.live_1) && !(SHU.live_2)) {
			evaluation += DEAD_2;
		}
		else if (SHU.live_1 && SHU.live_2) {
			evaluation += LIVE_2;
		}
		else {
			evaluation += SLEEP_2;
		}
		break;
	case 3:
		if (!(SHU.live_1) && !(SHU.live_2)) {
			evaluation += DEAD_3;
		}
		else if (SHU.live_1 && SHU.live_2) {
			evaluation += LIVE_3;
		}
		else {
			evaluation += SLEEP_3;
		}
		break;
	case 4:
		if (!(SHU.live_1) && !(SHU.live_2)) {
			evaluation += DEAD_4;
		}
		else if (SHU.live_1 && SHU.live_2) {
			evaluation += LIVE_4;
		}
		else {
			evaluation += SLEEP_4;
		}
		break;
	case 5:
		evaluation += LIVE_5;
		break;
	}
	switch (PIE.num) {
	case 1:
		if (!(PIE.live_1) && !(PIE.live_2)) {
			evaluation += DEAD_1;
		}
		else if (PIE.live_1 && PIE.live_2) {
			evaluation += LIVE_1;
		}
		break;
	case 2:
		if (!(PIE.live_1) && !(PIE.live_2)) {
			evaluation += DEAD_2;
		}
		else if (PIE.live_1 && PIE.live_2) {
			evaluation += LIVE_2;
		}
		else {
			evaluation += SLEEP_2;
		}
		break;
	case 3:
		if (!(PIE.live_1) && !(PIE.live_2)) {
			evaluation += DEAD_3;
		}
		else if (PIE.live_1 && PIE.live_2) {
			evaluation += LIVE_3;
		}
		else {
			evaluation += SLEEP_3;
		}
		break;
	case 4:
		if (!(PIE.live_1) && !(PIE.live_2)) {
			evaluation += DEAD_4;
		}
		else if (PIE.live_1 && PIE.live_2) {
			evaluation += LIVE_4;
		}
		else {
			evaluation += SLEEP_4;
		}
		break;
	case 5:
		evaluation += LIVE_5;
		break;
	}
	switch (NA.num) {
	case 1:
		if (!(NA.live_1) && !(NA.live_2)) {
			evaluation += DEAD_1;
		}
		else if (NA.live_1 && NA.live_2) {
			evaluation += LIVE_1;
		}
		break;
	case 2:
		if (!(NA.live_1) && !(NA.live_2)) {
			evaluation += DEAD_2;
		}
		else if (NA.live_1 && NA.live_2) {
			evaluation += LIVE_2;
		}
		else {
			evaluation += SLEEP_2;
		}
		break;
	case 3:
		if (!(NA.live_1) && !(NA.live_2)) {
			evaluation += DEAD_3;
		}
		else if (NA.live_1 && NA.live_2) {
			evaluation += LIVE_3;
		}
		else {
			evaluation += SLEEP_3;
		}
		break;
	case 4:
		if (!(NA.live_1) && !(NA.live_2)) {
			evaluation += DEAD_4;
		}
		else if (NA.live_1 && NA.live_2) {
			evaluation += LIVE_4;
		}
		else {
			evaluation += SLEEP_4;
		}
		break;
	case 5:
		evaluation += LIVE_5;
		break;
	}
	return evaluation;
}
