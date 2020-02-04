#include "game.hpp"
#include "levels.hpp"
#include "sprites.hpp"
#include <cstring>
// #include <iostream>

using namespace blit;

// Gives the top left ofa tile
point Game::tilePosition(int x, int y) {
    return point(x * TILE_STRIDE, this->screenSize.h - ((y + 1) * TILE_STRIDE));
}

point Game::tilePosition(point &tile) {
    return this->tilePosition(tile.x, tile.y);
}

unsigned int Game::getTile(int x, int y) {
    if (x < 0 || x >= COLUMNS || y < 0 || y >= ROWS) {
        return 0;
    }
    return tiles[y * COLUMNS + x];
}

bool Game::isTileWall(int x, int y) {
    return (this->getTile(x, y) & TILE_WALL) != 0;
}
void Game::loadLevel(unsigned int levelNumber) {

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
        this->liftX = *(p++) << 3u;
    }

    for (unsigned int i = 0; i < NUM_EGGS; i++) {
        x = *(p++);
        y = *(p++);
        this->eggsLeft++;
        setTile(x, y, (i << 4u) | TILE_EGG);
        /*    if (player_data->egg[i] == 0) {
              Do_InitTile(x, y, (i << 4) | TILE_EGG);
              eggs_left++;
            }
        */
    }

    for (unsigned int i = 0; i < this->numGrain; i++) {
        x = *(p++);
        y = *(p++);
        setTile(x, y, (i << 4u) | TILE_GRAIN);
        /*        if (player_data->grain[i] == 0) {
                    Do_InitTile(x, y, (i << 4) | TILE_GRAIN);
                }
        */
    }

    for (auto &duck : ducks) {
        duck.tile.x = *(p++);
        duck.tile.y = *(p++);
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
    if (levelNumber >> 3u == 1) {
        this->numDucks = 0;
    }
    // Fourth time through the levels you get the full enchilada
    if (levelNumber >= 24) {
        this->numDucks = 5;
    }

    for (int i = 0; i < this->numDucks; i++) {
        auto &duck = this->ducks[i];
        duck.pos = this->tilePosition(duck.tile);
        duck.pos.y -= 12; // Ducks are tall.
        duck.state = BORED;
        duck.dir = DIR_R;
    }

    auto &h = this->henry;
    h.tile = {7, 2};
    h.pos = tilePosition(this->henry.tile);
    h.partial = {7, 0};
    h.pos.x += 7;
    h.pos.y -= 8;   // Henry is 2 tiles tall
    h.state = WALK; // player_mode = PLAYER_WALK
    h.dir = DIR_R;
    // button_ack = 0x1f;
}

void Game::renderBackground(surface &s) {
    // WARNING MAGIC NUMBERS ABOUND
    // Score
    s.sprite(SpriteScore, point(0, 0));
    s.sprite(SpriteBlank, point(27, 0));

    // Player
    s.sprite(SpritePlayer, point(0, 12));
    s.sprite(SpriteDigits[this->currentPlayer + 1], point(27, 13));

    // Level
    s.sprite(SpriteLevel, point(36, 12));
    int n = this->currentLevel + 1;
    s.sprite(SpriteDigits[n % 10], point(69, 13));
    n /= 10;
    s.sprite(SpriteDigits[n % 10], point(64, 13));
    if (n > 10) {
        s.sprite(SpriteDigits[n % 10], point(59, 13));
    }

    // Bonus
    s.sprite(SpriteBonus, point(78, 12));
    s.sprite(SpriteDigits[0], point(117, 13));

    // Time
    s.sprite(SpriteTime, point(126, 12));

    // Level deets
    for (int x = 0; x < COLUMNS; x++) {
        for (int y = 0; y < ROWS; y++) {
            const point &pos = this->tilePosition(x, y);

            uint8_t tile = getTile(x, y);
            if (tile & TILE_WALL) {
                s.sprite(SpriteWall, pos);
            }
            if (tile & TILE_LADDER) {
                s.sprite(SpriteLadder, pos);
            }
            if (tile & TILE_EGG) {
                s.sprite(SpriteEgg, pos);
            }
            if (tile & TILE_GRAIN) {
                s.sprite(SpriteGrain, pos);
            }
        }
    }

    //  Cage
    const Sprite &cageSprite = this->hasBigDuck ? SpriteCageOpen : SpriteCage;
    s.sprite(cageSprite, point(0, 20));
}

