#include"head_title_library.h"
#include"victory_condition.h"
#include"AI_player_DFS_alpha_beta.h"
int main() {
	//TEST_26:改用raylib库实现图形界面
	srand((unsigned int)time(NULL));
	InitAudioDevice();
	Image boardImage = LoadImage("./source/OIP.jpg");
	Image ruleImage = LoadImage("./source/rule.jpg");
	Image blackImage = LoadImage("./source/black.jpg");
	Image whiteImage = LoadImage("./source/white.jpg");
	InitWindow(boardImage.width*5, boardImage.height*5, "AI_five_son_play");
	SetTargetFPS(120);
	Texture BoardImage = LoadTextureFromImage(boardImage);
	Texture RuleImage = LoadTextureFromImage(ruleImage);
	Texture BlackImage = LoadTextureFromImage(blackImage);
	Texture WhiteImage = LoadTextureFromImage(whiteImage);
	Vector2 boardPosition = { 0.0f, 0.0f };
	Music bgm = LoadMusicStream("./source/music.mp3");
	Sound sound = LoadSound("./source/sound2.wav");
	SetMusicVolume(bgm, 0.5f);
	SetSoundVolume(sound, 10.0f);
	PlayMusicStream(bgm);
	int color = rand() % 2;
	SPACE chessboard[LENGTH][LENGTH] = { 0 };
	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			chessboard[i][j].x = i;
			chessboard[i][j].y = j;
			chessboard[i][j].belong = Blank;
		}
	}
	if (color == White) {
		int x_rand = rand() % 3 + 5, y_rand = rand() % 3 + 5;
		chessboard[x_rand][y_rand].belong = Black;
	}
	int AI_color = (color == White) ? Black : White;
	Color col= (color == White) ? WHITE : BLACK;
	Color AI_col = (AI_color == White) ? WHITE : BLACK;
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
			case WHITE_UI:
				current_state = GAMETIME;
				break;
			}
		}
		BeginDrawing();
		switch (current_state) {
		case RULE_UI:
			DrawTextureEx(RuleImage, boardPosition, 0.0f, 1.0f, WHITE);
			break;
		case BLACK_UI:
			DrawTextureEx(BlackImage, boardPosition, 0.0f, 1.0f, WHITE);
			break;
		case WHITE_UI:
			DrawTextureEx(WhiteImage, boardPosition, 0.0f, 1.0f, WHITE);
			break;
		case GAMETIME:
			DrawTextureEx(BoardImage, boardPosition, 0.0f, 5.0f, WHITE);
			if (line >= 0 && line < LENGTH && column >= 0 && column < LENGTH) {
				DrawCircle(60 + 92 * column, 120 + 92 * line, 40, col);
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
			if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && left_button_pressed) {
				if (line >= 0 && line < LENGTH && column >= 0 && column < LENGTH) {
					if (chessboard[line][column].belong == Blank) {
						chessboard[line][column].belong = color;
						PlaySound(sound);
						if (color == victory_condition(chessboard)) {
							current_state = WIN_UI;
						}
						else {
							SPACE AI = AI_player_optimized(chessboard, AI_color);
							if (AI.x >= 0 && AI.x < LENGTH && AI.y >= 0 && AI.y < LENGTH) {
								chessboard[AI.x][AI.y].belong = AI_color;
							}
							if (AI_color == victory_condition(chessboard)) {
								current_state = LOSE_UI;
							}
						}
					}
				}
			}
			break;
		case WIN_UI:
			DrawText("You win!Congratulations!", 10, 10, 130, BLACK);
			break;
		case LOSE_UI:
			DrawText("You lose!What a pity!", 10, 10, 130, BLACK);
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