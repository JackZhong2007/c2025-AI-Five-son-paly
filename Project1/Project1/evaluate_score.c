#include "evaluate_score.h"

// 检查一个方向的连续棋子模式
Pattern check_direction(SPACE stone_place, SPACE chessboard[LENGTH][LENGTH], int dx, int dy) {
	Pattern pattern = { 1, 0, 0, 0 };
	int x = stone_place.x, y = stone_place.y;
	int color = stone_place.belong;

	// 检查左侧/上方
	for (int i = 1; i <= 4; i++) {
		int nx = x - i * dx, ny = y - i * dy;
		if (nx < 0 || nx >= LENGTH || ny < 0 || ny >= LENGTH) {
			pattern.blocked_left = 1;
			break;
		}
		if (chessboard[nx][ny].belong == color) {
			pattern.continuous++;
		}
		else if (chessboard[nx][ny].belong == BLANK) {
			// 检查是否有跳连
			int nnx = nx - dx, nny = ny - dy;
			if (nnx >= 0 && nnx < LENGTH && nny >= 0 && nny < LENGTH &&
				chessboard[nnx][nny].belong == color) {
				pattern.has_jump = 1;
			}
			break;
		}
		else {
			pattern.blocked_left = 1;
			break;
		}
	}

	// 检查右侧/下方
	for (int i = 1; i <= 4; i++) {
		int nx = x + i * dx, ny = y + i * dy;
		if (nx < 0 || nx >= LENGTH || ny < 0 || ny >= LENGTH) {
			pattern.blocked_right = 1;
			break;
		}
		if (chessboard[nx][ny].belong == color) {
			pattern.continuous++;
		}
		else if (chessboard[nx][ny].belong == BLANK) {
			// 检查是否有跳连
			int nnx = nx + dx, nny = ny + dy;
			if (nnx >= 0 && nnx < LENGTH && nny >= 0 && nny < LENGTH &&
				chessboard[nnx][nny].belong == color) {
				pattern.has_jump = 1;
			}
			break;
		}
		else {
			pattern.blocked_right = 1;
			break;
		}
	}

	return pattern;
}

// 简化的方向检查（专注于威胁识别）
Pattern check_direction_simple(SPACE chessboard[LENGTH][LENGTH], int x, int y, int color, int dx, int dy) {
	Pattern pattern = { 1, 0, 0, 0 };

	// 检查正向
	for (int i = 1; i <= 4; i++) {
		int nx = x + i * dx, ny = y + i * dy;
		if (nx < 0 || nx >= LENGTH || ny < 0 || ny >= LENGTH) {
			pattern.blocked_right = 1;
			break;
		}
		if (chessboard[nx][ny].belong == color) {
			pattern.continuous++;
		}
		else {
			if (chessboard[nx][ny].belong == BLANK) {
				// 空位，不阻挡
			}
			else {
				pattern.blocked_right = 1;
			}
			break;
		}
	}

	// 检查反向
	for (int i = 1; i <= 4; i++) {
		int nx = x - i * dx, ny = y - i * dy;
		if (nx < 0 || nx >= LENGTH || ny < 0 || ny >= LENGTH) {
			pattern.blocked_left = 1;
			break;
		}
		if (chessboard[nx][ny].belong == color) {
			pattern.continuous++;
		}
		else {
			if (chessboard[nx][ny].belong == BLANK) {
				// 空位，不阻挡
			}
			else {
				pattern.blocked_left = 1;
			}
			break;
		}
	}

	return pattern;
}

// 根据模式计算分数（进攻）
int get_pattern_score(Pattern pattern) {
	int continuous = pattern.continuous;
	int blocked_left = pattern.blocked_left;
	int blocked_right = pattern.blocked_right;

	// 连五直接胜利
	if (continuous >= 5) {
		return LIVE_5;
	}

	// 根据连续数和阻挡情况判断棋形
	switch (continuous) {
	case 1:
		if (!blocked_left && !blocked_right) return LIVE_1;
		return DEAD_1;

	case 2:
		if (!blocked_left && !blocked_right) return LIVE_2;
		else if (blocked_left != blocked_right) return SLEEP_2;
		return DEAD_2;

	case 3:
		if (!blocked_left && !blocked_right) {
			return LIVE_3;
		}
		else if (blocked_left != blocked_right) {
			// 冲三：一端被阻挡，另一端空
			return CHONG_3;
		}
		else {
			// 两端都被阻挡，是死三
			return SLEEP_3;
		}

	case 4:
		if (!blocked_left && !blocked_right) {
			return LIVE_4;
		}
		else if (blocked_left != blocked_right) {
			// 冲四：一端被阻挡，另一端空
			return CHONG_4;
		}
		else {
			// 两端都被阻挡，是眠四
			return SLEEP_4;
		}

	default:
		return 0;
	}
}

