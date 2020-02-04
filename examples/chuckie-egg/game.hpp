#pragma once
#include "32blit.hpp"
#include <cstdint>

// Game frame rate was 3/100ths of a second
#define UPDATE_INTERVAL_MS 60

#define ROWS 25
#define COLUMNS 20
#define TILE_STRIDE 8

#define TILE_WALL 0x01u
#define TILE_LADDER 0x02u
#define TILE_EGG 0x04u
#define TILE_GRAIN 0x08u

#define MAX_DUCKS 5
#define MAX_PLAYERS 4
#define NUM_EGGS 12

/*** Game interface.  */
#define BUTTON_RIGHT 0x01u
#define BUTTON_LEFT 0x02u
#define BUTTON_DOWN 0x04u
#define BUTTON_UP 0x08u
#define BUTTON_JUMP 0x10u

/* extern uint8_t buttons;
extern uint8_t button_ack;
extern int cheat;
extern int skip_frame;
*/

// Offset into tile to get on ladder
#define LADDER_PARTIAL_X 0

/* Direction bitflags  */
#define DIR_L 1
#define DIR_R 2
#define DIR_UP 4
#define DIR_DOWN 8
#define DIR_HORIZ (DIR_R | DIR_L)
#define DIR_VERT (DIR_UP | DIR_DOWN)

enum HenryState { WALK, CLIMB, JUMP, FALL, LIFT };

struct Henry {
  blit::point pos;
  blit::point tile;
  blit::point partial;
  blit::point speed;
  HenryState state;
  int dir;
  int falling;
  int sliding;
};

struct Player {
  uint8_t score[8];
  uint8_t bonus[4];
  uint8_t egg[16];
  uint8_t grain[16];
  int lives;
};

// NOTE: EAT1 should never be rendered but is used in the state
// machine for duck eating animation
enum DuckState { BORED, STEP, EAT1, EAT2, EAT3, EAT4 };

struct Duck {
  blit::point pos;
  blit::point tile;
  DuckState state;
  int dir;
};

struct BigDuck {
  blit::point pos;
  vec2 dPos;
  int dir;
  int frame;
};

class Game {
public:
  void SetScreenSize(blit::size &);
  void Render(blit::surface &);
  void Tickle(uint32_t);

private:
  unsigned int getTile(int x, int y);
  bool isTileWall(int x, int y);
  inline void setTile(int x, int y, uint8_t tile) {
    tiles[y * COLUMNS + x] = tile;
  }
  inline void addToTile(int x, int y, uint8_t contents) {
    tiles[y * COLUMNS + x] |= contents;
  }

  void loadLevel(unsigned int);
  void renderBackground(blit::surface &);
  void renderDucks(blit::surface &);
  void renderHenry(blit::surface &);
  void renderLifts(blit::surface &);
  void renderBigBird(blit::surface &);
  void pollKeys();
  void moveHenry();
  bool startJump(Henry &);
  void jumpHenry(Henry &);
  void fallHenry(Henry &);
  void climbHenry(Henry &);
  void walkHenry(Henry &);
  void liftHenry(Henry &);
  void animateHenry(Henry &);

  void addScore(int, int);
  bool cannotMove(Henry &);
  bool canGrabLadder(Henry &, int16_t);

  blit::point tilePosition(blit::point &);
  blit::point tilePosition(int, int);

  // Screen
  blit::size screenSize;

  // Uodate timing
  uint32_t lastTime;

  // input
  uint16_t buttonsDown;
  uint16_t buttonAck; // ???
  // int numPlayers

  // Level info
  bool hasLift;
  int numGrain;
  int numDucks;
  int liftX;
  int liftY[2];
  int currentLift;
  bool hasBigDuck;

  // state
  uint16_t currentLevel;
  uint8_t currentPlayer;
  uint8_t eggsLeft;
  uint8_t tiles[ROWS * COLUMNS];
  Player playerData[MAX_PLAYERS];
  BigDuck bigDuck;
  Duck ducks[MAX_DUCKS];
  Henry henry;
};
