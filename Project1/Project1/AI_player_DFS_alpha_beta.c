#include "AI_player_DFS_alpha_beta.h"

// 检查周围是否有棋子的辅助函数
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

// 紧急防守检查：检查是否有需要立即防守的威胁
int check_urgent_defense(SPACE chessboard[LENGTH][LENGTH], int color, int* defense_x, int* defense_y) {
    int opponent_color = (color == BLACK ? WHITE : BLACK);
    int max_threat = 0;
    int best_x = -1, best_y = -1;

    // 检查对手的所有可能落子点
    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < LENGTH; j++) {
            if (chessboard[i][j].belong == BLANK && has_neighbor(chessboard, i, j, 2)) {
                // 模拟对手落子
                chessboard[i][j].belong = opponent_color;

                // 评估威胁程度
                int threat = evaluate_threat_level(chessboard, i, j, opponent_color);

                // 回溯
                chessboard[i][j].belong = BLANK;

                if (threat > max_threat) {
                    max_threat = threat;
                    best_x = i;
                    best_y = j;
                }
            }
        }
    }

    // 根据威胁程度决定是否紧急防守
    if (max_threat >= 1000) { // 活三或更严重的威胁
        *defense_x = best_x;
        *defense_y = best_y;
        return 1;
    }

    return 0;
}

// 使用α-β剪枝的Minimax算法
int minimax(SPACE chessboard[LENGTH][LENGTH], int depth, int alpha, int beta, int maximizingPlayer, int color) {
    // 达到搜索深度，返回局面评估
    if (depth == 0) {
        return situation_assessment(chessboard, color);
    }

    if (maximizingPlayer) {
        int maxEval = INT_MIN;
        int move_found = 0;

        for (int i = 0; i < LENGTH; i++) {
            for (int j = 0; j < LENGTH; j++) {
                // 只搜索有棋子周围的区域（2格范围内）
                if (chessboard[i][j].belong == BLANK && has_neighbor(chessboard, i, j, 2)) {
                    move_found = 1;

                    // 尝试落子
                    chessboard[i][j].belong = color;
                    int eval = minimax(chessboard, depth - 1, alpha, beta, 0, color);
                    // 回溯
                    chessboard[i][j].belong = BLANK;

                    if (eval > maxEval) {
                        maxEval = eval;
                    }

                    if (eval > alpha) {
                        alpha = eval;
                    }

                    if (beta <= alpha) {
                        break; // β剪枝
                    }
                }
            }
            if (beta <= alpha) break;
        }

        // 如果没有找到合适的移动，随机选择一个有邻居的位置
        if (!move_found) {
            for (int i = 0; i < LENGTH; i++) {
                for (int j = 0; j < LENGTH; j++) {
                    if (chessboard[i][j].belong == BLANK && has_neighbor(chessboard, i, j, 2)) {
                        chessboard[i][j].belong = color;
                        int eval = situation_assessment(chessboard, color);
                        chessboard[i][j].belong = BLANK;
                        return eval;
                    }
                }
            }
        }

        return maxEval;
    }
    else {
        int minEval = INT_MAX;
        int opponent_color = (color == BLACK ? WHITE : BLACK);
        int move_found = 0;

        for (int i = 0; i < LENGTH; i++) {
            for (int j = 0; j < LENGTH; j++) {
                // 只搜索有棋子周围的区域
                if (chessboard[i][j].belong == BLANK && has_neighbor(chessboard, i, j, 2)) {
                    move_found = 1;

                    // 对手落子
                    chessboard[i][j].belong = opponent_color;
                    int eval = minimax(chessboard, depth - 1, alpha, beta, 1, color);
                    // 回溯
                    chessboard[i][j].belong = BLANK;

                    if (eval < minEval) {
                        minEval = eval;
                    }

                    if (eval < beta) {
                        beta = eval;
                    }

                    if (beta <= alpha) {
                        break; // α剪枝
                    }
                }
            }
            if (beta <= alpha) break;
        }

        if (!move_found) {
            for (int i = 0; i < LENGTH; i++) {
                for (int j = 0; j < LENGTH; j++) {
                    if (chessboard[i][j].belong == BLANK && has_neighbor(chessboard, i, j, 2)) {
                        chessboard[i][j].belong = opponent_color;
                        int eval = situation_assessment(chessboard, color);
                        chessboard[i][j].belong = BLANK;
                        return eval;
                    }
                }
            }
        }

        return minEval;
    }
}

