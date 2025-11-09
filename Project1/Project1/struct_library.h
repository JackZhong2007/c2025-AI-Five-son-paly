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
	bool live_1;
	bool live_2;
	bool chong_1[3];
	bool chong_2[3];
}NUM_LIVE;

typedef enum{BLACK,WHITE,BLANK}STATUS;

#define LENGTH 15

#define SEARCH_DEPTH 3
/*
#define DEAD_1 0
#define LIVE_1 1

#define DEAD_2 0
#define SLEEP_2 1
#define LIVE_2 10

#define DEAD_3 0
#define SLEEP_3 200
#define CHONG_3 5
#define LIVE_3 300

#define DEAD_4 0
#define CHONG_4 250
#define SLEEP_4 600
#define LIVE_4 1000

#define LIVE_5 10000
#define CHONG_5 500
*/

#define DEAD_1 0
#define LIVE_1 1

#define DEAD_2 0
#define SLEEP_2 5
#define LIVE_2 20

#define DEAD_3 0
#define SLEEP_3 50
#define CHONG_3 15
#define LIVE_3 500

#define DEAD_4 0
#define CHONG_4 100
#define SLEEP_4 600
#define LIVE_4 10000

#define LIVE_5 100000
#define CHONG_5 2000
