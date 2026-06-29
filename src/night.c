#include "../lib/tigr.h"
#include "../lib/night.h"
#include <stdlib.h>
#include "../lib/player.h"
#include <stdio.h>
#include "../lib/crop.h"
#include "../lib/fence.h"

Tigr *houseN = NULL;
Tigr *fenceN = NULL;
Tigr *grassNight = NULL;
Tigr *pathN = NULL;

void assetsNight()
{
    if (!houseN)
        houseN = tigrLoadImage("assets/house.png");
    if (!fenceN)
        fenceN = tigrLoadImage("assets/fence.png");
    if (!grassNight)
        grassNight = tigrLoadImage("assets/nightgrass1.png"); // darker grass
    if (!pathN)
        pathN = tigrLoadImage("assets/path.png");
}

void updateFarmerNight(Tigr *screen)
{
    if (!player.sprite)
        initPlayer(&player, "assets/farmer.png");
    movePlayer(&player, screen);
    drawPlayer(&player, screen);
}

void drawNight(Tigr *screen)
{
    assetsNight();

    // Fill background with dark blue‑green tone
    tigrFill(screen, 0, 0, screen->w, screen->h, tigrRGB(20, 60, 80));

    // Draw night grass tiles
    if (grassNight)
    {
        for (int y = 0; y < screen->h; y += grassNight->h)
        {
            for (int x = 0; x < screen->w; x += grassNight->w)
            {
                tigrBlit(screen, grassNight, x, y, 0, 0, grassNight->w, grassNight->h);
            }
        }
    }

    // House stays visible
    if (houseN)
        tigrBlitAlpha(screen, houseN, 760, 200, 0, 0, houseN->w, houseN->h, 255);

    // Fence stays visible
    if (gameFence.health > 0)
    {
        if (fenceN)
            tigrBlitAlpha(screen, fenceN, 8, -30, 0, 0, fenceN->w, fenceN->h, 255);
    }
    if (gameFence.health <= 0)
    {
    }
    // Path stays visible
    if (pathN)
        tigrBlitAlpha(screen, pathN, 320, 100, 0, 0, pathN->w, pathN->h, 255);

    updateFarmerNight(screen);
}
