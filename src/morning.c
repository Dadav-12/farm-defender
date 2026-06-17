#include "../lib/tigr.h"
#include "morning.h"
#include<stdlib.h>

Tigr *grass = NULL;

void initMorningAssets()
{
    if (!grass)
    {
        grass = tigrLoadImage("assets/grassm.png"); // load once
    }
}
void drawMorning(Tigr *screen)
{
    initMorningAssets();

    // Draw the grass background full screen
    tigrBlit(screen, grass, 0, 0, 0, 0, grass->w, grass->h);

    
}
