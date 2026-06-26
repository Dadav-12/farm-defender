#include "../lib/tigr.h"
#include "morning.h"
#include <stdlib.h>
#include "player.h"
#include "store.h"
#include <stdio.h>

Tigr *house = NULL;
Tigr *shop = NULL;
Tigr *fence = NULL;
Tigr *grass = NULL;
Tigr *path = NULL;

void assets()
{
    if (!house)
    {
        house = tigrLoadImage("assets/house.png");
    }
    if (!shop)
    {
        shop = tigrLoadImage("assets/shop.png");
    }
    if (!fence)
    {
        fence = tigrLoadImage("assets/fence.png");
    }
    if (!grass)
    {
        grass = tigrLoadImage("assets/grass.png");
    }
    if (!path)
    {
        path = tigrLoadImage("assets/path.png");
    }
}

void drawFarmPlot(Tigr *screen)
{
    TPixel soil = tigrRGB(160, 82, 45);
    TPixel border = tigrRGB(139, 69, 19);

    int left = 250;
    int top = 160;
    int rows = 3, cols = 3, gap = 10;

    int bedWidth = 93;   // fixed width
    int bedHeight = 126; // fixed height

    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            int x = left + c * (bedWidth + gap);
            int y = top + r * (bedHeight + gap);

            tigrFillRect(screen, x, y, bedWidth, bedHeight, soil);
            tigrRect(screen, x, y, bedWidth, bedHeight, border);
        }
    }
}

void updateFarmer(Tigr *screen)
{
    if (!player.sprite)
    {
        initPlayer(&player, "assets/farmer.png");
    }
    movePlayer(&player, screen);
    drawPlayer(&player, screen);
}

void drawMorning(Tigr *screen)
{
    assets();

    // Draw the grass background full screen//
    tigrFill(screen, 0, 0, screen->w, screen->h, tigrRGB(34, 139, 34));

    // Draw grass as the back ground of the map
    if (grass)
    {
        for (int y = 0; y < screen->h; y += grass->h)
        {
            for (int x = 0; x < screen->w; x += grass->w)
            {
                // Draw grass tile at (x, y)
                tigrBlit(screen, grass, x, y, 0, 0, grass->w, grass->h);
            }
        }
    }

    drawFarmPlot(screen);

    // Draw house on the right side of the path
    if (house)
    {
        tigrBlitAlpha(screen, house, 760, 200, 0, 0, house->w, house->h, 255);
    }

    // Draw shop below the house
    if (shop)
    {
        tigrBlitAlpha(screen, shop, 800, 350, 0, 0, shop->w, shop->h, 255);
    }

    // Draaw the fence surrounding the base
    if (fence)
    {
        tigrBlitAlpha(screen, fence, 8, -30, 0, 0, fence->w, fence->h, 255);
    }

    // Draw path
    if (path)
    {
        tigrBlitAlpha(screen, path, 320, 100, 0, 0, path->w, path->h, 255);
    }

    updateFarmer(screen);
    storeSystem(screen, &player);
}