#include "screen.h"

UTFT screen(SSD1289, 38, 39, 40, 41);

const int SCREEN_WIDTH  = 320; // <-- screen.getDisplayXSize()
const int SCREEN_HEIGHT = 240; // <-- screen.getDisplayYSize()

const int X_MID = SCREEN_WIDTH / 2;
const int Y_MID = SCREEN_HEIGHT / 2;

MainState main_state = MainState::Menu;
GameState game_state = GameState::Playing;

char b_message;