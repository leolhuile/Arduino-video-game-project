#include "games.h"

// ----------------------------------- TOOLS -----------------------------------

// TODO : Removing those macros :
#define PAD_COLOUR RGB_GREEN
#define BALL_COLOUR RGB_GREEN

namespace {
  inline static void drawField(uint8_t r, uint8_t g, uint8_t b) {
    screen.setColor(r, g, b);

    // Borders :
    screen.drawHLine(0, 0, SCREEN_WIDTH);
    screen.drawHLine(0, SCREEN_HEIGHT, SCREEN_WIDTH);

    // Middle Line : // ?? Unsure as it looks like a border ??
    screen.drawLine(X_MID, 0, X_MID, SCREEN_HEIGHT);
  }



  /*************** PAD ***************/

  class Pad {
    //# ¤¤¤¤¤¤¤¤¤¤ CLASS ATTRIBUTS ¤¤¤¤¤¤¤¤¤ #//
    public:
      //Measures :
      static const int PAD_LENGTH;
      static const int PAD_WIDTH;
      //Limits :
      static const int TOP_LIMIT;
      static const int BOTTOM_LIMIT;

    //# ¤¤¤¤¤¤¤¤¤¤¤¤¤ ATTRIBUTS ¤¤¤¤¤¤¤¤¤¤¤¤ #//
    private:
      int x; // ! Should be a constant but I didn't found a way to declare 'x' as one
      int y; // y is the top of the pad not its middle


    //# ¤¤¤¤¤¤¤¤¤ GETTERS & SETTERS ¤¤¤¤¤¤¤¤ #//
    public:
      int getYTop() const noexcept {
        return self.y;
      }

      int getYCenter() const noexcept {
        return self.y + PAD_LENGTH / 2;
      }

    //# ¤¤¤¤¤¤¤¤¤¤¤¤¤¤ METHODS ¤¤¤¤¤¤¤¤¤¤¤¤¤ #//
    private:
      inline void erasePad() const noexcept {
        screen.setColor(RGB_BLACK);
        screen.fillRect(
          self.x, 0,
          self.x + PAD_WIDTH, SCREEN_HEIGHT
        );
      }

      inline void drawPad() const noexcept {
        /* Draw pad at current coordinates : (self.x , self.y) */

        // Draw pad :
        screen.setColor(PAD_COLOUR);  // TODO : Choisir une couleur pour les pads
        screen.fillRect(
          self.x, self.y,
          self.x + PAD_WIDTH, self.y + PAD_LENGTH
        );
      }

    public:
      // For SETUP :
      inline void setIt(int x) noexcept {
        self.x = x;
        self.y = Y_MID - PAD_LENGTH / 2;
        self.drawPad();
      }

      // For PLAYING :
      inline void moveUp(int speed) noexcept {
        if (self.y == TOP_LIMIT) return;

        self.erasePad();
        self.y -= (speed <= self.y) ? speed : self.y;
        self.drawPad();
      }
      inline void moveDown(int speed) noexcept {
        if (self.y == BOTTOM_LIMIT) return;

        self.erasePad();
        const int dy = BOTTOM_LIMIT - self.y;
        self.y += (speed <= dy) ? speed : dy;
        self.drawPad();
      }
  };

  const int Pad::PAD_LENGTH = 35;
  const int Pad::PAD_WIDTH = 5;
  const int Pad::TOP_LIMIT = 0;
  const int Pad::BOTTOM_LIMIT = 205; // <-- SCREEN_HEIGHT - PAD_LENGTH


  static Pad player, computer;
  inline static void initPads() {
    player.setIt(0);
    computer.setIt(SCREEN_WIDTH - Pad::PAD_WIDTH);
  }



  /*************** BALL **************/

  class Ball {
    enum class Direc { Right = 1, Left = -1 };

    //# ¤¤¤¤¤¤¤¤¤¤ CLASS ATTRIBUTS ¤¤¤¤¤¤¤¤¤ #//
    private:
      static const int RADIUS;


    //# ¤¤¤¤¤¤¤¤¤¤¤¤¤ ATTRIBUTS ¤¤¤¤¤¤¤¤¤¤¤¤ #//
    private:
      int x, y;
      int speeds[2];  // ?? Still unsure ??
      Direc direc;