void Game::renderDucks(surface &s) {

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
        s.sprite(sprite, pos, flip);
    }
}

void Game::renderHenry(surface &s) {

    Henry &h = this->henry;
    sprite_transform flip = NONE;
    rect *sequence;
    unsigned int spriteIndex;

    if ((h.dir & (DIR_UP | DIR_DOWN)) != 0) { // Not going left or right
        sequence = SpriteHenryClimbs;
        spriteIndex = h.pos.y;
    } else {
        sequence = SpriteHenryWalks;
        spriteIndex = h.pos.x;
        if (h.dir == DIR_L) {
            flip = HORIZONTAL;
        }
    }

    spriteIndex = (spriteIndex >> 1u) & 0x03u; // Change animation every 2 pixels

    if (h.state != CLIMB) {
        if (h.speed.x == 0) {
            spriteIndex = 0;
        }
    } else if (h.speed.y == 0) {
        spriteIndex = 0;
    }
    s.sprite(sequence[spriteIndex], h.pos, flip);
}

void Game::renderLifts(surface &s) {
    if (this->hasLift) {
        s.sprite(SpriteLift, point(this->liftX, this->liftY[0]));
        s.sprite(SpriteLift, point(this->liftX, this->liftY[1]));
    }
}

void Game::renderBigBird(surface &s) {
    BigDuck &bigBird = this->bigDuck;
    sprite_transform flip = (bigBird.dir == DIR_L) ? HORIZONTAL : NONE;
    s.sprite(bigBird.frame ? SpriteBigDuckFrame : SpriteBigDuck, bigBird.pos,
             flip);
}

void Game::pollKeys() {

    uint16_t down = 0;
    if (pressed(button::DPAD_LEFT) || joystick.x < -0.1f) {
        down |= BUTTON_LEFT;
    }
    if (pressed(button::DPAD_RIGHT) || joystick.x > 0.1f) {
        down &= ~BUTTON_LEFT;
        down |= BUTTON_RIGHT;
    }
    if (pressed(button::DPAD_UP) || joystick.y < -0.1f) {
        down |= BUTTON_UP;
    }
    if (pressed(button::DPAD_DOWN) || joystick.y > 0.1f) {
        down &= ~BUTTON_UP;
        down |= BUTTON_DOWN;
    }
    if (pressed(button::A | button::JOYSTICK)) {
        down |= BUTTON_JUMP;
    }
    this->buttonsDown = down;
}

void Game::moveHenry() {
    Henry &h = this->henry;
    uint16_t down = this->buttonsDown;
    h.speed = {0, 0};
    if (down & BUTTON_RIGHT) {
        h.speed.x++;
    }
    if (down & BUTTON_LEFT) {
        h.speed.x--;
    }
    if (down & BUTTON_DOWN) {
        h.speed.y--;
    }
    if (down & BUTTON_UP) {
        h.speed.y++;
    }
    h.speed.y *= 2;
    switch (h.state) {
        case HenryState::JUMP:
            this->jumpHenry(h);
            break;
        case HenryState::FALL:
            this->fallHenry(h);
            break;
        case HenryState::CLIMB:
            this->climbHenry(h);
            break;
        case HenryState::WALK:
            this->walkHenry(h);
            break;
        case HenryState::LIFT:
            this->liftHenry(h);
            break;
    }
    this->animateHenry(h);
}

bool Game::canGrabLadder(Henry &h, int16_t speedY) {

    int16_t newPartialX  = h.partial.x + h.speed.x;
    if (newPartialX != LADDER_PARTIAL_X) {
        return false;
    }
    if (speedY == 0) {
        return false;
    }
    int16_t newPartialY = h.partial.y + h.speed.y;
    int16_t x = h.tile.x;
    int16_t y = h.tile.y;
    if (speedY > 0) {
        if ((this->getTile(x, y) & TILE_LADDER) == 0) { // Not on a ladder
            if (h.partial.y >=4) {
                // Check in case there's a ladder just above
                if ((this->getTile(x, y + 1) & TILE_LADDER) == 0) {
                    return false;
                }
            }
        }
        h.state = HenryState::CLIMB;
        if (newPartialY & 1) {
            h.speed.y++;
        }
        return true;
    }
    if ((this->getTile(x, y) & TILE_LADDER) == 0) {
        return false;
    }
    if ((this->getTile(x, y-1) & TILE_LADDER) == 0) {
        return false;
    }
    h.state = HenryState::CLIMB;
    if (newPartialY & 1) {
        h.speed.y--;
    }
    return true;
}