// 威胁分数计算（专注于防守）
int get_threat_score(Pattern pattern) {
	int continuous = pattern.continuous;
	int blocked_left = pattern.blocked_left;
	int blocked_right = pattern.blocked_right;

	if (continuous >= 5) return 100000; // 连五

	switch (continuous) {
	case 4:
		if (!blocked_left && !blocked_right) return 10000; // 活四
		else if (blocked_left != blocked_right) return 5000; // 冲四
		else return 1000; // 眠四

	case 3:
		if (!blocked_left && !blocked_right) return 1000; // 活三
		else if (blocked_left != blocked_right) return 500; // 冲三
		else return 100; // 眠三

	case 2:
		if (!blocked_left && !blocked_right) return 50; // 活二
		else if (blocked_left != blocked_right) return 20; // 冲二
		else return 5; // 眠二

	default:
		return 0;
	}
}

// 专门评估威胁程度的函数
int evaluate_threat_level(SPACE chessboard[LENGTH][LENGTH], int x, int y, int color) {
	int threat_score = 0;

	// 检查四个方向的威胁
	int directions[4][2] = { {0, 1}, {1, 0}, {1, 1}, {1, -1} };

	for (int i = 0; i < 4; i++) {
		Pattern pattern = check_direction_simple(chessboard, x, y, color, directions[i][0], directions[i][1]);
		threat_score += get_threat_score(pattern);
	}

	return threat_score;
}

// 简化的评估函数
int evaluate_score(SPACE stone_place, SPACE chessboard[LENGTH][LENGTH]) {
	int score = 0;
	int x = stone_place.x, y = stone_place.y;
	int color = stone_place.belong;
	int opponent_color = (color == BLACK ? WHITE : BLACK);

	// 进攻分数：这个落子对己方的价值
	int offense_score = 0;
	int directions[4][2] = { {0, 1}, {1, 0}, {1, 1}, {1, -1} };

	for (int i = 0; i < 4; i++) {
		Pattern pattern = check_direction(stone_place, chessboard, directions[i][0], directions[i][1]);
		offense_score += get_pattern_score(pattern);
	}

	// 防守分数：这个落子对对手的阻碍
	int defense_score = 0;

	// 检查这个落子是否阻止了对手的威胁
	for (int i = 0; i < 4; i++) {
		// 检查这个位置对对手的价值
		SPACE temp = { x, y, opponent_color };
		Pattern opponent_pattern = check_direction(temp, chessboard, directions[i][0], directions[i][1]);
		int opponent_threat = get_threat_score(opponent_pattern);

		// 如果这个位置原本对对手有很大威胁，现在被我们占了，给予防守加分
		if (opponent_threat > 500) { // 活三或更严重的威胁
			defense_score += opponent_threat * 0.8; // 防守价值是威胁价值的80%
		}
	}

	// 综合分数：进攻 + 防守
	score = offense_score + defense_score;

	// 额外加分：中心位置优势
	int center_x = LENGTH / 2, center_y = LENGTH / 2;
	int distance = abs(x - center_x) + abs(y - center_y);
	score += (LENGTH - distance) * 2;

	return score;
}










