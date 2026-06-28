#include "../lib/tigr.h"
#include <stdbool.h>
#include "../lib/crop.h"
#include "../lib/gamestate.h"
#include "../lib/player.h"
#include <stdlib.h>
#include<stdio.h>
// Global 
Crop crops[ROWS][COLS];

// Sprite
static Tigr *spriteHarvest = NULL;
static Tigr *spriteNoHarvest = NULL;

void initCrops()
{
    int startX = 230, startY = 160;
    int gapX = 103, gapY = 136;

    // Load sprites once
    spriteHarvest = tigrLoadImage("assets/harvest1.png");
    spriteNoHarvest = tigrLoadImage("assets/noharvest1.png");

    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            crops[r][c].x = startX + c * gapX;
            crops[r][c].y = startY + r * gapY;
            crops[r][c].health = 100;
            crops[r][c].canHarvest = false;
            crops[r][c].isWatering = false;
            crops[r][c].cropAlive = true;
            crops[r][c].cropHP = 100;
        }
    }
}

void cropLogic(Player *player, Tigr *screen)
{
    if (currentState == MORNING )
    {
        for (int r = 0; r < ROWS; r++)
        {
            for (int c = 0; c < COLS; c++)
            {
                Crop *crop = &crops[r][c];

                if (crop->health == MAX_HEALTH && crop->cropAlive == true)
                    crop->canHarvest = true;
            }
        }
    }

   

    //Night healing//
    if (currentState == NIGHT)
    {
        for (int r = 0; r < ROWS; r++)
        {
            for (int c = 0; c < COLS; c++)
            {
                Crop *crop = &crops[r][c];
                if (crop->isWatering && crop->cropAlive==true)
                {
                    crop->health = MAX_HEALTH;
                    crop->cropHP = 100;
                    crop->isWatering = false;
                   
                }
            }
        }
    }
    // water//
    if (tigrKeyDown(screen, 'E') && player->waterCount > 0)
    {
        for (int r = 0; r < ROWS; r++)
        {
            for (int c = 0; c < COLS; c++)
            {
                Crop *crop = &crops[r][c];
                if (abs(player->x - crop->x) < 50 && abs(player->y - crop->y) < 50)
                {
                    crop->isWatering = true;
                    player->waterCount--;
                }
            }
        }
    }

    //Harvest//
    if (tigrKeyDown(screen, 'H') && currentState==MORNING )
    {
        for (int r = 0; r < ROWS; r++)
        {
            for (int c = 0; c < COLS; c++)
            {
                Crop *crop = &crops[r][c];
                if (abs(player->x - crop->x) < 50 && abs(player->y - crop->y) < 50 && crop->canHarvest )
                {
                    player->balance += 5;
                    crop->health = 0;
                    crop->canHarvest = false;
                    crop->isWatering = false;
                }
            }
        }
    }
   

    // Draw crops
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            Crop *crop = &crops[r][c];
            if(crop->cropAlive==true){
            Tigr *sprite = crop->canHarvest ? spriteHarvest : spriteNoHarvest;
            tigrBlitAlpha(screen, sprite, crop->x, crop->y, 0, 0, sprite->w, sprite->h, 255);
            }
        }
    }
}
