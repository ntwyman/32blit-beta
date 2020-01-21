#include "32blit.hpp"
#include "game.hpp"
#include <iostream>

using namespace blit;
uint32_t last_frame = 0;

Game *game;
extern uint8_t egg_sheet[];
int level_index = 0;

void init() {
  set_screen_mode(screen_mode::hires);
  game = new Game();
  game->LoadLevel(0);
  fb.sprites = spritesheet::load(egg_sheet, nullptr);
}

int left_down = 0;
int right_down = 0;

void update(uint32_t time) {
  auto level = level_index;
  if (pressed(button::DPAD_LEFT)) {
    left_down = 1;
  } else if (left_down == 1) {
    left_down = 0;
    level_index--;
  }
  if (pressed(button::DPAD_RIGHT)) {
    right_down = 1;
  } else if (right_down == 1) {
    right_down = 0;
    level_index++;
  }
  level_index &= 0x07;
  if (level_index != level) {
    game->LoadLevel(level_index);
  }
}

void render(uint32_t time) {
  char time_str[255];

  fb.pen(rgba{0, 0, 0});
  fb.clear();
  game->Render(fb);
}