// 补全MIN函数
int MIN(SPACE place, SPACE chessboard[LENGTH][LENGTH]) {
    int opponent_color = (place.belong == BLACK ? WHITE : BLACK);
    // 计算位置索引
    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < LENGTH; j++) {
            if (&chessboard[i][j] == &place) {
                chessboard[i][j].belong = opponent_color;
                int score = situation_assessment(chessboard, place.belong);
                chessboard[i][j].belong = BLANK;
                return score;
            }
        }
    }
    return 0;
}

// 补全MAX函数  
int MAX(SPACE place, SPACE chessboard[LENGTH][LENGTH]) {
    // 计算位置索引
    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < LENGTH; j++) {
            if (&chessboard[i][j] == &place) {
                chessboard[i][j].belong = place.belong;
                int score = situation_assessment(chessboard, place.belong);
                chessboard[i][j].belong = BLANK;
                return score;
            }
        }
    }
    return 0;
}

// 使用α-β剪枝的主函数
void afa_beita(SPACE chessboard[LENGTH][LENGTH], int color) {
    int defense_x, defense_y;

    // 首先检查是否需要紧急防守
    if (check_urgent_defense(chessboard, color, &defense_x, &defense_y)) {
        chessboard[defense_x][defense_y].belong = color;
        return;
    }

    int bestScore = INT_MIN;
    int bestX = -1, bestY = -1;

    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < LENGTH; j++) {
            // 只考虑有棋子周围的空位
            if (chessboard[i][j].belong == BLANK && has_neighbor(chessboard, i, j, 2)) {
                // 尝试落子
                chessboard[i][j].belong = color;
                int score = minimax(chessboard, SEARCH_DEPTH - 1, INT_MIN, INT_MAX, 0, color);
                // 回溯
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
    if (bestX == -1 || bestY == -1) {
        for (int i = LENGTH / 2 - 1; i <= LENGTH / 2 + 1; i++) {
            for (int j = LENGTH / 2 - 1; j <= LENGTH / 2 + 1; j++) {
                if (chessboard[i][j].belong == BLANK) {
                    chessboard[i][j].belong = color;
                    return;
                }
            }
        }
        // 如果中心都被占了，随便找个位置
        for (int i = 0; i < LENGTH; i++) {
            for (int j = 0; j < LENGTH; j++) {
                if (chessboard[i][j].belong == BLANK) {
                    chessboard[i][j].belong = color;
                    return;
                }
            }
        }
    }
    else {
        chessboard[bestX][bestY].belong = color;
    }
}

// 改进的进攻AI
void AI_player_offense(SPACE space[LENGTH][LENGTH], int color) {
    afa_beita(space, color);
}

// 改进的防守AI
void AI_player_defense(SPACE space[LENGTH][LENGTH], int color) {
    afa_beita(space, color);
}

// 局面评估函数
int situation_assessment(SPACE chessboard[LENGTH][LENGTH], int color) {
    int situation_score = 0;
    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < LENGTH; j++) {
            if (chessboard[i][j].belong == color) {
                SPACE stone = { i, j, color };
                situation_score += evaluate_score(stone, chessboard);
            }
            else if (chessboard[i][j].belong == BLANK) {
                continue;
            }
            else {
                SPACE stone = { i, j, chessboard[i][j].belong };
                situation_score -= evaluate_score(stone, chessboard);
            }
        }
    }
    if (color == BLACK) {
        situation_score += 100;
    }
    return situation_score;
}

// 优化的AI落子函数
void AI_player_optimized(SPACE chessboard[LENGTH][LENGTH], int color) {
    afa_beita(chessboard, color);
}





