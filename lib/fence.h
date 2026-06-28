#ifndef FENCE_H
#define FENCE_H

#include "../lib/tigr.h"
#include <stdbool.h>

typedef struct
{
    int health;
    int maxHealth;
    bool isDestroyed;
    int x, y;
} Fence;

extern Fence gameFence;

void initFence();
void repairFence(Tigr *screen, Player *player);
void displayFenceHealth(Tigr *screen);

#endif