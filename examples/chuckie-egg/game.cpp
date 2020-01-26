#include "game.hpp"
#include "levels.hpp"
#include "sprites.hpp"
#include <cstring>

using namespace blit;

Game::Game(size &screen) : screenSize(screen), lastTime(0) {
  this->loadLevel(0);
}

const point Game::tilePosition(int x, int y) {
  return point(x * TILE_STRIDE, this->screenSize.h - ((y + 1) * TILE_STRIDE));
}

const point Game::tilePosition(point &tile) {
  return this->tilePosition(tile.x, tile.y);
}

void Game::loadLevel(int levelNumber) {

  // Clear out the existing tiles
  memset(&this->tiles[0], 0, sizeof(this->tiles));
  this->hasBigDuck = levelNumber > 7;

  /* Get faster as we go up through the levels
  i = level_index >> 4;
  if (i > 8) {
      i = 8;
  }
  timer_ticks[0] = 9 - i;
  timer_ticks[1] = 0;
  timer_ticks[2] = 0;
  */

  // Data for the level
  const uint8_t *p = getLevelData(levelNumber);
  int numWalls = *(p++);
  int numLadders = *(p++);
  this->hasLift = bool(*p++);
  this->numGrain = *(p++);
  this->numDucks = *(p++);

  int x, y;
  while (numWalls--) {
    y = *(p++);       // row
    x = *(p++);       // first column
    int end = *(p++); // last column
    while (x <= end) {
      setTile(x, y, TILE_WALL);
      x++;
    }
  }

  while (numLadders--) {
    x = *(p++);
    y = *(p++);
    int end = *(p++);
    while (y <= end) {
      addToTile(x, y, TILE_LADDER);
      y++;
    }
  }

  if (hasLift) {
    this->liftX = int(*(p++)) << 3;
  }

  int eggsLeft = 0;
  for (int i = 0; i < NUM_EGGS; i++) {
    x = *(p++);
    y = *(p++);
    setTile(x, y, (i << 4) | TILE_EGG);
    /*    if (player_data->egg[i] == 0) {
          Do_InitTile(x, y, (i << 4) | TILE_EGG);
          eggs_left++;
        }
    */
  }

  for (int i = 0; i < this->numGrain; i++) {
    x = *(p++);
    y = *(p++);
    setTile(x, y, (i << 4) | TILE_GRAIN);
    /*        if (player_data->grain[i] == 0) {
                Do_InitTile(x, y, (i << 4) | TILE_GRAIN);
            }
    */
  }

  for (int i = 0; i < MAX_DUCKS; i++) {
    ducks[i].tile.x = *(p++);
    ducks[i].tile.y = *(p++);
  }
  this->currentLevel = levelNumber;

  if (this->hasLift) {
    this->liftY[0] = 232;
    this->liftY[1] = 142;
    currentLift = 0;
  }

  this->bigDuck.pos = point(4, 36);
  this->bigDuck.dPos = vec2(0, 0);
  this->bigDuck.frame = 0;
  this->bigDuck.dir = 0;

  // First time with the big duck you get a break
  if ((levelNumber >> 3) == 1) {
    this->numDucks = 0;
  }
  // Fourth time through the levels you get the full enchilada
  if (levelNumber >= 24) {
    this->numDucks = 5;
  }

  for (int i = 0; i < this->numDucks; i++) {
    Duck *pDuck = &this->ducks[i];
    pDuck->pos = this->tilePosition(pDuck->tile);
    pDuck->pos.y -= 12; // Ducks are tall.
    pDuck->state = BORED;
    pDuck->dir = DIR_R;
  }

  this->henry.tile = {7, 3};
  this->henry.pos = this->tilePosition(this->henry.tile);
  this->henry.partial = {7, 0};
  this->henry.state = WALK; // player_mode = PLAYER_WALK;
  this->henry.dir = DIR_R;
  // button_ack = 0x1f;
}

void Game::renderBackground(surface &fb) {
  // WARNING MAGIC NUMBERS ABOUND
  // Score
  fb.sprite(SpriteScore, point(0, 0));
  fb.sprite(SpriteBlank, point(27, 0));

  // Player
  fb.sprite(SpritePlayer, point(0, 12));
  fb.sprite(SpriteDigits[this->currentPlayer + 1], point(27, 13));

  // Level
  fb.sprite(SpriteLevel, point(36, 12));
  int n = this->currentLevel + 1;
  fb.sprite(SpriteDigits[n % 10], point(69, 13));
  n /= 10;
  fb.sprite(SpriteDigits[n % 10], point(64, 13));
  if (n > 10) {
    fb.sprite(SpriteDigits[n % 10], point(59, 13));
  }

  // Bonus
  fb.sprite(SpriteBonus, point(78, 12));
  fb.sprite(SpriteDigits[0], point(117, 13));

  // Time
  fb.sprite(SpriteTime, point(126, 12));

  // Level deets
  for (int x = 0; x < COLUMNS; x++) {
    for (int y = 0; y < ROWS; y++) {
      const point &pos = this->tilePosition(x, y);

      point(x * TILE_STRIDE, fb.bounds.h - ((y + 1) * TILE_STRIDE));
      uint8_t tile = getTile(x, y);
      if (tile & TILE_WALL) {
        fb.sprite(SpriteWall, pos);
      }
      if (tile & TILE_LADDER) {
        fb.sprite(SpriteLadder, pos);
      }
      if (tile & TILE_EGG) {
        fb.sprite(SpriteEgg, pos);
      }
      if (tile & TILE_GRAIN) {
        fb.sprite(SpriteGrain, pos);
      }
    }
  }

  //  Cage
  const Sprite &cageSprite = this->hasBigDuck ? SpriteCageOpen : SpriteCage;
  fb.sprite(cageSprite, point(0, 20));
}

