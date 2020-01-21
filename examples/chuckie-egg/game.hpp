#pragma once
#include "32blit.hpp"
#include <cstdint>

#define ROWS 25
#define COLUMNS 20
#define STRIDE 8

#define TILE_WALL 1
#define TILE_LADDER 2
#define TILE_EGG 4
#define TILE_GRAIN 8

class Game {
public:
  void Render(surface &);
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
  uint8_t tiles[ROWS * COLUMNS];
};