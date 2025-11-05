#include"evaluate_score.h"
NUM_LIVE check_continue_heng(SPACE stone_place, SPACE chessboard[LENGTH][LENGTH]) {
	const int X = stone_place.x, Y = stone_place.y;
	NUM_LIVE num_live = { 1,true,true,{false,false,false},{false,false,false}	};
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
			for (int j = 1; j <= 3; j++) {
				if (Y - i - j < 0) 	break;
				else {
					if (chessboard[X][Y - i - j].belong == stone_place.belong) {
						num_live.chong_1[j-1] = true;
					}
					else {
						break;
					}
				}
			}
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
			for (int j = 1; j <= 3; j++) {
				if (Y + i + j >LENGTH-1) break;
				else {
					if (chessboard[X][Y + i + j].belong == stone_place.belong) {
						num_live.chong_2[j - 1] = true;
					}
					else {
						break;
					}
				}
			}
			break;
		}
	}
	return num_live;
}
NUM_LIVE check_continue_shu(SPACE stone_place, SPACE chessboard[LENGTH][LENGTH]) {
	const int X = stone_place.x, Y = stone_place.y;
	NUM_LIVE num_live = { 1,true,true,{false,false,false},{false,false,false} };
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
			for (int j = 1; j <= 3; j++) {
				if (X - i - j < 0) {
					break;
				}
				else {
					if (chessboard[X - i - j][Y].belong == stone_place.belong) {
						num_live.chong_1[j - 1] = true;
					}
					else {
						break;
					}
				}
			}
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
			for (int j = 1; j <= 3; j++) {
				if (X + i + j > LENGTH - 1) {
					break;
				}
				else {
					if (chessboard[X + i + j][Y].belong == stone_place.belong) {
						num_live.chong_2[j - 1] = true;
					}
					else {
						break;
					}
				}
			}
			break;
		}
	}
	return num_live;
}
NUM_LIVE check_continue_pie(SPACE stone_place, SPACE chessboard[LENGTH][LENGTH]) {
	const int X = stone_place.x, Y = stone_place.y;
	NUM_LIVE num_live = { 1,true,true,{false,false,false},{false,false,false} };
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
			for (int j = 1; j <= 3; j++) {
				if (X - i - j < 0)	break;
				if (Y + i + j > LENGTH - 1)	break;
				else {
					if (chessboard[X - i - j][Y + i + j].belong == stone_place.belong) {
						num_live.chong_1[j - 1] = true;
					}
					else {
						break;
					}
				}
			}
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
			for (int j = 1; j <= 3; j++) {
				if (Y - i - j < 0)	break;
				if (X + i + j > LENGTH - 1)	break;
				else {
					if (chessboard[X + i + j][Y - i - j].belong == stone_place.belong) {
						num_live.chong_1[j - 1] = true;
					}
					else {
						break;
					}
				}
			}
			break;
		}
	}
	return num_live;
}
NUM_LIVE check_continue_na(SPACE stone_place, SPACE chessboard[LENGTH][LENGTH]) {
	const int X = stone_place.x, Y = stone_place.y;
	NUM_LIVE num_live = { 1,true,true,{false,false,false},{false,false,false} };
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
			for (int j = 1; j <= 3; j++) {
				if (Y - i - j < 0)	break;
				if (X - i - j < 0)	break;
				else {
					if (chessboard[X - i - j][Y - i - j].belong == stone_place.belong) {
						num_live.chong_1[j - 1] = true;
					}
					else {
						break;
					}
				}
			}
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
			for (int j = 1; j <= 3; j++) {
				if (Y + i + j > LENGTH - 1)	break;
				if (X + i + j > LENGTH - 1)	break;
				else {
					if (chessboard[X + i + j][Y + i + j].belong == stone_place.belong) {
						num_live.chong_1[j - 1] = true;
					}
					else {
						break;
					}
				}
			}
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
	NUM_LIVE HSPN[4] = { check_continue_heng(stone_place, chessboard),
						check_continue_shu(stone_place, chessboard), 
						check_continue_pie(stone_place, chessboard),
						check_continue_na(stone_place, chessboard) };
	switch (HSPN[0].num) {
		case 1:
			if (!(HSPN[0].live_1) && !(HSPN[0].live_2)) {
				evaluation += DEAD_1;
			}
			else if (HSPN[0].live_1 && HSPN[0].live_2) {
				evaluation += LIVE_1;
			}
			break;
		case 2:
			if (!(HSPN[0].live_1) && !(HSPN[0].live_2)) {
				evaluation += DEAD_2;
			}
			else if (HSPN[0].live_1 && HSPN[0].live_2) {
				evaluation += LIVE_2;
			}
			else {
				evaluation += SLEEP_2;
			}
			break;
		case 3:
			if (!(HSPN[0].live_1) && !(HSPN[0].live_2)) {
				evaluation += DEAD_3;
			}
			else if (HSPN[0].live_1 && HSPN[0].live_2) {
				evaluation += LIVE_3;
			}
			else {
				evaluation += SLEEP_3;
			}
			break;
		case 4:
			if (!(HSPN[0].live_1) && !(HSPN[0].live_2)) {
				evaluation += DEAD_4;
			}
			else if (HSPN[0].live_1 && HSPN[0].live_2) {
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
	switch (HSPN[1].num) {
	case 1:
		if (!(HSPN[1].live_1) && !(HSPN[1].live_2)) {
			evaluation += DEAD_1;
		}
		else if (HSPN[1].live_1 && HSPN[1].live_2) {
			evaluation += LIVE_1;
		}
		break;
	case 2:
		if (!(HSPN[1].live_1) && !(HSPN[1].live_2)) {
			evaluation += DEAD_2;
		}
		else if (HSPN[1].live_1 && HSPN[1].live_2) {
			evaluation += LIVE_2;
		}
		else {
			evaluation += SLEEP_2;
		}
		break;
	case 3:
		if (!(HSPN[1].live_1) && !(HSPN[1].live_2)) {
			evaluation += DEAD_3;
		}
		else if (HSPN[1].live_1 && HSPN[1].live_2) {
			evaluation += LIVE_3;
		}
		else {
			evaluation += SLEEP_3;
		}
		break;
	case 4:
		if (!(HSPN[1].live_1) && !(HSPN[1].live_2)) {
			evaluation += DEAD_4;
		}
		else if (HSPN[1].live_1 && HSPN[1].live_2) {
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
	switch (HSPN[2].num) {
	case 1:
		if (!(HSPN[2].live_1) && !(HSPN[2].live_2)) {
			evaluation += DEAD_1;
		}
		else if (HSPN[2].live_1 && HSPN[2].live_2) {
			evaluation += LIVE_1;
		}
		break;
	case 2:
		if (!(HSPN[2].live_1) && !(HSPN[2].live_2)) {
			evaluation += DEAD_2;
		}
		else if (HSPN[2].live_1 && HSPN[2].live_2) {
			evaluation += LIVE_2;
		}
		else {
			evaluation += SLEEP_2;
		}
		break;
	case 3:
		if (!(HSPN[2].live_1) && !(HSPN[2].live_2)) {
			evaluation += DEAD_3;
		}
		else if (HSPN[2].live_1 && HSPN[2].live_2) {
			evaluation += LIVE_3;
		}
		else {
			evaluation += SLEEP_3;
		}
		break;
	case 4:
		if (!(HSPN[2].live_1) && !(HSPN[2].live_2)) {
			evaluation += DEAD_4;
		}
		else if (HSPN[2].live_1 && HSPN[2].live_2) {
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
	switch (HSPN[3].num) {
	case 1:
		if (!(HSPN[3].live_1) && !(HSPN[3].live_2)) {
			evaluation += DEAD_1;
		}
		else if (HSPN[3].live_1 && HSPN[3].live_2) {
			evaluation += LIVE_1;
		}
		break;
	case 2:
		if (!(HSPN[3].live_1) && !(HSPN[3].live_2)) {
			evaluation += DEAD_2;
		}
		else if (HSPN[3].live_1 && HSPN[3].live_2) {
			evaluation += LIVE_2;
		}
		else {
			evaluation += SLEEP_2;
		}
		break;
	case 3:
		if (!(HSPN[3].live_1) && !(HSPN[3].live_2)) {
			evaluation += DEAD_3;
		}
		else if (HSPN[3].live_1 && HSPN[3].live_2) {
			evaluation += LIVE_3;
		}
		else {
			evaluation += SLEEP_3;
		}
		break;
	case 4:
		if (!(HSPN[3].live_1) && !(HSPN[3].live_2)) {
			evaluation += DEAD_4;
		}
		else if (HSPN[3].live_1 && HSPN[3].live_2) {
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
	int chong[8] = { 0 };
	for (int i = 0; i <= 2; i++) {
		if (HSPN[0].chong_1[i])	chong[0]++;
		if (HSPN[0].chong_2[i])	chong[1]++;
		if (HSPN[1].chong_1[i])		chong[2]++;
		if (HSPN[1].chong_2[i])		chong[3]++;
		if (HSPN[2].chong_1[i])		chong[4]++;
		if (HSPN[2].chong_2[i])		chong[5]++;
		if (HSPN[3].chong_1[i])		chong[6]++;
		if (HSPN[3].chong_2[i])		chong[7]++;
	}
	for (int i = 0; i < 8; i++) {
		int num = 0;
		if (i == 0 || i == 1) num = 0;
		if (i == 2 || i == 3) num = 1;
		if (i == 4 || i == 5) num = 2;
		if (i == 6 || i == 7) num = 3;
		if (chong[i] > 0) {
			switch (HSPN[num].num + chong[i]) {
			case 2:	evaluation += CHONG_3;	break;
			case 3:	evaluation += CHONG_4;  break;
			case 4: evaluation += CHONG_5;	break;
			}
		}
	}
	return evaluation;
}
