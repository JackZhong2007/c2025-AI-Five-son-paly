#pragma once
/*
#include"head_title_library.h"
#include"struct_library.h"
NUM_LIVE check_continue_heng(SPACE stone_place, SPACE chessboard[LENGTH][LENGTH]);
NUM_LIVE check_continue_shu(SPACE stone_place, SPACE chessboard[LENGTH][LENGTH]);
NUM_LIVE check_continue_pie(SPACE stone_place, SPACE chessboard[LENGTH][LENGTH]);
NUM_LIVE check_continue_na(SPACE stone_place, SPACE chessboard[LENGTH][LENGTH]);
int evaluate_score(SPACE stone_place, SPACE chessboard[LENGTH][LENGTH]);
*/
#include"head_title_library.h"
#include"struct_library.h"
typedef struct {
    int continuous;    // 连续棋子数
    int blocked_left;  // 左侧是否被阻挡
    int blocked_right; // 右侧是否被阻挡
    int has_jump;      // 是否有跳连
} Pattern;

// 函数声明
Pattern check_direction(SPACE stone_place, SPACE chessboard[LENGTH][LENGTH], int dx, int dy);
Pattern check_direction_simple(SPACE chessboard[LENGTH][LENGTH], int x, int y, int color, int dx, int dy);
int get_pattern_score(Pattern pattern);
int get_threat_score(Pattern pattern);
int evaluate_score(SPACE stone_place, SPACE chessboard[LENGTH][LENGTH]);
int evaluate_threat_level(SPACE chessboard[LENGTH][LENGTH], int x, int y, int color);