void Game::renderDucks(surface &fb) {

  for (int i = 0; i < this->numDucks; i++) {

    Duck &duck = this->ducks[i];

    point pos = duck.pos;
    int dir = duck.dir;
    sprite_transform flip = (dir == DIR_L) ? HORIZONTAL : NONE;
    Sprite sprite = SpriteDuck;

    switch (duck.state) {
    case BORED:
      if (dir & DIR_VERT) { // Going up or down
        sprite = SpriteDuckUp;
      }
      break;
    case STEP:
      if (dir & DIR_HORIZ) {
        sprite = SpriteDuckStep;
      } else {
        sprite = SpriteDuckUpStep;
      }
      break;
    case EAT2:
    case EAT3:
    case EAT4:
      sprite = (duck.state == EAT3) ? SpriteDuckEat2 : SpriteDuckEat;
      if (dir == DIR_L) {
        pos.x -= 8;
      }
      break;
    default:
      abort();
    }

    fb.sprite(sprite, pos, flip);
  }
}

void Game::renderHenry(surface &fb) {

  Henry &h = this->henry;
  sprite_transform flip = NONE;
  rect *sequence;
  int spriteIndex;

  if (h.dir == 0) { // Not going left or right
    sequence = SpriteHenryClimbs;
    spriteIndex = h.pos.y;
  } else {
    sequence = SpriteHenryWalks;
    spriteIndex = h.pos.x;
    if (h.dir == DIR_L) {
      flip = HORIZONTAL;
    }
  }

  spriteIndex = (spriteIndex >> 1) & 0x03; // Change animation every 2 pixels

  if (h.state != CLIMB) {
    if (h.speed.x == 0) {
      spriteIndex = 0;
    }
  } else if (h.speed.y == 0) {
    spriteIndex = 0;
  }
  fb.sprite(sequence[spriteIndex], h.pos, flip);
}

void Game::renderLifts(surface &fb) {
  if (this->hasLift) {
    fb.sprite(SpriteLift, point(this->liftX, this->liftY[0]));
    fb.sprite(SpriteLift, point(this->liftX, this->liftY[1]));
  }
}

void Game::renderBigBird(surface &fb) {
  BigDuck &bigBird = this->bigDuck;
  sprite_transform flip = (bigBird.dir == DIR_L) ? HORIZONTAL : NONE;
  fb.sprite(bigBird.frame ? SpriteBigDuckFrame : SpriteBigDuck, bigBird.pos,
            flip);
}

void Game::Render(surface &fb) {
  /*
   Render callback is roughly every 25 ms
  */
  this->renderBackground(fb);
  this->renderDucks(fb);
  this->renderHenry(fb);
  this->renderLifts(fb);
  this->renderBigBird(fb);
}

void Game::pollKeys() {

  int buttons = 0;
  if (pressed(button::DPAD_LEFT) || joystick.x < -0.1f) {
    buttons |= BUTTON_LEFT;
  }
  if (pressed(button::DPAD_RIGHT) || joystick.x > 0.1f) {
    buttons &= ~BUTTON_LEFT;
    buttons |= BUTTON_RIGHT;
  }
  if (pressed(button::DPAD_UP) || joystick.y > 0.1f) {
    buttons |= BUTTON_UP;
  }
  if (pressed(button::DPAD_DOWN) || joystick.y < -0.1f) {
    buttons &= ~BUTTON_UP;
    buttons |= BUTTON_DOWN;
  }
  if (pressed(button::A | button::JOYSTICK)) {
    buttons |= BUTTON_JUMP;
  }
  this->buttonsDown = buttons;
}

void Game::moveHenry() {
  Henry &h = this->henry;
  int buttonsDown = this->buttonsDown;
  h.speed = {0, 0};
  if (buttonsDown & BUTTON_RIGHT) {
    h.speed.x++;
  }
  if (buttonsDown & BUTTON_LEFT) {
    h.speed.x--;
  }
  if (buttonsDown & BUTTON_DOWN) {
    h.speed.y--;
  }
  if (buttonsDown & BUTTON_UP) {
    h.speed.y++;
  }
  h.speed.y *= 2;
  /*
  switch (h.state) {
  case HenryState::JUMP:
    this->jumpHenry();
    break;
  case HenryState::FALL:
    h.falling++;
    int tmp = h.falling;
    if (tmp < 4) {
      h.speed.x = h.sliding;
      h.speed.y = -1;
    }
  }
  */
}

void Game::jumpHenry() {
  // FOR NWO
}
void Game::Tickle(uint32_t time)
/*
The Update tick - runs roughly every 10 ms
*/
{
  // First time, just note the time.
  if (this->lastTime == 0) {
    this->lastTime = time;
    return;
  }

  // Wait until roughly 3/100ths of a second has gone by
  if ((time - this->lastTime) < UPDATE_INTERVAL_MS) {
    return;
  }

  this->pollKeys();
}
