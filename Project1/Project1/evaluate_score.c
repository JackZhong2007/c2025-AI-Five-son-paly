#include "evaluate_score.h"
NUM_LIVE check_continue_heng(SPACE stone_place, SPACE chessboard[LENGTH][LENGTH]) {
	const int X = stone_place.x, Y = stone_place.y;
	NUM_LIVE num_live = { 1,true,true,{false,false,false},{false,false,false},{true,true }};
	for (int i = 1; i <= 4; i++) {
		if (Y - i < 0) {
			num_live.live[0] = false;
			break;
		}
		if (chessboard[X][Y - i].belong == stone_place.belong) {
			num_live.num++;
		}
		else if(chessboard[X][Y - i].belong != BLANK){
			num_live.live[0] = false;
			break;
		}
		else {
			for (int j = 1; j <= 3; j++) {
				if (Y - i - j < 0) 	break;
				else {
					if (chessboard[X][Y - i - j].belong == stone_place.belong) {
						num_live.chong_1[j-1] = true;
					}
					else if (chessboard[X][Y - i - j].belong != BLANK) {
						num_live.chong_live[0] = false;
						break;
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
			num_live.live[1] = false;
			break;
		}
		if (chessboard[X][Y + i].belong == stone_place.belong) {
			num_live.num++;
		}
		else if (chessboard[X][Y + i].belong != BLANK) {
			num_live.live[1] = false;
			break;
		}
		else {
			for (int j = 1; j <= 3; j++) {
				if (Y + i + j >LENGTH-1) break;
				else {
					if (chessboard[X][Y + i + j].belong == stone_place.belong) {
						num_live.chong_2[j - 1] = true;
					}
					else if (chessboard[X][Y + i + j].belong != BLANK) {
						num_live.chong_live[1] = false;
						break;
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
	NUM_LIVE num_live = { 1,true,true,{false,false,false},{false,false,false},{true,true} };
	for (int i = 1; i <= 4; i++) {
		if (X - i < 0) {
			num_live.live[0] = false;
			break;
		}
		if (chessboard[X-i][Y].belong == stone_place.belong) {
			num_live.num++;
		}
		else if (chessboard[X - i][Y].belong != BLANK) {
			num_live.live[0] = false;
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
					else if (chessboard[X - i - j][Y].belong != BLANK) {
						num_live.chong_live[0] = false;
						break;
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
			num_live.live[1] = false;
			break;
		}
		if (chessboard[X+i][Y].belong == stone_place.belong) {
			num_live.num++;
		}
		else if (chessboard[X + i][Y].belong != BLANK) {
			num_live.live[1] = false;
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
					else if (chessboard[X + i + j][Y].belong != BLANK) {
						num_live.chong_live[1] = false;
						break;
					}
					else{
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
	NUM_LIVE num_live = { 1,true,true,{false,false,false},{false,false,false},{true,true} };
	for (int i = 1; i <= 4; i++) {
		if (X- i < 0) {
			num_live.live[0] = false;
			break;
		}
		if (Y+i > LENGTH - 1) {
			num_live.live[0] = false;
			break;
		}
		if (chessboard[X - i][Y+i].belong == stone_place.belong) {
			num_live.num++;
		}
		else if (chessboard[X - i][Y + i].belong != BLANK) {
			num_live.live[0] = false;
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
					else if (chessboard[X - i - j][Y + i + j].belong != BLANK) {
						num_live.chong_live[0] = false;
						break;
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
			num_live.live[1] = false;
			break;
		}
		if (X + i > LENGTH - 1) {
			num_live.live[1] = false;
			break;
		}
		if (chessboard[X + i][Y-i].belong == stone_place.belong) {
			num_live.num++;
		}
		else if (chessboard[X + i][Y - i].belong != BLANK) {
			num_live.live[1] = false;
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
					else if (chessboard[X + i + j][Y - i - j].belong != BLANK) {
						num_live.chong_live[1] = false;
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
	NUM_LIVE num_live = { 1,true,true,{false,false,false},{false,false,false},{true,true} };
	for (int i = 1; i <= 4; i++) {
		if (Y - i < 0) {
			num_live.live[0] = false;
			break;
		}
		if (X - i < 0) {
			num_live.live[0] = false;
			break;
		}
		if (chessboard[X - i][Y - i].belong == stone_place.belong) {
			num_live.num++;
		}
		else if (chessboard[X - i][Y - i].belong != BLANK) {
			num_live.live[0] = false;
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
					else if (chessboard[X - i - j][Y - i - j].belong != BLANK) {
						num_live.chong_live[0] = false;
						break;
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
			num_live.live[1] = false;
			break;
		}
		if (Y + i > LENGTH - 1) {
			num_live.live[1] = false;
			break;
		}
		if (chessboard[X + i][Y + i].belong == stone_place.belong) {
			num_live.num++;
		}
		else if (chessboard[X + i][Y + i].belong != BLANK) {
			num_live.live[1] = false;
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
					else if (chessboard[X + i + j][Y + i + j].belong != BLANK) {
						num_live.chong_live[1] = false;
						break;
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
int evaluate_score(SPACE stone_place,SPACE chessboard[LENGTH][LENGTH]) {int evaluation = 0;
	const int sign = stone_place.belong == BLACK ? 1 : -1;
	const int X = stone_place.x, Y = stone_place.y;
	NUM_LIVE HSPN[4] = {check_continue_heng(stone_place, chessboard),
						check_continue_shu(stone_place, chessboard) , 
						check_continue_pie(stone_place, chessboard),
						check_continue_na(stone_place, chessboard) };
	switch (HSPN[0].num) {
		case 1:
			if (!(HSPN[0].live[0]) && !(HSPN[0].live[1])) {
				evaluation += DEAD_1;
			}
			else if (HSPN[0].live[0] && HSPN[0].live[1]) {
				evaluation += LIVE_1;
			}
			break;
		case 2:
			if (!(HSPN[0].live[0]) && !(HSPN[0].live[1])) {
				evaluation += DEAD_2;
			}
			else if (HSPN[0].live[0] && HSPN[0].live[1]) {
				evaluation += LIVE_2;
			}
			else {
				evaluation += SLEEP_2;
			}
			break;
		case 3:
			if (!(HSPN[0].live[0]) && !(HSPN[0].live[1])) {
				evaluation += DEAD_3;
			}
			else if (HSPN[0].live[0] && HSPN[0].live[1]) {
				evaluation += LIVE_3;
			}
			else {
				evaluation += SLEEP_3;
			}
			break;
		case 4:
			if (!(HSPN[0].live[0]) && !(HSPN[0].live[1])) {
				evaluation += DEAD_4;
			}
			else if (HSPN[0].live[0] && HSPN[0].live[1]) {
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
		if (!(HSPN[1].live[0]) && !(HSPN[1].live[1])) {
			evaluation += DEAD_1;
		}
		else if (HSPN[1].live[0] && HSPN[1].live[1]) {
			evaluation += LIVE_1;
		}
		break;
	case 2:
		if (!(HSPN[1].live[0]) && !(HSPN[1].live[1])) {
			evaluation += DEAD_2;
		}
		else if (HSPN[1].live[0] && HSPN[1].live[1]) {
			evaluation += LIVE_2;
		}
		else {
			evaluation += SLEEP_2;
		}
		break;
	case 3:
		if (!(HSPN[1].live[0]) && !(HSPN[1].live[1])) {
			evaluation += DEAD_3;
		}
		else if (HSPN[1].live[0] && HSPN[1].live[1]) {
			evaluation += LIVE_3;
		}
		else {
			evaluation += SLEEP_3;
		}
		break;
	case 4:
		if (!(HSPN[1].live[0]) && !(HSPN[1].live[1])) {
			evaluation += DEAD_4;
		}
		else if (HSPN[1].live[0] && HSPN[1].live[1]) {
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
		if (!(HSPN[2].live[0]) && !(HSPN[2].live[1])) {
			evaluation += DEAD_1;
		}
		else if (HSPN[2].live[0] && HSPN[2].live[1]) {
			evaluation += LIVE_1;
		}
		break;
	case 2:
		if (!(HSPN[2].live[0]) && !(HSPN[2].live[1])) {
			evaluation += DEAD_2;
		}
		else if (HSPN[2].live[0] && HSPN[2].live[1]) {
			evaluation += LIVE_2;
		}
		else {
			evaluation += SLEEP_2;
		}
		break;
	case 3:
		if (!(HSPN[2].live[0]) && !(HSPN[2].live[1])) {
			evaluation += DEAD_3;
		}
		else if (HSPN[2].live[0] && HSPN[2].live[1]) {
			evaluation += LIVE_3;
		}
		else {
			evaluation += SLEEP_3;
		}
		break;
	case 4:
		if (!(HSPN[2].live[0]) && !(HSPN[2].live[1])) {
			evaluation += DEAD_4;
		}
		else if (HSPN[2].live[0] && HSPN[2].live[1]) {
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
		if (!(HSPN[3].live[0]) && !(HSPN[3].live[1])) {
			evaluation += DEAD_1;
		}
		else if (HSPN[3].live[0] && HSPN[3].live[1]) {
			evaluation += LIVE_1;
		}
		break;
	case 2:
		if (!(HSPN[3].live[0]) && !(HSPN[3].live[1])) {
			evaluation += DEAD_2;
		}
		else if (HSPN[3].live[0] && HSPN[3].live[1]) {
			evaluation += LIVE_2;
		}
		else {
			evaluation += SLEEP_2;
		}
		break;
	case 3:
		if (!(HSPN[3].live[0]) && !(HSPN[3].live[1])) {
			evaluation += DEAD_3;
		}
		else if (HSPN[3].live[0] && HSPN[3].live[1]) {
			evaluation += LIVE_3;
		}
		else {
			evaluation += SLEEP_3;
		}
		break;
	case 4:
		if (!(HSPN[3].live[0]) && !(HSPN[3].live[1])) {
			evaluation += DEAD_4;
		}
		else if (HSPN[3].live[0] && HSPN[3].live[1]) {
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
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j <= 2; j++) {
			if (HSPN[i].chong_1[j]) {
				chong[2*i]++;
			}
			if (HSPN[i].chong_2[j]) {
				chong[2*i+1]++;
			}
		}
	}
	for (int i = 0; i < 8; i++) {
		if (chong[i] > 0) {
			if (HSPN[i / 2].chong_live[i % 2] && HSPN[i / 2].live[(i + 1) % 2]) {
				switch (HSPN[i / 2].num + chong[i]) {
				case 2:	evaluation += LIVE_CHONG_3;	break;
				case 3:	evaluation += LIVE_CHONG_4;  break;
				case 4: evaluation += CHONG_5;	break;
				}
			}
			else if (!(HSPN[i / 2].chong_live[i % 2]) && !(HSPN[i / 2].live[(i + 1) % 2])) {
				switch (HSPN[i / 2].num + chong[i]) {
				case 2:	evaluation += DEAD_CHONG_3;	break;
				case 3:	evaluation += DEAD_CHONG_4;  break;
				case 4: evaluation += CHONG_5;	break;
				}
			}
			else {
				switch (HSPN[i / 2].num + chong[i]) {
				case 2:	evaluation += SLEEP_CHONG_3;	break;
				case 3:	evaluation += SLEEP_CHONG_4;  break;
				case 4: evaluation += CHONG_5;	break;
				}
			}
		}
	}
	return evaluation;
}
