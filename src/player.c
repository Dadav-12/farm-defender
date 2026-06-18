#include "player.h"
#include<stdio.h>

void initPlayer(Player *p, const char *spritePath)
{
    p->x = 500;
    p->y = 300;
    p->speed = 5;
    p->health = 100;
    p->damage = 10;
    p->sprite = tigrLoadImage(spritePath);
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

    // Keep inside farm fence
    if (p->x < 215)
        p->x = 215;
    if (p->x > 1060 - p->sprite->w)
        p->x = 1060 - p->sprite->w;
    if (p->y < 135)
        p->y = 135;
    if (p->y > 580 - p->sprite->h)
        p->y = 580 - p->sprite->h;
    if (p->y < 135 && !(p->x > 590 && p->x < 670))
    {
        p->y = 135;
    }
}

void drawPlayer(Player *p, Tigr *screen)
{
    tigrBlitAlpha(screen, p->sprite, p->x, p->y, 0, 0, p->sprite->w, p->sprite->h, 255);
}
