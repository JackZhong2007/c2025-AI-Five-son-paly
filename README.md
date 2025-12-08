# 项目报告
项目名称：AI五子棋  
学生：钟俊凯  
学号：2025080901027
# 项目内容
项目目标：在控制台实现人机对战五子棋游戏  
核心功能：一个具备较为强大的攻防能力的AI  
技术亮点：使用alpha-beta剪枝加速极小化极大算法，DFS ，raylib库
成果：AI具有较强算力，程序运行稳定 ，采用raylib实现GUI
# 项目概述
操作系统：WIN11  
编程语言：C  
IDE:VS2026  
# 系统设计
系统架构图：1.游戏前置准备  2.随机执黑执白  3.轮流落子  4.每次落子后检验是否胜利
# 模块详细设计：
1.数据结构设计：  
棋盘空间&棋盘空间状态枚举  
<img width="322" height="193" alt="image" src="https://github.com/user-attachments/assets/bae09207-6f9c-4c83-b6d9-c066610f4806" />
使用一个二维数组SPACE chessboard[LENGTH][LENGTH]作为棋盘，其中LENGTH为棋盘长度15；x,y分别为line和column；belong有三种状态：typedef enum { BLACK, WHITE, BLANK }STATUS;  
棋形结构  
<img width="774" height="359" alt="image" src="https://github.com/user-attachments/assets/8f3b06c6-ee86-412e-8110-5edbe3237839" />
棋形由连续子数码Num和是否“活”两部分组成，该结构以此命名。  
我将棋形分为了“活”，“死”，“眠”，“冲”这四个部分，其中“冲”比较特殊，又细分为了“活冲”，“死冲”，“眠冲”，而Num就是简单的一到五这五个情况。  
不同棋形有着不同的分值，而NUM_LIVE的成员作用为：num代表主体连续数，bool live[2]的两个量分别代指两端是否为“活”（是否被对方堵住或者被棋盘大小限制），bool chong_1[3]和bool   chong_2[3]分别判断在主体两端由于空白空间而中止计数时，两端是否由于“冲”棋形而产生只有中间断了一个的“连续”棋形，其中[3]是为计数，bool chong_live[2]是为判断越过空白后的子是否为“活”  
2.功能模块设计  
（1）main.c:游戏开始前置准备，主循环——一方落子->判定是否获胜->另一方落子->判断是否或者  
（2）head_title_library.h:包含一系列头文件，宏定义，类定义，方便调用  
（3）viction_condition.c:包含一个函数： int victory_condition(SPACE space[LENGTH][LENGTH]); ->判断当前棋局是否有五连子  
（4）evaluate_score.c:包含五个函数：  
<img width="1578" height="238" alt="image" src="https://github.com/user-attachments/assets/6c1914bc-3ccf-47f7-8246-4b5043d75b07" />
（5）AI_player_DFS_alpha_beta.c:包含四个函数： int has_neighbor(SPACE chessboard[LENGTH][LENGTH], int x, int y, int distance);int minimax(SPACE chessboard[LENGTH][LENGTH], int depth, int alpha, int beta, int maximizingPlayer, int color); ->判读某位置周围两格的范围内是否有落子  
int minimax(SPACE chessboard[LENGTH][LENGTH], int depth, int alpha, int beta, int maximizingPlayer, int color); ->alpha-beta剪枝处理DFS极小化极大算法  
int situation_assessment(SPACE chessboard[LENGTH][LENGTH], int color); ->统计当前总得分（AI方总分-人类方总分）  
SPACE AI_player_optimized(SPACE chessboard[LENGTH][LENGTH], int color); ->调用minimax，若未找到合适位置则优先在棋盘中心区间随机落子  
# 核心算法实现&代码展示&算法原理简述
该项目最为核心的算法是alpha-beta剪枝和minimax&DFS算法  
搜索的深度通过宏定义#define SEARCH_DEPTH 4 设置为4，这在保证了程序运行速度的用时又确保了AI算力的足够强大  
以下为AI_player_DFS_alpha_beta函数原码  
<img width="1346" height="1178" alt="image" src="https://github.com/user-attachments/assets/308073f1-d3ef-4c49-bfaa-b2c69b0c7647" />  
minimax算法是在每一层轮流选取对于下棋方而言的最优解，经过DFS全局遍历搜索深度后，得出在搜索深度内的最优解（默认与对方极限博弈），而alpha_beta剪枝则是在minimax的基础上增加了一个剪枝的效果，使得在一些注定无效的情况时停止DFS，转向搜索其他，从而加速搜索。剪枝的逻辑是：假设当前层为AI层，在这一层AI落子会尽可能使得落子后全局评估分数较低（有利于AI），而在下一层（human层），聪明的人类玩家会让人类落子后全局评估分数尽可能高（有利于人类）。在human层遍历时，每经过一次搜索，最终会采取的情况的全局评估分数是单调不减的，而对于AI层，每经过一次搜索，最终会采取的情况的全局评估分数是单调不增的，因此，当human层的搜索分数开始大于AI层预设的搜索分数时，就可以采取剪枝，停止该结点的搜索，因为继续搜索下去，分数只会增加，而无论是否再增加，上一AI层都不会采取这一结点情况，因此可以避免无效的搜索，提高了搜索效率。  
# 测试&运行结果截图  
游戏过程中按esc可退出游戏。
玩法介绍界面：
<img width="1416" height="1527" alt="image" src="https://github.com/user-attachments/assets/3c2fecb8-511c-4b1b-9a99-89270d60590f" />  
该界面产生的同时开始播放bgm  
按鼠标右键进入下一环节。  
执黑时：  
<img width="1414" height="1531" alt="image" src="https://github.com/user-attachments/assets/30193d48-5ead-4311-9b49-c0a6af7cab44" />  
执白时：  
<img width="1413" height="1527" alt="image" src="https://github.com/user-attachments/assets/9b532ac2-7d76-4416-af06-19b9cf7d439f" />   
按鼠标右键进入下一环节。  
<img width="1409" height="1527" alt="image" src="https://github.com/user-attachments/assets/d1ee570b-add6-4876-8689-7d18fc983b67" />  
鼠标移到想要落子的位置后，按鼠标左键进行预落子，按鼠标右键进行落子，落子成功后会有音效提示，AI思考落子期间bgm会停止。  
败北结算画面：  
<img width="1409" height="1529" alt="image" src="https://github.com/user-attachments/assets/c4a93ba9-7dc3-4ec3-8a8f-582f5f896c9b" />
胜利结算画面：  
<img width="1414" height="1532" alt="image" src="https://github.com/user-attachments/assets/862b1904-540d-43b1-aca8-fadd236ff0c1" />  

