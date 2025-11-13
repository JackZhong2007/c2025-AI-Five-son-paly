# 项目报告
项目名称：AI五子棋  
学生：钟俊凯  
学号：2025080901027
# 项目内容
项目目标：在控制台实现人机对战五子棋游戏  
核心功能：一个具备较为强大的攻防能力的AI  
技术亮点：使用alpha-beta剪枝加速极小化极大算法，DFS  
成果：AI具有较强算力，程序运行稳定  
# 项目概述
操作系统：WIN11  
编程语言：C  
IDE:VS2022  
# 系统设计
系统架构图：1.游戏前置准备  2.随机执黑执白  3.轮流落子  4.每次落子后检验是否胜利
# 模块详细设计：
1.数据结构设计：  
棋盘空间&棋盘空间状态枚举  
typedef struct {  
    int x;  
    int y;  
    int belong;  
}SPACE;  
使用一个二维数组SPACE chessboard[LENGTH][LENGTH]作为棋盘，其中LENGTH为棋盘长度15；x,y分别为line和column；belong有三种状态：typedef enum { BLACK, WHITE, BLANK }STATUS;  
棋形结构  
typedef struct {  
    int num;  
    bool live[2];  
    bool chong_1[3];  
    bool chong_2[3];  
    bool chong_live[2];  
}NUM_LIVE;  
棋形由连续子数码Num和是否“活”两部分组成，该结构以此命名。  
我将棋形分为了“活”，“死”，“眠”，“冲”这四个部分，其中“冲”比较特殊，又细分为了“活冲”，“死冲”，“眠冲”，而Num就是简单的一到五这五个情况。  
不同棋形有着不同的分值，而NUM_LIVE的成员作用为：num代表主体连续数，bool live[2]的两个量分别代指两端是否为“活”（是否被对方堵住或者被棋盘大小限制），bool chong_1[3]和bool   chong_2[3]分别判断在主体两端由于空白空间而中止计数时，两端是否由于“冲”棋形而产生只有中间断了一个的“连续”棋形，其中[3]是为计数，bool chong_live[2]是为判断越过空白后的子是否为“活”  
2.功能模块设计  
（1）main.c:游戏开始前置准备，主循环——一方落子->判定是否获胜->另一方落子->判断是否或者  
（2）head_title_library.h:包含一系列头文件，宏定义，类定义，方便调用  
（3）before_begin.c：包含三个函数：  void console_individual(); ->隐藏光标  
                             int before_begin(); ->UI界面，随机设置执黑和执白方  
                             void set_individual_chessboard(SPACE chessboard[LENGTH][LENGTH]); ->棋盘初始化  
（4）print_chessboard.c:包含一个函数： void print_chessboard(SPACE chessboard[15][15]); ->打印棋盘的当前落子情况  
（5）human_player_play.c:包含一个函数： void human_player_play(int ,int ,SPACE space[LENGTH][LENGTH],int ); ->人类玩家输入落子位置并落子  
（6）viction_condition.c:包含一个函数： int victory_condition(SPACE space[LENGTH][LENGTH]); ->判断当前棋局是否有五连子  
（7）evaluate_score.c:包含五个函数： NUM_LIVE check_continue_heng(SPACE stone_place, SPACE chessboard[LENGTH][LENGTH]); ->计数当前落子位置“横”方向棋形要素  
NUM_LIVE check_continue_shu(SPACE stone_place, SPACE chessboard[LENGTH][LENGTH]); ->计数当前落子位置“竖”方向棋形要素  
NUM_LIVE check_continue_pie(SPACE stone_place, SPACE chessboard[LENGTH][LENGTH]); ->计数当前落子位置“撇”方向棋形要素  
NUM_LIVE check_continue_na(SPACE stone_place, SPACE chessboard[LENGTH][LENGTH]); ->计数当前落子位置“捺”方向棋形要素  
int evaluate_score(SPACE stone_place, SPACE chessboard[LENGTH][LENGTH]); ->统计当前位置在当前棋局下的总得分  
（8）AI_player_DFS_alpha_beta.c:包含四个函数： int has_neighbor(SPACE chessboard[LENGTH][LENGTH], int x, int y, int distance);int minimax(SPACE chessboard[LENGTH][LENGTH], int depth, int alpha, int beta, int maximizingPlayer, int color); ->判读某位置周围两格的范围内是否有落子  
int minimax(SPACE chessboard[LENGTH][LENGTH], int depth, int alpha, int beta, int maximizingPlayer, int color); ->alpha-beta剪枝处理DFS极小化极大算法  
int situation_assessment(SPACE chessboard[LENGTH][LENGTH], int color); ->统计当前总得分（AI方总分-人类方总分）  
SPACE AI_player_optimized(SPACE chessboard[LENGTH][LENGTH], int color); ->调用minimax，若未找到合适位置则优先在棋盘中心区间随机落子  
# 核心算法实现&代码展示
该项目最为核心的算法是alpha-beta剪枝和minimax&DFS算法  
搜索的深度通过宏定义#define SEARCH_DEPTH 4 设置为4，这在保证了程序运行速度的用时又确保了AI算力的足够强大  
以下为AI_player_DFS_alpha_beta函数原码  
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
<img width="1346" height="1178" alt="image" src="https://github.com/user-attachments/assets/308073f1-d3ef-4c49-bfaa-b2c69b0c7647" />