    //# ¤¤¤¤¤¤¤¤¤ GETTERS & SETTERS ¤¤¤¤¤¤¤¤ #//
    public:
      int getY() const noexcept {
        return self.y;
      }

    //# ¤¤¤¤¤¤¤¤¤¤¤¤¤¤ METHODS ¤¤¤¤¤¤¤¤¤¤¤¤¤ #//
    private:
      inline void drawBall() const noexcept {
        /* Draw pad at current coordinates : (self.x , self.y) */

        screen.setColor(BALL_COLOUR);
        screen.fillCircle(self.x, self.y, RADIUS);
      }
      inline void eraseBall() const noexcept {
        /* Draw pad at current coordinates : (self.x , self.y) */

        screen.setColor(BALL_COLOUR);
        screen.fillCircle(self.x, self.y, RADIUS);
      }

      inline int computeYSpeed(Pad pad) noexcept {
        /*
            Length of pad : 35px

            Part of pad : 5 px

            7 parts
            */

        int pad_Ycenter = pad.getYCenter();

        int relative_y = self.y - pad_Ycenter;
        if (-2 <= relative_y && relative_y <= 2) {
          return 0;
        }

        int factor;
        if (relative_y > 2) {
          factor = -1;
        } else {
          factor = 1;
          relative_y *= -1;
        }

        int y_speed = 0;
        for (int i = 1; i <= (Pad::PAD_LENGTH / 5) / 2; ++i) {
          if (relative_y <= 2 + i * 5) {
            return factor * y_speed;
          }
          y_speed += 5;  // ?? valeur incertaine ??
        }
      }

    public:
      // For SETUP :
      inline void spawn() noexcept {
        self.eraseBall();

        self.speeds[0] = 1;  // ?? x_speed est à revoir ??
        self.speeds[1] = 0;

        self.x = X_MID;
        self.y = Y_MID;

        self.drawBall();

        //TODO : Random choice
        self.direc = Direc::Left;
      }

      // For PLAYING :
      inline void getHit() noexcept {
        self.speeds[0] += 1;  // ?? valeur à revoir ??
      }

      inline void move() noexcept {
        // Test if tap border :
        if (self.y == RADIUS || self.y == SCREEN_HEIGHT - RADIUS) {
          self.speeds[1] *= -1;
        }

        // Test if tap pad :
        if (
          self.x == Pad::PAD_WIDTH + RADIUS
          || self.x == SCREEN_WIDTH - (Pad::PAD_WIDTH + RADIUS)) {
          Pad pad;
          switch (self.direc) {
            case Direc::Left: pad = player; break;
            case Direc::Right: pad = computer; break;
          }
          self.speeds[1] = self.computeYSpeed(pad);
        }

        //* Draw
        self.eraseBall();
        self.x += (int)self.direc * self.speeds[0];
        self.y += (int)self.direc * self.speeds[1];
        self.drawBall();
      }
  };

  const int Ball::RADIUS = 5;


  Ball ball;


}


// ----------------------------------- SETUP -----------------------------------

void game_Pong_setup() {
  screen.InitLCD(LANDSCAPE); // A retirer si c pas dans le 1er setup (normalement le 1er est 'menu_setup')

  screen.fillScr(RGB_BLACK);

  drawField(RGB_WHITE);
  initPads();
  //ball.spawn();

  Serial.println("Pong Setup finished");
}


// ------------------------------------ LOOP -----------------------------------

// DEBUG :: Test move functionnality
static bool player_up{ true }, computer_up{ false };
void game_Pong_loop() {
  Serial.println("Pong Loop");

  (player_up) ? player.moveUp(5) : player.moveDown(5);
  switch (player.getYTop()) {
    case Pad::TOP_LIMIT: player_up = false; break;
    case Pad::BOTTOM_LIMIT: player_up = true; break;
  }

  (computer_up) ? computer.moveUp(5) : computer.moveDown(5);
  switch (computer.getYTop()) {
    case Pad::TOP_LIMIT: computer_up = false; break;
    case Pad::BOTTOM_LIMIT: computer_up = true; break;
  }

  delay(100);
}