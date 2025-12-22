# 项目报告  
学院专业班级：计算机学院大类一班
项目名称：AI五子棋  
学生：钟俊凯  
学号：2025080901027  
指导教师：俸志刚  
实验日期：2025 年10  月15  日  
实验地点： 品学楼C区105  
# 一.项目内容
项目目标：在控制台实现人机对战五子棋游戏  
核心功能：一个具备较为强大的攻防能力的AI  
技术亮点：使用alpha-beta剪枝加速极小化极大算法，DFS ，raylib库
成果：AI具有较强算力，程序运行稳定 ，采用raylib实现GUI
# 二.实验环境  
1.硬件环境  
CPU型号：Ultra 9 275HX  
内存大小：32GB  
存储介质及容量：固态硬盘2TB  
其他硬件：显卡8GB  
2.软件环境  
操作系统：WIN11  
编译工具：Visual Studio2026  
调试工具：其自带调试工具  
编程语言：C  
# 三.系统设计
系统架构图：1.游戏前置准备  2.随机执黑执白  3.轮流落子  4.每次落子后检验是否胜利
# 四.模块详细设计：
1.数据结构设计：  
棋盘空间&棋盘空间状态枚举  
<img width="322" height="193" alt="image" src="https://github.com/user-attachments/assets/bae09207-6f9c-4c83-b6d9-c066610f4806" />  
使用一个二维数组SPACE chessboard[LENGTH][LENGTH]作为棋盘，其中LENGTH为棋盘长度15；x,y分别为line和column；belong有三种状态：  
<img width="369" height="161" alt="image" src="https://github.com/user-attachments/assets/5f744dc9-3dc4-4137-a375-c83ec7a7fb9d" />  
（全部大写会与raylib.h中的BLACK,WHITE,BLANK冲突，故改为首字母大写）
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
（5）AI_player_DFS_alpha_beta.c:包含四个函数： 
<img width="2127" height="328" alt="image" src="https://github.com/user-attachments/assets/f452a44f-d848-4eab-b2eb-6e27e5fc8e21" />  
int has_neighbor ->判读某位置周围两格的范围内是否有落子  
int minimax ->alpha-beta剪枝处理DFS极小化极大算法  
int situation_assessment ->统计当前总得分（AI方总分-人类方总分）  
SPACE AI_player_optimized ->调用minimax，若未找到合适位置则优先在棋盘中心区间随机落子  
# 五.核心算法实现&代码展示&算法原理简述
该项目最为核心的算法是alpha-beta剪枝和minimax&DFS算法  
搜索的深度通过宏定义#define SEARCH_DEPTH 4 设置为4，这在保证了程序运行速度的用时又确保了AI算力的足够强大  
以下为AI_player_DFS_alpha_beta函数原码  
<img width="1346" height="1178" alt="image" src="https://github.com/user-attachments/assets/308073f1-d3ef-4c49-bfaa-b2c69b0c7647" />  
minimax算法是在每一层轮流选取对于下棋方而言的最优解，经过DFS全局遍历搜索深度后，得出在搜索深度内的最优解（默认与对方极限博弈），而alpha_beta剪枝则是在minimax的基础上增加了一个剪枝的效果，使得在一些注定无效的情况时停止DFS，转向搜索其他，从而加速搜索。剪枝的逻辑是：假设当前层为AI层，在这一层AI落子会尽可能使得落子后全局评估分数较低（有利于AI），而在下一层（human层），聪明的人类玩家会让人类落子后全局评估分数尽可能高（有利于人类）。在human层遍历时，每经过一次搜索，最终会采取的情况的全局评估分数是单调不减的，而对于AI层，每经过一次搜索，最终会采取的情况的全局评估分数是单调不增的，因此，当human层的搜索分数开始大于AI层预设的搜索分数时，就可以采取剪枝，停止该结点的搜索，因为继续搜索下去，分数只会增加，而无论是否再增加，上一AI层都不会采取这一结点情况，因此可以避免无效的搜索，提高了搜索效率。 

