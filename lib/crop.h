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
    int health;
    bool canHarvest;
    bool isWatering;
} Crop;
extern Crop crops[ROWS][COLS];


// One main function to handle all crop logic
void cropLogic(Player *player, Tigr *screen);
void initCrops();
#endif
