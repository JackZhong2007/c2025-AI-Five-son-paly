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
}NUM_LIVE;

typedef enum{BLACK,WHITE,BLANK}STATUS;

#define LENGTH 15

#define DEAD_1 0
#define LIVE_1 1
#define DEAD_2 0
#define SLEEP_2 1
#define LIVE_2 10
#define DEAD_3 0
#define SLEEP_3 10
#define CHONG_3 20
#define LIVE_3 100
#define DEAD_4 0
#define CHONG_4 300
#define SLEEP_4 500
#define LIVE_4 1000
#define LIVE_5 10000