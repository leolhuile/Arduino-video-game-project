#include "menu.h"

// ----------------------------------- TOOLS -----------------------------------

namespace {
  inline static void drawSnakeBox(uint8_t r, uint8_t g, uint8_t b) {
    screen.setColor(r,g,b);

    const int Y_RECT = 110;

    //Draw Rect :
    screen.drawRoundRect(       //param : (x1,y1 , x2,y2)
      //1st corner
      90 , Y_RECT,
      //2nd corner 
      90 + 135, Y_RECT + 30
    );

    //Print games' names on screen :
    screen.setBackColor(RGB_BLACK);
    screen.setFont(SmallFont);
    screen.print(               //param : (string , x,y , optional<degrees>)
      "Snake",
      CENTER,
      Y_RECT + 15
    );
  }
  inline static void drawPongBox(uint8_t r, uint8_t g, uint8_t b) {
    screen.setColor(r,g,b);

    const int Y_RECT = 160;

    //Draw Rect :
    screen.drawRoundRect(       //param : (x1,y1 , x2,y2)
      //1st corner
      90 , Y_RECT,
      //2nd corner 
      90+135 , Y_RECT + 30
    );

    //Print games' names on screen :
    screen.setBackColor(RGB_BLACK);
    screen.setFont(SmallFont);
    screen.print(               //param : (string , x,y , optional<degrees>)
      "Pong",
      CENTER,
      Y_RECT + 15
    );
  }

  enum class SelectorState { SelectNone, SelectSnake, SelectPong };
  static SelectorState selector;

  inline static void selectSnake() {
    drawSnakeBox(RGB_GREEN);
    drawPongBox(RGB_WHITE);
    selector = SelectorState::SelectSnake;
  }
  inline static void selectPong() {
    drawSnakeBox(RGB_WHITE);
    drawPongBox(RGB_GREEN);
    selector = SelectorState::SelectPong;
  }
  inline static void selectNone() {
    drawSnakeBox(RGB_WHITE);
    drawPongBox(RGB_WHITE);
    selector = SelectorState::SelectNone;
  }
}


// ----------------------------------- SETUP -----------------------------------

void menu_setup() {
  screen.InitLCD(LANDSCAPE);

  //Switch ON screen :
  screen.fillScr(RGB_BLACK);

  selectNone();

  //Print Title :
  screen.setBackColor(RGB_BLACK);
  screen.setColor(220,180,150);  //<-- Title Color
  screen.setFont(BigFont);
  screen.print("Penta BOX", CENTER, 0);

  game_state = GameState::Playing;
}


// ------------------------------------ LOOP -----------------------------------

void menu_loop() {
  if (Serial1.available()) {
    b_message = Serial1.read(); //<-- Reading data from HC-06

    //DEBUG :: Received message :
    Serial.print("Received from HC-05: ");
    Serial.println(b_message);

    if (selector ==  SelectorState::SelectNone) {
      selectSnake();
    } else {
      //Computing message :
      switch (b_message) {
        case 'H' :
          selectSnake();
          break;

        case 'B' :
          selectPong();
          break;

        case 'a' :
          switch (selector) {
            case SelectorState::SelectSnake : main_state = MainState::Snake; break;
            case SelectorState::SelectPong  : main_state = MainState::Pong;  break;
          } break;

        case 'b' :
          selectNone();
          break;

        //DEBUG :: Unknown message :
        default :
          Serial.print("Unknown message received: ");
          Serial.println(b_message);
      }
    }
  }
}