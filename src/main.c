#include "../lib/tigr.h"
#include "intro.h"
#include "gamestate.h"
#include "instruction.h"
#include "morning.h"
#include "player.h"
#include "night.h"
#include "crop.h"

// for testing can change DAY_LENGTH and NIGHT_LENGTH to just 10 seconds
const float DAY_LENGTH = 180.0f;  // Morning lasts 180 seconds or 3 minutes
const float NIGHT_LENGTH = 60.0f; // Night lasts 60 seconds or 1 minutes
float dayTimer = 0.0f;
int currentDay = 1;

// Data base for the crops
const CropData crop_configs[] = {
    [CROP_WHEAT] = {100.0f, 20},
    [CROP_TOMATO] = {100.0f, 50},
    [CROP_CORN] = {100.0f, 35},
    [CROP_BERRY] = {100.0f, 80}};

int main()
{
    Tigr *screen = tigrWindow(1280, 801, "Farm Defender", 0);

    // calling the function to initialized the crops
    crop_configs;

    while (!tigrClosed(screen))
    {
        // tigerTime() from TIGR library remove the need for time.h
        float dt = tigrTime();

        switch (currentState)
        {
        case INTRO:
            drawIntro(screen);
            break;
        case INSTRUCTION:
            drawInstruction(screen);
            break;
        case MORNING:
            drawMorning(screen);

            // Increment our timer by the delta time
            dayTimer += dt;

            // Draw the timer and day counter on screen
            tigrPrint(screen, tfont, 600, 20, tigrRGB(255, 255, 255), "Time to Night: %.1f", DAY_LENGTH - dayTimer);
            tigrPrint(screen, tfont, 600, 40, tigrRGB(255, 255, 255), "Day: %d / 5", currentDay);

            // switch to Night
            if (dayTimer >= DAY_LENGTH)
            {
                currentState = NIGHT;
                dayTimer = 0.0f; // Reset timer for the night cycle
            }
            break;
        case NIGHT:
            drawNight(screen);

            // Run the timer for the night phase
            dayTimer += dt;
            tigrPrint(screen, tfont, 600, 20, tigrRGB(255, 255, 255), "Time to Morning: %.1f", NIGHT_LENGTH - dayTimer);
            tigrPrint(screen, tfont, 600, 40, tigrRGB(255, 255, 255), "Day: %d / 5", currentDay);

            // switch back to Morning
            if (dayTimer >= NIGHT_LENGTH)
            {
                currentState = MORNING;
                dayTimer = 0.0f; // Reset timer
                currentDay++;    // Advance to the next day

                // check winning condition
                if (currentDay > 5)
                {
                    currentState = WIN;
                }
            }
            break;

        case WIN:
            tigrClear(screen, tigrRGB(0, 0, 0));
            tigrPrint(screen, tfont, 550, 360, tigrRGB(0, 255, 0), "YOU SURVIVED 5 NIGHTS!");
            break;

        case LOSE:
            tigrClear(screen, tigrRGB(0, 0, 0));
            tigrPrint(screen, tfont, 550, 360, tigrRGB(255, 0, 0), "YOU DIED.");
            break;
        }
        if (currentState == MORNING || currentState == NIGHT)
        {
            displayPlayerState(&player, screen);
        }
        tigrUpdate(screen);
    }

    tigrFree(screen);
    return 0;
}