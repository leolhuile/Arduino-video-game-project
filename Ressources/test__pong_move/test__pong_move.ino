#include "hc06.h"
#include "menu.h"
#include "games.h"


/*  Plan :
main.ino (<< hc06, menu, games)

------------------------
hc06
|> hc06.h

screen
|> screen.h
|> screen.cpp
------------------------

menu (<< screen)
|> menu.h
|> menu.cpp

games (<< screen)
|> games.h
|> game_snake.cpp
|> game_pong.cpp
*/


// ----------------------------------- SETUP -----------------------------------

void setup() {
  //hc06_setup();
  //menu_setup();

  Serial.begin(38400);

  //Pour tester le pong :
  game_Pong_setup();
  main_state = MainState::Pong;
}


// ----------------------------------- LOOP ------------------------------------

void loop() {
  game_Pong_loop();
}