#ifndef PLAYER_H
#define PLAYER_H

#include "../lib/tigr.h"

typedef struct
{
    int x, y; // postition on screen//
    int speed;
    int health;
    int damage;
    Tigr *sprite;

    int balance;     // coins
    int waterCount;  // inventory: water
    int hammerCount; // inventory: hammer
} Player;
extern Player player;

void initPlayer(Player *p, const char *spritePath);
void movePlayer(Player *p, Tigr *screen);
void drawPlayer(Player *p, Tigr *screen);
void displayPlayerState(Player *p, Tigr *screen);

#endif
