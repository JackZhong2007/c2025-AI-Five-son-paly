#include"console_individual.h"
#include"head_title_library.h"
void console_individual() {
	HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorinfo;
	GetConsoleCursorInfo(hconsole, &cursorinfo);
	cursorinfo.bVisible = false;
	SetConsoleCursorInfo(hconsole, &cursorinfo);
}
