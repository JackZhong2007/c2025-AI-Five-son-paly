#include"victory_condition.h"
#include"head_title_library.h"
#include"struct_library.h"
int victory_condition(SPACE space[LENGTH][LENGTH]) {
	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			if (space[i][j].belong == BLANK) {
				continue;
			}
			int color = space[i][j].belong;
			if (j <= LENGTH - 5){
				bool win = true;
				for (int k = 1; k <= 4; k++) {//right
					if (space[i][j + k].belong != color) {
						win = false;
						break;
					}
				}
				if (win) {
					return color;
				}
			}
			if (i <= LENGTH - 5) {
				bool win = true;
				for (int k = 1; k <= 4; k++) {//down
					if (space[i + k][j].belong != color) {
						win = false;
						break;
					}
				}
				if (win) {
					return color;
				}
			}
			if (j <= LENGTH - 5&&i<=LENGTH-5) {
				bool win = true;
				for (int k = 1; k <= 4; k++) {//right and down
					if (space[i+k][j + k].belong != color) {
						win = false;
						break;
					}
				}
				if (win) {
					return color;
				}
			}
			if (j <= LENGTH - 5&&i>=4) {
				bool win = true;
				for (int k = 1; k <= 4; k++) {//right and up
					if (space[i-k][j + k].belong != color) {
						win = false;
						break;
					}
				}
				if (win) {
					return color;
				}
			}
			
		}
	}
	return BLANK;
}