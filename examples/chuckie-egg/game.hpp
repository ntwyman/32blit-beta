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

enum DuckState { BORED, STEP, EAT1, EAT2, EAT3, EAT4 };

struct Duck {
  uint8_t x;
  uint8_t y;
  uint8_t tileX;
  uint8_t tileY;
  DuckState state;
  int dir;
};

struct Player {
  uint8_t score[8];
  uint8_t bonus[4];
  uint8_t egg[16];
  uint8_t grain[16];
  int lives;
};

class Game {
public:
  void Render(blit::surface &);
  // void Tickle();
  void LoadLevel(int levelNumber);

private:
  inline unsigned int getTile(int x, int y) { return tiles[y * COLUMNS + x]; }
  inline void setTile(int x, int y, uint8_t tile) {
    tiles[y * COLUMNS + x] = tile;
  }
  inline void addToTile(int x, int y, uint8_t contents) {
    tiles[y * COLUMNS + x] |= contents;
  }

  void renderBackground(blit::surface &);

  bool hasLift;
  int numGrain;
  int numDucks;
  int liftX;
  int currentPlayer;
  uint8_t tiles[ROWS * COLUMNS];
  Duck ducks[MAX_DUCKS];
  Player playerData[MAX_PLAYERS];
};
