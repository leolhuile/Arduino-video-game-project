#ifndef __SCREEN__
  #include <UTFT.h>

  // Main object :
  extern UTFT screen;

  // Useful values :
  extern const int SCREEN_HEIGHT;
  extern const int SCREEN_WIDTH;
  extern const int X_MID;
  extern const int Y_MID;
  #define MIDDLE X_MID, Y_MID

  // Fonts :
  extern uint8_t SmallFont[];
  extern uint8_t BigFont[];

  // Colors :
  #define RGB_WHITE 255, 255, 255
  #define RGB_BLACK 0, 0, 0
  #define RGB_GREEN 0, 255, 0  // <-- Chosen Box Color

  // State Machines :
  enum class MainState { Menu, Snake, Pong };
  extern MainState main_state;

  enum class GameState { Loading, OnBreak, Playing };
  extern GameState game_state;

  // To declare it ONCE and for all :
  #define self (*this)
  extern char b_message;

  #define __SCREEN__
#endif