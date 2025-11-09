#pragma once
#include"head_title_library.h"
#include"struct_library.h"
int has_neighbor(SPACE chessboard[LENGTH][LENGTH], int x, int y, int distance);
int check_urgent_defense(SPACE chessboard[LENGTH][LENGTH], int color, int* defense_x, int* defense_y);
int minimax(SPACE chessboard[LENGTH][LENGTH], int depth, int alpha, int beta, int maximizingPlayer, int color);
int MIN(SPACE place, SPACE chessboard[LENGTH][LENGTH]);
int MAX(SPACE place, SPACE chessboard[LENGTH][LENGTH]);
void afa_beita(SPACE chessboard[LENGTH][LENGTH], int color);
void AI_player_offense(SPACE space[LENGTH][LENGTH], int color);
void AI_player_defense(SPACE space[LENGTH][LENGTH], int color);
int situation_assessment(SPACE chessboard[LENGTH][LENGTH], int color);
void AI_player_optimized(SPACE chessboard[LENGTH][LENGTH], int color);




/*
int has_neighbor(SPACE chessboard[LENGTH][LENGTH], int x, int y, int distance);
int check_urgent_defense(SPACE chessboard[LENGTH][LENGTH], int color, int* defense_x, int* defense_y);
int minimax(SPACE chessboard[LENGTH][LENGTH], int depth, int alpha, int beta, int maximizingPlayer, int color);
int MIN(SPACE place, SPACE chessboard[LENGTH][LENGTH]);
int MAX(SPACE place, SPACE chessboard[LENGTH][LENGTH]);
void afa_beita(SPACE chessboard[LENGTH][LENGTH], int color);
void AI_player_offense(SPACE space[LENGTH][LENGTH], int color);
void AI_player_defense(SPACE space[LENGTH][LENGTH], int color);
int situation_assessment(SPACE chessboard[LENGTH][LENGTH], int color);
void AI_player_optimized(SPACE chessboard[LENGTH][LENGTH], int color);
*/