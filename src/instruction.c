#include "../lib/tigr.h"
#include "gamestate.h"
#include "instruction.h"

// Draw the instruction screen
void instruction(Tigr *screen)
{
    tigrClear(screen, tigrRGB(0, 0, 0));
    tigrPrint(screen, tfont, 500, 100, tigrRGB(255, 255, 255), "FARM DEFENDER");
    tigrPrint(screen, tfont, 300, 200, tigrRGB(255, 255, 255), "CONTROLS:");
    tigrPrint(screen, tfont, 300, 250, tigrRGB(255, 255, 255), "W - MOVE UP");
    tigrPrint(screen, tfont, 300, 280, tigrRGB(255, 255, 255), "S - MOVE DOWN");
    tigrPrint(screen, tfont, 300, 310, tigrRGB(255, 255, 255), "A - MOVE LEFT");
    tigrPrint(screen, tfont, 300, 340, tigrRGB(255, 255, 255), "D - MOVE RIGHT");
    tigrPrint(screen, tfont, 300, 420, tigrRGB(255, 255, 255), "PROTECT YOUR CROPS");
    tigrPrint(screen, tfont, 300, 450, tigrRGB(255, 255, 255), "SURVIVE 5 NIGHTS");
    tigrPrint(screen, tfont, 300, 550, tigrRGB(255, 255, 0), "PRESS ENTER TO START");
}

// Check if Enter is pressed
void checkEnter(Tigr *screen)
{
    if (tigrKeyDown(screen, TK_RETURN))
    {
        currentState = MORNING; // switch to morning scene
    }
}

// Draw instruction screen and handle input
void drawInstruction(Tigr *screen)
{
    instruction(screen);
    checkEnter(screen);
}