同时，alpha-beta剪枝和minimax&DFS的实现离不开估值函数，由于估值函数较长，在此展示部分代码及估值函数思路:  
<img width="454" height="816" alt="image" src="https://github.com/user-attachments/assets/4f89c865-76cc-4d48-b4fc-efdabd648188" />  
对于一个点的分数，需要评估其四个方向（横竖撇捺）的棋形，不同棋形对应着不同的分值：  
<img width="351" height="810" alt="image" src="https://github.com/user-attachments/assets/df4120dd-609a-4060-8ffd-e88f1979d99a" />  
该系列分值是在反复测试后得出的较为合理的值，虽然肯定不是最合适的值，但已经可以使得AI落子逻辑自洽  
上上图展示了“横”情况棋形的判断，前文谈及棋形有活死冲之分，活和死是比较好判断的，而冲的具体判断还需要后续再次处理；在图中可以看出，判断活和死就是简单的向一个方向延展（只需延展四个），直到下一个子为空白或者对方的子时记录该方向延展个数，后续再与反方向延展个数相加即可得到活和死的棋形。冲类型的判断是基于当在一个方向延展时遇到了空白，则尝试跳过空白处继续延展（只需延展三个），若与估值点棋颜色相同则计数，否则则停止计数，后续再与反方向延展个数相加即可得到具体的冲的棋形。  
# 六.实验结果及分析  
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
<img width="1414" height="1532" alt="image" src="https://github.com/user-attachments/assets/003f83dc-afa8-4c44-8a46-eca70dec5908" />  
鼠标移到想要落子的位置后，按鼠标左键进行预落子，按鼠标右键进行落子，落子成功后会有音效提示，AI思考落子期间bgm会停止，红心标记为双方上一手落点位置的提示。  
败北结算画面：  
<img width="1409" height="1529" alt="image" src="https://github.com/user-attachments/assets/c4a93ba9-7dc3-4ec3-8a8f-582f5f896c9b" />
胜利结算画面：  
<img width="1414" height="1532" alt="image" src="https://github.com/user-attachments/assets/862b1904-540d-43b1-aca8-fadd236ff0c1" />  
# 结果分析  
1.AI在较短时间进行了高质量的落子，说明了四层的搜索深度的合理性，面对业余玩家可以在执黑和执白时都拥有较高的算力。  
2.使用raylib库，使得原先手动输入落子位置变为了GUI，提高了可玩度，也使得界面更加美观。  
3.未使用Cmakelist,使得该项目迁移性较差，同时raylib库的使用的一个弊端是该项目无法在未配置raylib环境的ide上运行。  
4.随着双方落子数量的增加，当落子总数超过16手时AI落子速度会出现较明显的下降。  优化方向：改进evaluate_score函数。  
# 七.实验总结与心得体会  
本次实验项目完成了AI五子棋的开发，系统采用多文件模块化开发思想，功能稳定。关键技术点包括估值函数的实现，深度优先搜索和alpha-beta剪枝的实现，以及GUI的运用。  
C语言知识点梳理：  
掌握raylib库较为实用的功能的用法，调试能力显著增强，能够快速定位并解决逻辑错误。深化了DFS的运用，学会了对alpha-beta剪枝的运用。  
心得体会：  本次个人独立进行首个项目的开发使我受益匪浅，从一开始对于多文件的不适应和不理解，到逐渐体悟到模块化编程的好处的过程让我对项目作业有了更加清晰的认知。在项目开发过程中，我对C语言的结构体，递归等知识点的理解更加透彻，尤其是关于DFS搜索深度的设定，让我明白编程不仅要追求功能，还要追求运行效率，除此之外，raylib库的运用也让我明白了项目的开发要从使用者的角度进行思考和优化。同时，这次项目开发的经历让我在面对代码报错或运行结果不尽人意时从原来的惊慌失措变得更加冷静，培养出了快速独立自主debug的能力。  
困难与反思：  项目开发过程中遇到的最大的问题是估值函数的编写，该函数的编写不断地突破我预先的想象，使得我不得不不断的重新划分棋形，重新对该部分函数进行改写。这反应出了我自上而下的去编写代码的能力的不足，需要更多的项目开发经验不断改善。在面对从未接触过的alpha-beta函数，我经历了自主学习和迁移运用的过程，从最初递归的混乱不堪到最后的逻辑自洽，我的算法编写能力在其中得到了锻炼。在这次开发经历中，我较好地落实了老师教导的各种数据结构，函数，变量的命名要规范的教诲，使得我在开发过程中逻辑更加地严密，这让我明白了养成养好编码习惯的重要性。
