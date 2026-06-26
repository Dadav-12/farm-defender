#include "player.h"
#include<stdbool.h>
Player player;
bool isOutsideFarm = 0;
void initPlayer(Player *p, const char *spritePath)
{
    p->x = 500;
    p->y = 300;
    p->speed = 5;
    p->health = 100;
    p->damage = 10;
    p->sprite = tigrLoadImage(spritePath);

    p->balance = 20;
    p->hammerCount = 0;
    p->waterCount = 0;
}

void movePlayer(Player *p, Tigr *screen)
{
    if (tigrKeyHeld(screen, 'W'))
        p->y -= p->speed;

    if (tigrKeyHeld(screen, 'S'))
        p->y += p->speed;

    if (tigrKeyHeld(screen, 'A'))
        p->x -= p->speed;
    if (tigrKeyHeld(screen, 'D'))
        p->x += p->speed;

    // Detect crossing gate
    if (p->y < 135 && p->x > 590 && p->x < 670)
        isOutsideFarm = 1; 
    if (p->y >= 135 && p->x > 590 && p->x < 670)
        isOutsideFarm = 0; 

    // Keep inside farm fence
    if (p->x < 215)
        p->x = 215;
    if (p->x > 1100 - p->sprite->w)
        p->x = 1100 - p->sprite->w;
    if (p->y < 135)
        p->y = 135;
    if (p->y > 590 - p->sprite->h)
        p->y = 590 - p->sprite->h;
    if (p->y < 135 && !(p->x > 590 && p->x < 670))
    {
        p->y = 135;
    }
}

void drawPlayer(Player *p, Tigr *screen)
{
    tigrBlitAlpha(screen, p->sprite, p->x, p->y, 0, 0, p->sprite->w, p->sprite->h, 255);
}

void displayPlayerState(Player *p, Tigr *screen)
{
    // Draw inventory box
    tigrFillRect(screen, 20, 20, 150, 60, tigrRGB(0, 0, 128)); // dark blue box
    tigrPrint(screen, tfont, 30, 30, tigrRGB(255, 255, 255), "hammer %d", p->hammerCount);
    tigrPrint(screen, tfont, 30, 50, tigrRGB(255, 255, 255), "water %d", p->waterCount);

    // Draw HP box
    tigrFillRect(screen, 20, 100, 150, 40, tigrRGB(128, 0, 0)); // dark red box
    tigrPrint(screen, tfont, 30, 110, tigrRGB(255, 255, 255), "hp = %d", p->health);
    tigrFillRect(screen, 20, 150, 150, 40, tigrRGB(0, 128, 0));
    tigrPrint(screen, tfont, 30, 160, tigrRGB(255, 255, 255), "balance = %d", p->balance);
}