#include "../lib/tigr.h"
#include "store.h"
#include <stdbool.h>
#include "player.h"
Item hammer = {"hammer", 15};
Item water = {"water", 5};
bool openStore = 0;
void storeSystem(Tigr *screen, Player *player)
{
    // detect the press 'O'//
    if (tigrKeyDown(screen, 'O'))
    {
        openStore = !openStore;
    }

    if (openStore)
    {
        tigrRect(screen, 950, 200, 250, 150, tigrRGB(255, 255, 255));

        // menu//
        tigrPrint(screen, tfont, 960, 210, tigrRGB(255, 255, 0), "Store:");
        tigrPrint(screen, tfont, 960, 240, tigrRGB(255, 255, 0), "1. Buy Hammer (15 coins)");
        tigrPrint(screen, tfont, 960, 270, tigrRGB(255, 255, 0), "2. Buy Water (5 coins)");
        tigrPrint(screen, tfont, 960, 300, tigrRGB(255, 255, 0), "Press O to close");

        // Buy Hammer
        if (tigrKeyDown(screen, '1') && player->balance >= hammer.price)
        {
            player->balance -= hammer.price;
            player->hammerCount++;
        }

        // Buy Water
        if (tigrKeyDown(screen, '2') && player->balance >= water.price)
        {
            player->balance -= water.price;
            player->waterCount++;
        }
    }
}
