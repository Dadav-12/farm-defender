
#include "../lib/tigr.h"
#include "intro.h"
#include "gamestate.h"



int main()
{
    Gamestate currentState = INTRO;
    Tigr *screen = tigrWindow(1280, 720, "Farm Defender", 0);

    while (!tigrClosed(screen))
    {
        if(currentState==INTRO){
        drawIntro(screen);
        }
        tigrUpdate(screen);
    }

    tigrFree(screen);
    return 0;
}
