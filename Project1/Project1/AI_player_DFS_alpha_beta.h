#pragma once
#include"head_title_library.h"
#include"struct_library.h"
int has_neighbor(SPACE chessboard[LENGTH][LENGTH], int x, int y, int distance);int minimax(SPACE chessboard[LENGTH][LENGTH], int depth, int alpha, int beta, int maximizingPlayer, int color);
int minimax(SPACE chessboard[LENGTH][LENGTH], int depth, int alpha, int beta, int maximizingPlayer, int color);
int situation_assessment(SPACE chessboard[LENGTH][LENGTH], int color);
SPACE AI_player_optimized(SPACE chessboard[LENGTH][LENGTH], int color);
