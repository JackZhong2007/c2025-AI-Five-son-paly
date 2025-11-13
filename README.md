# 项目报告
项目名称：AI五子棋  
学生：钟俊凯  
学号：2025080901027
# 项目内容
项目目标：在控制台实现人机对战五子棋游戏  
核心功能：一个具备较为强大的攻防能力的AI  
技术亮点：使用alpha-beta剪枝加速极小化极大算法算法，DFS  
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
main.c:游戏开始前置准备，主循环——一方落子->判定是否获胜->另一方落子->判断是否或者  
head_title_library.h:包含一系列头文件，宏定义，类定义，方便调用  
before_begin：包含三个函数：  void console_individual(); ->隐藏光标  
                             int before_begin(); ->UI界面，随机设置执黑和执白方  
                             void set_individual_chessboard(SPACE chessboard[LENGTH][LENGTH]); ->棋盘初始化
