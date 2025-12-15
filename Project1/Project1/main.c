#include"head_title_library.h"
#include"victory_condition.h"
#include"AI_player_DFS_alpha_beta.h"
int main() {
	//TEST_28:raylib实现后的重构——使begindrawing和enddrawing之间只进行绘图,将其他逻辑放在外面；修补了一些逻辑不恰当的Bug;调正了一下开头引用外部source部分的位置；增加AI落子提示和人类落子提示;解决了使用DrawText时的警告问题（改为使用DrawTextEx）
	srand((unsigned int)time(NULL));
	InitAudioDevice();
	Image boardImage = LoadImage("./source/OIP.jpg");
	Image ruleImage = LoadImage("./source/rule.jpg");
	Image blackImage = LoadImage("./source/black.jpg");
	Image whiteImage = LoadImage("./source/white.jpg");
	InitWindow(boardImage.width * 5, boardImage.height * 5, "AI_five_son_play");
	Texture BoardImage = LoadTextureFromImage(boardImage);
	Texture RuleImage = LoadTextureFromImage(ruleImage);
	Texture BlackImage = LoadTextureFromImage(blackImage);
	Texture WhiteImage = LoadTextureFromImage(whiteImage);
	Vector2 boardPosition = { 0.0f, 0.0f };
	Vector2 rulePosition = { 0.0f, 50.0f };
	Music bgm = LoadMusicStream("./source/music.mp3");
	Sound sound = LoadSound("./source/sound2.wav");
	Font font = GetFontDefault();
	Color tint = { 255, 100, 50, 255 };
	SetMusicVolume(bgm, 0.5f);
	SetSoundVolume(sound, 10.0f);
	PlayMusicStream(bgm);
	SetTargetFPS(120);
	int color = rand() % 2;
	SPACE chessboard[LENGTH][LENGTH] = { 0 };
	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			chessboard[i][j].x = i;
			chessboard[i][j].y = j;
			chessboard[i][j].belong = Blank;
		}
	}
	int AI_Column=0, AI_Line=0;
	bool AI_moved = false;
	if (color == White) {
		AI_Column = rand() % 3 + 5, AI_Line = rand() % 3 + 5;
		chessboard[AI_Line][AI_Column].belong = Black;
		AI_moved = true;
	}
	int AI_color = (color == White) ? Black : White;
	Color col= (color == White) ? WHITE : BLACK;
	int current_state = RULE_UI;
	int column=0, line=0;
	int x=0, y=0;
	bool left_button_pressed = false;
	while (!WindowShouldClose()) {
		if (IsKeyDown(KEY_ESCAPE)) {
			break;
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && current_state == GAMETIME) {
			x = GetMouseX();
			y = GetMouseY();
			column = (x - 14) / 92;
			line = (y - 74) / 92;
			left_button_pressed = true; 
		}
		if (current_state != GAMETIME && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
			switch (current_state) {
			case RULE_UI:
				current_state = (color == Black) ? BLACK_UI : WHITE_UI;
				break;
			case BLACK_UI:
				current_state = GAMETIME;
				break;
			case WHITE_UI:
				current_state = GAMETIME;
				break;
			}
		}
		if (current_state == GAMETIME && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && left_button_pressed) {
			if (line >= 0 && line < LENGTH && column >= 0 && column < LENGTH) {
				if (chessboard[line][column].belong == Blank) {
					chessboard[line][column].belong = color;
					PlaySound(sound);
					if (color == victory_condition(chessboard)) {
						current_state = WIN_UI;
					}
					else {
						SPACE AI = AI_player_optimized(chessboard, AI_color);
						AI_Line = AI.x, AI_Column = AI.y;
						if (AI_Line >= 0 && AI_Line < LENGTH && AI_Column >= 0 && AI_Column < LENGTH) {
							chessboard[AI_Line][AI_Column].belong = AI_color;
							AI_moved = true;
						}
						if (AI_color == victory_condition(chessboard)) {
							current_state = LOSE_UI;
						}
					}
				}
			}
		}
		BeginDrawing();
		switch (current_state) {
		case RULE_UI:
			DrawTextureEx(RuleImage, rulePosition, 0.0f, 1.0f, WHITE);
			break;
		case BLACK_UI:
			DrawTextureEx(BlackImage, rulePosition, 0.0f, 1.0f, WHITE);
			break;
		case WHITE_UI:
			DrawTextureEx(WhiteImage, rulePosition, 0.0f, 1.0f, WHITE);
			break;
		case GAMETIME:
			DrawTextureEx(BoardImage, boardPosition, 0.0f, 5.0f, WHITE);
			if (line >= 0 && line < LENGTH && column >= 0 && column < LENGTH) {
				DrawCircle(60 + 92 * column, 120 + 92 * line, 40, col);
				DrawCircle(60 + 92 * column, 120 + 92 * line, 8, RED);
			}
			for (int i = 0; i < LENGTH; i++) {
				for (int j = 0; j < LENGTH; j++) {
					if (chessboard[i][j].belong == Black) {
						DrawCircle(60 + 92 * j, 120 + 92 * i, 40, BLACK);
					}
					else if (chessboard[i][j].belong == White) {
						DrawCircle(60 + 92 * j, 120 + 92 * i, 40, WHITE);
					}
				}
			}
			if (AI_moved) {
				DrawCircle(60 + 92 * AI_Column, 120 + 92 * AI_Line, 8, RED);
			}
			break;
		case WIN_UI:
			DrawTextEx(font,"You win!Congratulations!",rulePosition, 160.0f, 4.0f, tint);
			break;
		case LOSE_UI:
			DrawTextEx(font, "You fail!What a pity!", rulePosition, 160.0f, 4.0f, tint);
			break;
		}
		EndDrawing();
		UpdateMusicStream(bgm);
		ClearBackground(RAYWHITE);
	}
	UnloadTexture(BoardImage);
	UnloadTexture(RuleImage);
	UnloadTexture(BlackImage);
	UnloadTexture(WhiteImage);
	StopMusicStream(bgm);
	UnloadMusicStream(bgm);
	UnloadSound(sound);
	CloseAudioDevice();
	CloseWindow();
	return 0;
}