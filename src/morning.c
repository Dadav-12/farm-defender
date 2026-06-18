#include "../lib/tigr.h"
#include "morning.h"
#include<stdlib.h>
#include "player.h"
#include<stdio.h>
 Tigr *house = NULL;
 Tigr *shop = NULL;
 Player farmer;
 void assets(){
    if(!house){
        house = tigrLoadImage("assets/house.png");
    }
    if(!shop){
        shop = tigrLoadImage("assets/shop.png");
    }

 }

 void drawFence(Tigr *screen)
 {
     TPixel brown = tigrRGB(139, 69, 19); // fence color

     int left = 200, top = 120;
     int width = 880, height = 460;
     int thickness = 15; // thickness of the fence

     // Top border
     tigrFillRect(screen, left, top, width, thickness, brown);

     // Bottom border
     tigrFillRect(screen, left, top + height, width, thickness, brown);

     // Left border
     tigrFillRect(screen, left, top, thickness, height, brown);

     // Right border
     tigrFillRect(screen, left + width, top, thickness, height + thickness, brown);
 }

void drawPath(Tigr *screen)
{
    TPixel dirt = tigrRGB(210, 180, 140); // dirt color

    // Vertical path (centered, touching top and bottom fence)
    tigrFillRect(screen, 610, 120, 40, 456, dirt);

    // Right branch (shorter, connecting to house area)
    tigrFillRect(screen, 610, 320, 180, 40, dirt);
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
    if (!farmer.sprite)
    {
        initPlayer(&farmer, "assets/farmer.png");
    }
    movePlayer(&farmer, screen);
    drawPlayer(&farmer, screen);
}
void drawMorning(Tigr *screen)
{
    assets();

    // Draw the grass background full screen//
    tigrFill(screen, 0, 0, screen->w, screen->h, tigrRGB(34, 139, 34));
    drawFence(screen);
    drawPath(screen);
    drawFarmPlot(screen);
    // Draw house on the right side of the path
    if(house){
        tigrBlitAlpha(screen, house, 760, 260, 0, 0, house->w, house->h, 255);
    }

    // Draw shop below the house
    if(shop){
    tigrBlitAlpha(screen, shop, 800, 400, 0, 0, shop->w, shop->h,255);}
    updateFarmer(screen);
}


