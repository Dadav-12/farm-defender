
#include "../lib/tigr.h"
#include "intro.h"
#include "gamestate.h"
#include "instruction.h"
#include "morning.h"
#include "player.h"
#include "night.h"

const float DAY_LENGTH = 10.0f;   // Morning lasts 60 seconds
const float NIGHT_LENGTH = 10.0f; // Night lasts 10 seconds (for testing)
float dayTimer = 0.0f;
int currentDay = 1;

int main()
{
    Tigr *screen = tigrWindow(1280, 720, "Farm Defender", 0);

    while (!tigrClosed(screen))
    {
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

            // Transition to Night
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

            // Transition back to Morning
            if (dayTimer >= NIGHT_LENGTH)
            {
                currentState = MORNING;
                dayTimer = 0.0f; // Reset timer
                currentDay++;    // Advance to the next day

                // Win Condition Check
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