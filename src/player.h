#ifndef PLAYER_H
#define PLAYER_H

#include "../lib/tigr.h"

typedef struct
{
    int x, y;
    int speed;
    int health;
    int damage;
    Tigr *sprite;
} Player;

void initPlayer(Player *p, const char *spritePath);
void movePlayer(Player *p, Tigr *screen);
void drawPlayer(Player *p, Tigr *screen);

#endif
