#include "../lib/tigr.h"
#include "../lib/intro.h"
#include "../lib/gamestate.h"
#include "../lib/instruction.h"
#include "../lib/morning.h"
#include "../lib/player.h"
#include "../lib/night.h"
#include "../lib/crop.h"
#include "../lib/animal.h"
#include "../lib/fence.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// for testing can change DAY_LENGTH and NIGHT_LENGTH to just 10 seconds
const float DAY_LENGTH = 60.0f;   // Morning lasts 60 seconds or 1 minutes
const float NIGHT_LENGTH = 60.0f; // Night lasts 60 seconds or 1 minutes
float dayTimer = 0.0f;
int currentDay = 1;
bool animalsSpawned = false;

int main()
{
    srand(time(NULL));
    Tigr *screen = tigrWindow(1280, 801, "Farm Defender", 0);

    initCrops(); // calling the function to initialized the crops
    initAnimals();
    initFence();

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
            displayFenceHealth(screen);
            repairFence(screen, &player);
            cropLogic(&player, screen);

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
            displayFenceHealth(screen);
            cropLogic(&player, screen);
            if (!animalsSpawned)
            {
                spawnAnimals(currentDay * 2 + 1);
                animalsSpawned = true;
            }

            drawAnimals(screen);
            updateAnimals(screen);

            // Run the timer for the night phase
            dayTimer += dt;
            tigrPrint(screen, tfont, 600, 20, tigrRGB(255, 255, 255), "Time to Morning: %.1f", NIGHT_LENGTH - dayTimer);
            tigrPrint(screen, tfont, 600, 40, tigrRGB(255, 255, 255), "Day: %d / 5", currentDay);

            // check winning condition
            if (currentDay > 5)
            {
                currentState = WIN;
            }
            if (player.health <= 0 || cropsMax <= 0)
            {
                currentState = LOSE;
                break;
            }

            // switch back to Morning
            if (dayTimer >= NIGHT_LENGTH)
            {
                currentState = MORNING;
                dayTimer = 0.0f; // Reset timer
                currentDay++;    // Advance to the next day
                animalCount = 0;
                animalsSpawned = false;
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