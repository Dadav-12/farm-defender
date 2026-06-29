#ifndef ANIMAL_H
#define ANIMAL_H

#include "../lib/gamestate.h"
#include "../lib/player.h"
#include "../lib/crop.h"
#include "../lib/Tigr.h"

#define ANIMAL_MAX 10

typedef struct
{
    float x, y;

    bool isAlive;

    int health;
    float speed;

    Crop *target;

    Tigr *sprite;
    int attackCooldown;

} Animal;

extern Animal animal[ANIMAL_MAX];
extern int animalCount;

void initAnimals();
void spawnAnimals(int amount);
void drawAnimals(Tigr* screen);
void updateAnimals(Tigr* screen);

#endif