#pragma once
#include "32blit.hpp"
#include <cstdint>

// Game frame rate was 3/100ths of a second
#define UPDATE_INTERVAL_MS 30 

#define ROWS 25
#define COLUMNS 20
#define TILE_STRIDE 8

#define TILE_WALL 1
#define TILE_LADDER 2
#define TILE_EGG 4
#define TILE_GRAIN 8

#define MAX_DUCKS 5
#define MAX_PLAYERS 4
#define NUM_EGGS 12

/*** Game interface.  */
#define BUTTON_RIGHT  1
#define BUTTON_LEFT   2
#define BUTTON_DOWN   4
#define BUTTON_UP     8
#define BUTTON_JUMP   0x10
/* extern uint8_t buttons;
extern uint8_t button_ack;
extern int cheat;
extern int skip_frame;
*/

/* Direction bitflags  */
#define DIR_L 1
#define DIR_R 2
#define DIR_UP 4
#define DIR_DOWN 8
#define DIR_HORIZ (DIR_R | DIR_L)
#define DIR_VERT (DIR_UP | DIR_DOWN)

enum HenryState {
  WALK,
  CLIMB,
  JUMP,
  FALL,
  LIFT
};

struct Henry {
  blit::point pos;
  blit::point tile;
  vec2 partial;
  vec2 speed;
  HenryState state;
  int dir;
  int falling;
  int sliding;
};

struct Player
{
  uint8_t score[8];
  uint8_t bonus[4];
  uint8_t egg[16];
  uint8_t grain[16];
  int lives;
};

// NOTE: EAT1 should never be rendered but is used in the state
// machine for duck eating animation
enum DuckState
{
  BORED,
  STEP,
  EAT1,
  EAT2,
  EAT3,
  EAT4
};

struct Duck
{
  blit::point pos;
  blit::point tile;
  DuckState state;
  int dir;
};

struct BigDuck
{
  blit::point pos;
  vec2 dPos;
  int dir;
  int frame;
};


class Game
{
public:
  Game(blit::size &);
  void Render(blit::surface &);
  void Tickle(uint32_t);

private:
  inline unsigned int getTile(int x, int y) { return tiles[y * COLUMNS + x]; }
  inline void setTile(int x, int y, uint8_t tile)
  {
    tiles[y * COLUMNS + x] = tile;
  }
  inline void addToTile(int x, int y, uint8_t contents)
  {
    tiles[y * COLUMNS + x] |= contents;
  }

  void loadLevel(int);
  void renderBackground(blit::surface &);
  void renderDucks(blit::surface &);
  void renderHenry(blit::surface &);
  void renderLifts(blit::surface &);
  void renderBigBird(blit::surface &);

  void pollKeys();
  void moveHenry();
  void jumpHenry();

  const blit::point tilePosition(blit::point &);
  const blit::point tilePosition(int, int);

  // Screen
  blit::size screenSize;

  // Uodate timing
  uint32_t lastTime;

  // input 
  int buttonsDown;
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
  int currentLevel;
  int currentPlayer;
  uint8_t tiles[ROWS * COLUMNS];
  Player playerData[MAX_PLAYERS];
  BigDuck bigDuck;
  Duck ducks[MAX_DUCKS];
  Henry henry;
};
