#include"AI_player_DFS_alpha_beta.h"
int has_neighbor(SPACE chessboard[LENGTH][LENGTH], int x, int y, int distance) {
    for (int i = x - distance; i <= x + distance; i++) {
        for (int j = y - distance; j <= y + distance; j++) {
            if (i >= 0 && i < LENGTH && j >= 0 && j < LENGTH && !(i == x && j == y)) {
                if (chessboard[i][j].belong != BLANK) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
int minimax(SPACE chessboard[LENGTH][LENGTH], int depth, int alpha, int beta, int maximizingPlayer, int color) {
    if (depth == 0) {
        return situation_assessment(chessboard, color);
    }
    if (maximizingPlayer) {
        for (int i = 0; i < LENGTH; i++) {
            for (int j = 0; j < LENGTH; j++) {
                if (chessboard[i][j].belong == BLANK && has_neighbor(chessboard, i, j, 2)) {
                    chessboard[i][j].belong = color;
                    int eval = minimax(chessboard, depth - 1, alpha, beta, 0, color);
                    chessboard[i][j].belong = BLANK;
                    if (eval > alpha) {
                        alpha = eval;
                    }
                    if (beta <= alpha) {
                        goto next1; // β剪枝
                    }
                }
            }
        }
        next1:;
        return alpha;
    }
    else {
        int opponent_color = (color == BLACK ? WHITE : BLACK);
        for (int i = 0; i < LENGTH; i++) {
            for (int j = 0; j < LENGTH; j++) {
                if (chessboard[i][j].belong == BLANK && has_neighbor(chessboard, i, j, 2)) {
                    chessboard[i][j].belong = opponent_color;
                    int eval = minimax(chessboard, depth - 1, alpha, beta, 1, color);
                    chessboard[i][j].belong = BLANK;
                    if (eval < beta) {
                        beta = eval;
                    }
                    if (beta <= alpha) {
                        goto next2; // α剪枝
                    }
                }
            }
        }
        next2:;
        return beta;
    }
}
SPACE AI_player_optimized(SPACE chessboard[LENGTH][LENGTH], int color) {
    int bestScore = INT_MIN;
    int bestX = -1, bestY = -1;
    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < LENGTH; j++) {
            if (chessboard[i][j].belong == BLANK && has_neighbor(chessboard, i, j, 2)) {
                chessboard[i][j].belong = color;
                int score = minimax(chessboard, SEARCH_DEPTH - 1, INT_MIN, INT_MAX, 0, color);
                chessboard[i][j].belong = BLANK;
                if (score > bestScore) {
                    bestScore = score;
                    bestX = i;
                    bestY = j;
                }
            }
        }
    }
    // 如果没有找到合适的移动（开局情况），选择中心区域
    //测试发现这部分不可删去，删去会发生AI不落子但提示已落子的情况
    if (bestX == -1 || bestY == -1) {
        for (int i = LENGTH / 2 - 1; i <= LENGTH / 2 + 1; i++) {
            for (int j = LENGTH / 2 - 1; j <= LENGTH / 2 + 1; j++) {
                if (chessboard[i][j].belong == BLANK) {
                    chessboard[i][j].belong = color;
                    return chessboard[i][j];
                }
            }
        }
        for (int i = 0; i < LENGTH; i++) {
            for (int j = 0; j < LENGTH; j++) {
                if (chessboard[i][j].belong == BLANK) {
                    chessboard[i][j].belong = color;
                    return chessboard[i][j];
                }
            }
        }
    }
    else {
        chessboard[bestX][bestY].belong = color;
        return chessboard[bestX][bestY];
    }
}
int situation_assessment(SPACE chessboard[LENGTH][LENGTH], int color) {
    int situation_score = 0;
    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < LENGTH; j++) {
            if (chessboard[i][j].belong == color) {
                situation_score += evaluate_score(chessboard[i][j], chessboard);
            }
            else if (chessboard[i][j].belong == BLANK) {
                continue;
            }
            else {
                situation_score -= evaluate_score(chessboard[i][j], chessboard);
            }
        }
    }
    if (color == BLACK) {
        situation_score += 100;
    }
    return situation_score;
}