void Game::jumpHenry(Henry &h) {

    h.speed.x = h.sliding;
    int16_t speedY= h.speed.y;
    int16_t fallRate = h.falling >> 2;
    if (fallRate >= 6)
        fallRate = 6;
    h.speed.y = 2 - fallRate;
    h.falling++;
    if (h.pos.y == 20) { // Top
        h.speed.y = -1;
        h.falling = 10;
    } else if (this->canGrabLadder(h, speedY)) {
        return;
    }

    int16_t newPartialY = h.partial.y + h.speed.y;
    uint8_t x = h.tile.x;
    uint8_t y = h.tile.y;
    if (newPartialY == 0) {
        if (this->isTileWall(x, y-1)) {
            h.state = HenryState::WALK;
        }
    } else if (newPartialY > 0) {
        if (newPartialY == 8 && this->isTileWall(x, y)) {
            h.state = HenryState::WALK;
        }
    } else {
        if (this->isTileWall(x, y-1 )) {
            h.state = HenryState::WALK;
            h.speed.y = -h.partial.y;
        }
    }
}

void Game::fallHenry(Henry &h) {
    h.falling++;
    int rate = h.falling;
    if (rate < 4) {
        h.speed.x = h.sliding;
        h.speed.y = -1;
    } else {
        h.speed.x = 0;
        rate = h.falling >> 2u;
        if (rate > 3) {
            rate = 3;
        }
        h.speed.y = -(rate + 1);
    }

    // Check what's in the next tile down
    if ((h.speed.y + h.partial.y) <= 0) {
        if (this->isTileWall(h.tile.x, h.tile.y - 1)) {
            h.state = HenryState::WALK;
            h.speed.y = -h.partial.y;
        }
    }
}

bool Game::startJump(Henry &h) {
    if ((buttons & BUTTON_JUMP) == 0) {
        return false;
    }
    debugf("StartJump");
    this->buttonAck |= 0x10u; // FOR NOW What is this ?
    h.falling = 0;
    h.state = HenryState::JUMP;
    h.sliding = h.speed.x;
    if (h.sliding > 0) {
        h.dir = DIR_R;
    } else if (h.sliding < 0) {
        h.dir = DIR_L;
    }
    this->jumpHenry(h);
    return true;
}

void Game::climbHenry(Henry &h) {
    if (this->startJump(h)) {
        return;
    }
    // Want to get off
    if (h.speed.x != 0 && h.partial.y == 0) {
        if (this->isTileWall(h.tile.x, h.tile.y - 1)) {
            h.speed.y = 0;
            h.state = HenryState::WALK;
        }
    }
    if (h.state != HenryState::WALK) {
        h.speed.x = 0;
        if (h.speed.y != 0 && h.partial.y == 0) {
            point checkTile = h.tile;
            if (h.speed.y >= 0) {
                checkTile.y += 2;
            } else {
                checkTile.y -= 1;
            }
            if ((this->getTile(checkTile.x, checkTile.y) & TILE_LADDER) == 0) {
                h.speed.y = 0;
            }
        }
    }
    h.dir = h.speed.y >= 0 ? DIR_UP : DIR_DOWN;
}

void Game::walkHenry(Henry &h) {

    if (this->startJump(h)) {
        return;
    }

    if (h.speed.y != 0) { // Trying to climb
        if (h.partial.x == LADDER_PARTIAL_X) {
            int y = h.tile.y + (h.speed.y > 0 ? 2 : -1);
            if (this->getTile(h.tile.x, y) & TILE_LADDER) {
                h.speed.x = 0;
                h.state = HenryState::CLIMB;
                return;
            }
        }
        h.speed.y = 0;
    }

    int newPartialX = h.partial.x + h.speed.x;
    int tileX = h.tile.x;
    if (newPartialX < 0) {
        tileX -= 1;
    } else if (newPartialX >= 8) {
        tileX++;
    }
    if (!this->isTileWall(tileX, h.tile.y - 1) ) {
        if ((newPartialX & 7) < 4) {
            h.sliding = 1;
            h.falling = 1;
        } else {
            h.sliding = -1;
            h.falling = 0;
        }
        h.state = HenryState::FALL;
    }

    if (this->cannotMove(h)) {
        h.speed.x = 0;
    }
    if (h.speed.x > 0) {
        h.dir = DIR_R;
    } else if (h.speed.x < 0) {
        h.dir = DIR_L;
    }
}

