#pragma once
#include "32blit.hpp"
#include <cstdint>

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
  // void Tickle();
  void LoadLevel(int levelNumber);

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

  void renderBackground(blit::surface &);
  void renderDucks(blit::surface &);
  void renderHenry(blit::surface &);
  void renderLifts(blit::surface &);

  const blit::point tilePosition(blit::point &);
  const blit::point tilePosition(int, int);

  // Screen
  blit::size screenSize;

  // state
  int currentLevel;
  int currentPlayer;
  // int numPlayers

  // Level info
  bool hasLift;
  int numGrain;
  int numDucks;
  int liftX;
  int liftY[2];
  int currentLift;
  bool hasBigDuck;

  uint8_t tiles[ROWS * COLUMNS];
  Player playerData[MAX_PLAYERS];
  BigDuck bigDuck;
  Duck ducks[MAX_DUCKS];
  Henry henry;
};
