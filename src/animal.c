#define FARM_LEFT 215
#define FARM_RIGHT 1100
#define FARM_TOP 135
#define FARM_BOTTOM 590
#define SPAWN_OFFSET 50

#include "../lib/animal.h"
#include "../lib/tigr.h"
#include "../lib/crop.h"
#include "../lib/gamestate.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

Animal animals[ANIMAL_MAX];
int animalCount = 0;

static Tigr *animalSprite = NULL;

// Helper: find first alive crop
Crop *findNextAliveCrop()
{
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            if (crops[r][c].cropHP > 0 && crops[r][c].cropAlive==1)
            {
                return &crops[r][c];
            }
        }
    }
    return NULL; // no crops left
}

void initAnimals()
{
    animalSprite = tigrLoadImage("assets/wolf.png");

    for (int i = 0; i < ANIMAL_MAX; i++)
    {
        animals[i].isAlive = false;
        animals[i].speed = 1.5f;
        animals[i].sprite = animalSprite;
        animals[i].target = NULL;
        animals[i].attackCooldown = 0;
    }
}

void spawnAnimals(int amount)
{
    if (amount > ANIMAL_MAX)
        amount = ANIMAL_MAX;

    animalCount = amount;

    for (int i = 0; i < ANIMAL_MAX; i++)
        animals[i].isAlive = false;

    for (int i = 0; i < animalCount; i++)
    {
        int side = rand() % 4;
        animals[i].isAlive = true;
        animals[i].health = 100;

        switch (side)
        {
        case 0:
            animals[i].x = FARM_LEFT + (rand() % (FARM_RIGHT - FARM_LEFT));
            animals[i].y = FARM_TOP - SPAWN_OFFSET;
            break;
        case 1:
            animals[i].x = FARM_LEFT + (rand() % (FARM_RIGHT - FARM_LEFT));
            animals[i].y = FARM_BOTTOM + SPAWN_OFFSET;
            break;
        case 2:
            animals[i].x = FARM_LEFT - SPAWN_OFFSET;
            animals[i].y = FARM_TOP + (rand() % (FARM_BOTTOM - FARM_TOP));
            break;
        case 3:
            animals[i].x = FARM_RIGHT + SPAWN_OFFSET;
            animals[i].y = FARM_TOP + (rand() % (FARM_BOTTOM - FARM_TOP));
            break;
        }

        // Assign a random crop target
        int row = rand() % ROWS;
        int col = rand() % COLS;
        animals[i].target = &crops[row][col];
        animals[i].attackCooldown = 0;
    }
}

void drawAnimals(Tigr *screen)
{
    for (int i = 0; i < animalCount; i++)
    {
        if (!animals[i].isAlive)
            continue;

        tigrBlitAlpha(
            screen,
            animals[i].sprite,
            animals[i].x,
            animals[i].y,
            0,
            0,
            animals[i].sprite->w,
            animals[i].sprite->h,
            255);
    }
}

void updateAnimals(Tigr* screen)
{
    for (int i = 0; i < animalCount; i++)
    {
        if (!animals[i].isAlive)
            continue;

        Animal *a = &animals[i];

        if (a->target == NULL)
            continue;

        // check colison with crops
        float dx = a->target->x - a->x;
        float dy = a->target->y - a->y;
        float dist = sqrtf(dx * dx + dy * dy);

        // checck colision with player
        float dxPlayer = player.x - a->x;
        float dyPlayer = player.y - a->y;
        float distToPlayer = sqrtf(dxPlayer * dxPlayer + dyPlayer * dyPlayer);

        // damage player if player is near with cooldown
        if (distToPlayer < 30)
        {
            if (a->attackCooldown <= 0)
            {
                player.health -= 5;     // damage player
                a->attackCooldown = 30; // wait 30 frames before next attack
            }
        }

        //player attack animals//
        if(tigrKeyDown(screen,'T')&&distToPlayer<=40 &&player.hammerCount>=1){
                a->health -= 10;
                if(a->health<=0){
                    a->isAlive = 0;
                }
            
        }
        
        // Movement
        if (dist > 10) // stop when close enough
        {
            a->x += (dx / dist) * a->speed;
            a->y += (dy / dist) * a->speed;
        }

        // Attack crop with cooldown
        if (dist < 10)
        {
            if (a->attackCooldown <= 0)
            {
                a->target->health -= 5; // damage crop
                a->target->cropHP -= 5;
                a->attackCooldown = 30; // wait 30 frames before next attack
            }
        }

        // Reduce cooldown each frame
        if (a->attackCooldown > 0)
            a->attackCooldown--;

        // Retarget if crop destroyed
        if (a->target->cropHP <= 0 && a->target->cropAlive==1)
        {
           
            a->target->cropAlive = false;
            a->target->cropHP = 0;
            a->target->health = 0;
            cropsMax--;
            a->target = findNextAliveCrop();
        }
    }
}
