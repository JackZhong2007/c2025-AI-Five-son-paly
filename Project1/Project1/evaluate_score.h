#pragma once
#include"head_title_library.h"
#include"struct_library.h"
int check_continue_heng(SPACE stone_place, SPACE chessboard[LENGTH][LENGTH]);
int check_continue_shu(SPACE stone_place, SPACE chessboard[LENGTH][LENGTH]);
int check_continue_pie(SPACE stone_place, SPACE chessboard[LENGTH][LENGTH]);
int check_continue_na(SPACE stone_place, SPACE chessboard[LENGTH][LENGTH]);
void evaluate_score(SPACE stone_place, SPACE chessboard[LENGTH][LENGTH]);