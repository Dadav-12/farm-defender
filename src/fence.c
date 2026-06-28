#include "../lib/tigr.h"
#include <stdbool.h>
#include "../lib/gamestate.h"
#include "../lib/player.h"
#include "../lib/fence.h"
#include <stdlib.h>
#include <stdio.h>

Fence gameFence;

void initFence()
{
    gameFence.health = 300;
    gameFence.maxHealth = 500;
    gameFence.isDestroyed = false;
    gameFence.x = 650;
    gameFence.y = 350;
}

void displayFenceHealth(Tigr *screen)
{
    // Displa fence Health
    tigrFillRect(screen, 20, 200, 150, 40, tigrRGB(255, 165, 0)); // Orange Box
    tigrPrint(screen, tfont, 30, 210, tigrRGB(255, 255, 255), "Fence = %d / %d", gameFence.health, gameFence.maxHealth);
}