/*
#include"evaluate_score.h"

// 新的分数设置
#define DEAD_1 0
#define LIVE_1 1

#define DEAD_2 0
#define SLEEP_2 5
#define LIVE_2 20

#define DEAD_3 0
#define SLEEP_3 50
#define CHONG_3 100
#define LIVE_3 500

#define DEAD_4 0
#define SLEEP_4 800
#define CHONG_4 2000
#define LIVE_4 10000

#define LIVE_5 100000

// 简化的模式识别结构
typedef struct {
	int continuous;    // 连续棋子数
	int blocked_left;  // 左侧是否被阻挡
	int blocked_right; // 右侧是否被阻挡
	int has_jump;      // 是否有跳连
} Pattern;

// 检查一个方向的连续棋子模式
Pattern check_direction(SPACE stone_place, SPACE chessboard[LENGTH][LENGTH], int dx, int dy) {
	Pattern pattern = { 1, 0, 0, 0 };
	int x = stone_place.x, y = stone_place.y;
	int color = stone_place.belong;

	// 检查左侧/上方
	for (int i = 1; i <= 4; i++) {
		int nx = x - i * dx, ny = y - i * dy;
		if (nx < 0 || nx >= LENGTH || ny < 0 || ny >= LENGTH) {
			pattern.blocked_left = 1;
			break;
		}
		if (chessboard[nx][ny].belong == color) {
			pattern.continuous++;
		}
		else if (chessboard[nx][ny].belong == BLANK) {
			// 检查是否有跳连
			int nnx = nx - dx, nny = ny - dy;
			if (nnx >= 0 && nnx < LENGTH && nny >= 0 && nny < LENGTH &&
				chessboard[nnx][nny].belong == color) {
				pattern.has_jump = 1;
			}
			break;
		}
		else {
			pattern.blocked_left = 1;
			break;
		}
	}

	// 检查右侧/下方
	for (int i = 1; i <= 4; i++) {
		int nx = x + i * dx, ny = y + i * dy;
		if (nx < 0 || nx >= LENGTH || ny < 0 || ny >= LENGTH) {
			pattern.blocked_right = 1;
			break;
		}
		if (chessboard[nx][ny].belong == color) {
			pattern.continuous++;
		}
		else if (chessboard[nx][ny].belong == BLANK) {
			// 检查是否有跳连
			int nnx = nx + dx, nny = ny + dy;
			if (nnx >= 0 && nnx < LENGTH && nny >= 0 && nny < LENGTH &&
				chessboard[nnx][nny].belong == color) {
				pattern.has_jump = 1;
			}
			break;
		}
		else {
			pattern.blocked_right = 1;
			break;
		}
	}

	return pattern;
}

// 根据模式计算分数
int get_pattern_score(Pattern pattern) {
	int continuous = pattern.continuous;
	int blocked_left = pattern.blocked_left;
	int blocked_right = pattern.blocked_right;
	int has_jump = pattern.has_jump;

	// 连五直接胜利
	if (continuous >= 5) {
		return LIVE_5;
	}

	// 根据连续数和阻挡情况判断棋形
	switch (continuous) {
	case 1:
		if (!blocked_left && !blocked_right) return LIVE_1;
		return DEAD_1;

	case 2:
		if (!blocked_left && !blocked_right) return LIVE_2;
		else if (blocked_left != blocked_right) return SLEEP_2;
		return DEAD_2;

	case 3:
		if (!blocked_left && !blocked_right) {
			return LIVE_3;
		}
		else if (blocked_left != blocked_right) {
			// 冲三：一端被阻挡，另一端空
			return CHONG_3;
		}
		else {
			// 两端都被阻挡，是死三
			return SLEEP_3;
		}

	case 4:
		if (!blocked_left && !blocked_right) {
			return LIVE_4;
		}
		else if (blocked_left != blocked_right) {
			// 冲四：一端被阻挡，另一端空
			return CHONG_4;
		}
		else {
			// 两端都被阻挡，是眠四
			return SLEEP_4;
		}

	default:
		return 0;
	}
}

// 简化的评估函数
int evaluate_score(SPACE stone_place, SPACE chessboard[LENGTH][LENGTH]) {
	int score = 0;
	int x = stone_place.x, y = stone_place.y;

	// 检查四个方向：水平、垂直、两个对角线
	int directions[4][2] = { {0, 1}, {1, 0}, {1, 1}, {1, -1} };

	for (int i = 0; i < 4; i++) {
		Pattern pattern = check_direction(stone_place, chessboard, directions[i][0], directions[i][1]);
		score += get_pattern_score(pattern);
	}

	// 额外加分：中心位置优势
	int center_x = LENGTH / 2, center_y = LENGTH / 2;
	int distance = abs(x - center_x) + abs(y - center_y);
	score += (LENGTH - distance) * 2;  // 离中心越近，分数越高

	return score;
}
*/









/*
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
		if (HSPN[0].chong_1[i])		chong[0]++;
		if (HSPN[0].chong_2[i])		chong[1]++;
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
*/