/*
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
int check_urgent_defense(SPACE chessboard[LENGTH][LENGTH], int color, int* defense_x, int* defense_y) {
    int opponent_color = (color == BLACK ? WHITE : BLACK);
    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < LENGTH; j++) {
            if (chessboard[i][j].belong == BLANK) {
                chessboard[i][j].belong = opponent_color;
                if (evaluate_score(chessboard[i][j], chessboard) >= 2000) { 
                    *defense_x = i;
                    *defense_y = j;
                    chessboard[i][j].belong = BLANK;
                    return 1; 
                }
                chessboard[i][j].belong = BLANK;
            }
        }
    }
    return 0;
}

// 优化的minimax函数，只搜索有意义的区域
int minimax(SPACE chessboard[LENGTH][LENGTH], int depth, int alpha, int beta, int maximizingPlayer, int color) {
    // 达到搜索深度，返回局面评估
    if (depth == 0) {
        return situation_assessment(chessboard, color);
    }

    if (maximizingPlayer) {
        int maxEval = INT_MIN;
        int move_found = 0;

        for (int i = 0; i < LENGTH; i++) {
            for (int j = 0; j < LENGTH; j++) {
                // 只搜索有棋子周围的区域（2格范围内）
                if (chessboard[i][j].belong == BLANK && has_neighbor(chessboard, i, j, 2)) {
                    move_found = 1;

                    // 尝试落子
                    chessboard[i][j].belong = color;
                    int eval = minimax(chessboard, depth - 1, alpha, beta, 0, color);
                    // 回溯
                    chessboard[i][j].belong = BLANK;

                    if (eval > maxEval) {
                        maxEval = eval;
                    }

                    if (eval > alpha) {
                        alpha = eval;
                    }

                    if (beta <= alpha) {
                        break; // β剪枝
                    }
                }
            }
            if (beta <= alpha) break;
        }

        // 如果没有找到合适的移动，随机选择一个有邻居的位置
        if (!move_found) {
            for (int i = 0; i < LENGTH; i++) {
                for (int j = 0; j < LENGTH; j++) {
                    if (chessboard[i][j].belong == BLANK && has_neighbor(chessboard, i, j, 2)) {
                        chessboard[i][j].belong = color;
                        int eval = situation_assessment(chessboard, color);
                        chessboard[i][j].belong = BLANK;
                        return eval;
                    }
                }
            }
        }

        return maxEval;
    }
    else {
        int minEval = INT_MAX;
        int opponent_color = (color == BLACK ? WHITE : BLACK);
        int move_found = 0;

        for (int i = 0; i < LENGTH; i++) {
            for (int j = 0; j < LENGTH; j++) {
                // 只搜索有棋子周围的区域
                if (chessboard[i][j].belong == BLANK && has_neighbor(chessboard, i, j, 2)) {
                    move_found = 1;

                    // 对手落子
                    chessboard[i][j].belong = opponent_color;
                    int eval = minimax(chessboard, depth - 1, alpha, beta, 1, color);
                    // 回溯
                    chessboard[i][j].belong = BLANK;

                    if (eval < minEval) {
                        minEval = eval;
                    }

                    if (eval < beta) {
                        beta = eval;
                    }

                    if (beta <= alpha) {
                        break; // α剪枝
                    }
                }
            }
            if (beta <= alpha) break;
        }

        if (!move_found) {
            for (int i = 0; i < LENGTH; i++) {
                for (int j = 0; j < LENGTH; j++) {
                    if (chessboard[i][j].belong == BLANK && has_neighbor(chessboard, i, j, 2)) {
                        chessboard[i][j].belong = opponent_color;
                        int eval = situation_assessment(chessboard, color);
                        chessboard[i][j].belong = BLANK;
                        return eval;
                    }
                }
            }
        }

        return minEval;
    }
}

// 补全MIN函数
int MIN(SPACE place, SPACE chessboard[LENGTH][LENGTH]) {
    int opponent_color = (place.belong == BLACK ? WHITE : BLACK);
    // 计算位置索引
    int index = -1;
    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < LENGTH; j++) {
            if (&chessboard[i][j] == &place) {
                chessboard[i][j].belong = opponent_color;
                int score = situation_assessment(chessboard, place.belong);
                chessboard[i][j].belong = BLANK;
                return score;
            }
        }
    }
    return 0;
}

// 补全MAX函数  
int MAX(SPACE place, SPACE chessboard[LENGTH][LENGTH]) {
    // 计算位置索引
    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < LENGTH; j++) {
            if (&chessboard[i][j] == &place) {
                chessboard[i][j].belong = place.belong;
                int score = situation_assessment(chessboard, place.belong);
                chessboard[i][j].belong = BLANK;
                return score;
            }
        }
    }
    return 0;
}

// 改进的α-β剪枝主函数
void afa_beita(SPACE chessboard[LENGTH][LENGTH], int color) {
    int defense_x, defense_y;

    // 首先检查是否需要紧急防守
    if (check_urgent_defense(chessboard, color, &defense_x, &defense_y)) {
        chessboard[defense_x][defense_y].belong = color;
        return;
    }

    int bestScore = INT_MIN;
    int bestX = -1, bestY = -1;

    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < LENGTH; j++) {
            // 只考虑有棋子周围的空位
            if (chessboard[i][j].belong == BLANK && has_neighbor(chessboard, i, j, 2)) {
                // 尝试落子
                chessboard[i][j].belong = color;
                int score = minimax(chessboard, SEARCH_DEPTH - 1, INT_MIN, INT_MAX, 0, color);
                // 回溯
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
    if (bestX == -1 || bestY == -1) {
        for (int i = LENGTH / 2 - 1; i <= LENGTH / 2 + 1; i++) {
            for (int j = LENGTH / 2 - 1; j <= LENGTH / 2 + 1; j++) {
                if (chessboard[i][j].belong == BLANK) {
                    chessboard[i][j].belong = color;
                    return;
                }
            }
        }
        // 如果中心都被占了，随便找个位置
        for (int i = 0; i < LENGTH; i++) {
            for (int j = 0; j < LENGTH; j++) {
                if (chessboard[i][j].belong == BLANK) {
                    chessboard[i][j].belong = color;
                    return;
                }
            }
        }
    }
    else {
        chessboard[bestX][bestY].belong = color;
    }
}

// 改进的进攻AI
void AI_player_offense(SPACE space[LENGTH][LENGTH], int color) {
    afa_beita(space, color);
}

// 改进的防守AI
void AI_player_defense(SPACE space[LENGTH][LENGTH], int color) {
    afa_beita(space, color);
}

// 局面评估函数
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

// 优化的AI落子函数
void AI_player_optimized(SPACE chessboard[LENGTH][LENGTH], int color) {
    afa_beita(chessboard, color);
}
*/






