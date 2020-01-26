#include "32blit.hpp"
#include "game.hpp"
#include <iostream>

using namespace blit;
uint32_t last_frame = 0;

Game *game;
extern uint8_t *getSpriteData();

void init() {
  set_screen_mode(screen_mode::hires);
  fb.sprites = spritesheet::load(getSpriteData(), nullptr);
  game = new Game(fb.bounds);
}

void update(uint32_t time) { game->Tickle(time); }

void render(uint32_t time) {
  fb.pen(rgba{0, 0, 0});
  fb.clear();
  game->Render(fb);
}