void Game::liftHenry(Henry &h) {
    if (this->startJump(h)) {
        return;
    }
}

void Game::animateHenry(Henry &h) {

    h.pos.x += h.speed.x;
    int16_t newPartialX = h.partial.x + h.speed.x;
    if (newPartialX < 0) {
        h.tile.x--;
    } else if (newPartialX >= 8) {
        h.tile.x++;
    }
    h.partial.x = newPartialX & 7;
    h.pos.y -= h.speed.y; // Screen pos has inverted y/
    int16_t newPartialY = h.partial.y + h.speed.y;
    if (newPartialY < 0) {
        h.tile.y--;
    } else if (newPartialY >= 8) {
        h.tile.y++;
    }
    h.partial.y = newPartialY & 7;

    uint16_t x = h.tile.x;
    uint16_t y = h.tile.y;
    if (h.partial.y >= 4) {
        y++;
    }

    uint8_t tile = this->getTile(x, y);
    if ((tile & (TILE_EGG | TILE_GRAIN)) == 0)
        return;
    Player &player = this->playerData[this->currentPlayer];
    if ((tile & TILE_GRAIN) == 0) {
        this->eggsLeft--;
        uint8_t eggIndex = tile >> 4;
        //        squidge(6);
        player.egg[eggIndex]--;
        this->setTile(x, y, 0);
        uint16_t score = (this->currentLevel / 4) + 1;
        if (score >= 10) {
            score = 10;
        }
        this->addScore(5, score);
    } else {
        //        squidge(5);
        uint8_t grainIndex = tile >> 4;
        player.grain[grainIndex]--;
        this->setTile(x, y, 0);
        this->addScore(6, 5);
        // bonus_hold = 14;
    }
}

bool Game::cannotMove(Henry &h) {
    if (h.speed.x == 0) {
        return false;
    }
    if (h.speed.x < 0) {
        if (h.pos.x == 0) {
            return true;
        }
        if (h.partial.x >= 2 || h.speed.y == 2) {
            return false;
        }
        uint16_t x = h.tile.x - 1;
        uint16_t y = h.tile.y;
        int16_t partialY = h.partial.y + h.speed.y;
        if (partialY < 0) {
            y--;
        } else if (partialY >= 8) {
            y++;
        }
        if (this->isTileWall(x, y)) {
            return true;
        }
        if (h.speed.y >= 0) {
            return false;
        }
        x = h.tile.x - 1;
        y++;
        return this->isTileWall(x, y);
    }
    if (h.pos.x >= 152) {
        return true;
    }
    if (h.partial.x < 5) {
        return false;
    }
    if (h.speed.y == 2) {
        return false;
    }
    uint16_t x = h.tile.x + 1;
    uint16_t y = h.tile.y;
    int16_t partialY = h.partial.y + h.speed.y;
    if (partialY < 0) {
        y--;
    } else if (partialY >= 8) {
        y++;
    }
    if (this->isTileWall(x, y)) {
        return true;
    }
    if (h.speed.y > 0) {
        return false;
    }
    x = h.tile.x + 1;
    y++;
    return this->isTileWall(x, y);
}

void Game::addScore(int n, int x) {
    // FOR NOW
}

void Game::SetScreenSize(blit::size &size) {
    this->screenSize = size;
    this->loadLevel(0);
}

void Game::Tickle(uint32_t time)
/*
The Update tick - runs roughly every 10 ms
*/
{

    if (this->lastTime == 0) {
        this->lastTime = time;
    }

    // Wait until roughly 3/100ths of a second has gone by
    if ((time - this->lastTime) < UPDATE_INTERVAL_MS) {
        return;
    }

    this->pollKeys();
    this->moveHenry();
}

void Game::Render(surface &s) {
    /*
     Render callback is roughly every 25 ms
    */
    this->renderBackground(s);
    this->renderDucks(s);
    this->renderHenry(s);
    this->renderLifts(s);
    this->renderBigBird(s);
}
