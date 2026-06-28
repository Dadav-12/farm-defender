#include "gamestate.h"
#include "intro.h"
#include <stdlib.h>
#include <stdio.h>

void drawSceneryIntro(Tigr *screen)
{
    // Cloud 1
    tigrFillCircle(screen, 200, 100, 40, tigrRGB(255, 255, 255));
    tigrFillCircle(screen, 240, 100, 50, tigrRGB(255, 255, 255));
    tigrFillCircle(screen, 280, 100, 40, tigrRGB(255, 255, 255));

    // Cloud 2
    tigrFillCircle(screen, 500, 80, 25, tigrRGB(255, 255, 255));
    tigrFillCircle(screen, 530, 65, 35, tigrRGB(255, 255, 255));
    tigrFillCircle(screen, 560, 80, 25, tigrRGB(255, 255, 255));

    // Cloud 3
    tigrFillCircle(screen, 900, 140, 25, tigrRGB(255, 255, 255));
    tigrFillCircle(screen, 930, 125, 35, tigrRGB(255, 255, 255));
    tigrFillCircle(screen, 960, 140, 25, tigrRGB(255, 255, 255));

    // Sun and ground
    tigrFillCircle(screen, 1000, 100, 70, tigrRGB(255, 255, 0));
    tigrFill(screen, 0, 600, 1280, 200, tigrRGB(0, 180, 0));
}
typedef struct
{
    int x;
    int y;
    int w;
    int h;
} Button;
Button button = {500, 500, 250, 80};
void detectMouseClick(Tigr *screen)
{
    int mouseX;
    int mouseY;
    int buttons;

    tigrMouse(screen, &mouseX, &mouseY, &buttons);

    if (mouseX >= button.x &&
        mouseX <= button.x + button.w &&
        mouseY >= button.y &&
        mouseY <= button.y + button.h)
    {
        if (buttons & 1)
        {
            currentState = INSTRUCTION;
        }
    }
}

Tigr *Logo = NULL;

void asset()
{
    if (!Logo)
    {
        Logo = tigrLoadImage("assets/Logo.png");
    }
}

void drawStartbox(Tigr *screen)
{
    // draw box//
    tigrFill(screen, button.x, button.y, button.w, button.h, tigrRGB(255, 0, 0));

    if (Logo)
    {
        tigrBlitAlpha(screen, Logo, 320, 100, 0, 0, 600, 300, 255);
    }

    tigrPrint(screen, tfont, button.x + 90, button.y + 35, tigrRGB(255, 255, 255), "START GAME");
}

void drawIntro(Tigr *screen)
{
    asset();

    tigrClear(screen, tigrRGB(135, 206, 235));

    // draw box to recieve click//
    drawStartbox(screen);

    // 3.draw the cloud sky scenry//
    drawSceneryIntro(screen);

    // 4.detect the mouse click on gamestart and switch to next screen and update game state to 2//
    detectMouseClick(screen);
}
