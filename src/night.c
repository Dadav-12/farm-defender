#include "../lib/tigr.h"
#include "night.h"
#include "player.h"

void drawNight(Tigr *screen)
{
    // Clear screen with a dark blue "night" color
    tigrClear(screen, tigrRGB(10, 15, 40));

    // Draw a temporary moon
    tigrFillCircle(screen, 1100, 150, 60, tigrRGB(220, 220, 230));

    // Alert text
    tigrPrint(screen, tfont, 550, 100, tigrRGB(255, 0, 0), "THE ENEMIES ARE COMING!");

    // Ensure the player can still move and be drawn during the night
    if (!player.sprite)
    {
        initPlayer(&player, "assets/farmer.png");
    }
    movePlayer(&player, screen);
    drawPlayer(&player, screen);
}