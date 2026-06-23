#ifndef STORE_H
#define STORE_H

#include <stdbool.h>
#include "../lib/tigr.h"
#include "player.h"
typedef struct
{
    char *name;
    int price;
} Item;

void storeSystem(Tigr *screen, Player *player); // handle transaction, return updated balance

#endif
