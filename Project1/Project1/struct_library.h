#pragma once
#include"head_title_library.h"
typedef struct{
	int x;
	int y;
	int belong;
	int score;
}SPACE;

typedef struct {
	int num;
	bool live[2];
	bool chong_1[3];
	bool chong_2[3];
	bool chong_live[2];
}NUM_LIVE;

typedef enum{BLACK,WHITE,BLANK}STATUS;

#define LENGTH 15

#define SEARCH_DEPTH 4

#define DEAD_1 0
#define LIVE_1 1

#define DEAD_2 0
#define SLEEP_2 1
#define LIVE_2 10

#define DEAD_3 0
#define SLEEP_3 200
#define LIVE_CHONG_3 5
#define DEAD_CHONG_3 0
#define SLEEP_CHONG_3 2
#define LIVE_3 300

#define DEAD_4 0
#define LIVE_CHONG_4 250
#define DEAD_CHONG_4 0
#define SLEEP_CHONG_4 50
#define SLEEP_4 5000
#define LIVE_4 10000

#define LIVE_5 1000000
#define CHONG_5 2000