/*
#include"AI_player_DFS_alpha_beta.h"

// 使用α-β剪枝的Minimax算法
int minimax(SPACE chessboard[LENGTH][LENGTH], int depth, int alpha, int beta, int maximizingPlayer, int color) {
    // 达到搜索深度或游戏结束，返回局面评估
    if (depth == 0) {
        return situation_assessment(chessboard, color);
    }
    if (maximizingPlayer) {
        int maxEval = INT_MIN;
        for (int i = 0; i < LENGTH; i++) {
            for (int j = 0; j < LENGTH; j++) {
                if (chessboard[i][j].belong == BLANK) {
                    // 尝试落子
                    chessboard[i][j].belong = color;
                    int eval = minimax(chessboard, depth - 1, alpha, beta, 0, color);
                    // 回溯
                    chessboard[i][j].belong = BLANK;

                    if (eval > maxEval) {
                        maxEval = eval;
                    }

                    if (eval > alpha) {
                        alpha = eval;
                    }

                    if (beta <= alpha) {
                        break; // β剪枝
                    }
                }
            }
        }
        return maxEval;
    }
    else {
        int minEval = INT_MAX;
        int opponent_color = (color == BLACK ? WHITE : BLACK);

        for (int i = 0; i < LENGTH; i++) {
            for (int j = 0; j < LENGTH; j++) {
                if (chessboard[i][j].belong == BLANK) {
                    // 对手落子
                    chessboard[i][j].belong = opponent_color;
                    int eval = minimax(chessboard, depth - 1, alpha, beta, 1, color);
                    // 回溯
                    chessboard[i][j].belong = BLANK;

                    if (eval < minEval) {
                        minEval = eval;
                    }

                    if (eval < beta) {
                        beta = eval;
                    }

                    if (beta <= alpha) {
                        break; // α剪枝
                    }
                }
            }
        }
        return minEval;
    }
}

// 补全MIN函数 - 最小层搜索
int MIN(SPACE place, SPACE chessboard[LENGTH][LENGTH]) {
    // 这个函数可以整合到minimax中，但为了保持接口，我们这样实现：
    int opponent_color = (place.belong == BLACK ? WHITE : BLACK);
    chessboard[(int)(&place - &chessboard[0][0]) / LENGTH][(int)(&place - &chessboard[0][0]) % LENGTH].belong = opponent_color;
    int score = situation_assessment(chessboard, place.belong);
    chessboard[(int)(&place - &chessboard[0][0]) / LENGTH][(int)(&place - &chessboard[0][0]) % LENGTH].belong = BLANK;
    return score;
}

// 补全MAX函数 - 最大层搜索  
int MAX(SPACE place, SPACE chessboard[LENGTH][LENGTH]) {
    chessboard[(int)(&place - &chessboard[0][0]) / LENGTH][(int)(&place - &chessboard[0][0]) % LENGTH].belong = place.belong;
    int score = situation_assessment(chessboard, place.belong);
    chessboard[(int)(&place - &chessboard[0][0]) / LENGTH][(int)(&place - &chessboard[0][0]) % LENGTH].belong = BLANK;
    return score;
}

// 使用α-β剪枝的主函数
void afa_beita(SPACE chessboard[LENGTH][LENGTH]) {
    int bestScore = INT_MIN;
    int bestX = -1, bestY = -1;
    int current_color = BLACK; // 可以根据实际情况调整

    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < LENGTH; j++) {
            if (chessboard[i][j].belong == BLANK) {
                // 尝试落子
                chessboard[i][j].belong = current_color;
                int score = minimax(chessboard, SEARCH_DEPTH - 1, INT_MIN, INT_MAX, 0, current_color);
                // 回溯
                chessboard[i][j].belong = BLANK;

                if (score > bestScore) {
                    bestScore = score;
                    bestX = i;
                    bestY = j;
                }
            }
        }
    }

    if (bestX != -1 && bestY != -1) {
        chessboard[bestX][bestY].belong = current_color;
    }
}

// 改进的进攻AI，使用α-β剪枝
void AI_player_offense(SPACE space[LENGTH][LENGTH], int color) {
    afa_beita(space);
}

// 改进的防守AI，使用α-β剪枝
void AI_player_defense(SPACE space[LENGTH][LENGTH], int color) {
    // 防守时可以考虑调整评估函数权重
    afa_beita(space);
}

// 局面评估函数（已存在）
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

// 优化的AI落子函数，结合进攻和防守
void AI_player_optimized(SPACE chessboard[LENGTH][LENGTH], int color) {
    int bestScore = INT_MIN;
    int bestX = -1, bestY = -1;

    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < LENGTH; j++) {
            if (chessboard[i][j].belong == BLANK) {
                // 进攻评估
                chessboard[i][j].belong = color;
                int offense_score = minimax(chessboard, SEARCH_DEPTH - 1, INT_MIN, INT_MAX, 0, color);
                chessboard[i][j].belong = BLANK;

                // 防守评估
                int opponent_color = (color == BLACK ? WHITE : BLACK);
                chessboard[i][j].belong = opponent_color;
                int defense_score = minimax(chessboard, SEARCH_DEPTH - 1, INT_MIN, INT_MAX, 0, color);
                chessboard[i][j].belong = BLANK;

                // 综合评分（可以根据需要调整权重）
                int total_score = offense_score * 0.6 + defense_score * 0.4;

                if (total_score > bestScore) {
                    bestScore = total_score;
                    bestX = i;
                    bestY = j;
                }
            }
        }
    }

    if (bestX != -1 && bestY != -1) {
        chessboard[bestX][bestY].belong = color;
    }
}
*/