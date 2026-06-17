
#include "../lib/tigr.h"
#include "intro.h"
#include "gamestate.h"
#include "instruction.h"



int main()
{
    Tigr *screen = tigrWindow(1280, 720, "Farm Defender", 0);

    while (!tigrClosed(screen))
    {
        switch (currentState)
        {
        case INTRO:
            drawIntro(screen);
            break;
        case INSTRUCTION:
            drawInstruction(screen);
            break;
        }

        tigrUpdate(screen);
    }

    tigrFree(screen);
    return 0;
}
