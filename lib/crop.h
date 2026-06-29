#ifndef CROP_H
#define CROP_H

#include "../lib/tigr.h"
#include <stdbool.h>
#include "../lib/player.h"
#define ROWS 3
#define COLS 3
#define MAX_HEALTH 100

typedef struct
{
    int x, y;
    int health;//chek harvest or not//
    int cropHP;//check attack from wolf//
    bool canHarvest;
    bool isWatering;
    bool cropAlive;
} Crop;
extern Crop crops[ROWS][COLS];
extern int cropsMax;

// One main function to handle all crop logic
void cropLogic(Player *player, Tigr *screen);
void initCrops();
#endif
