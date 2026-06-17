#ifndef GAMESTATE_H
#define GAMESTATE_H
//define all the state//
typedef enum
{
    INTRO,
    INSTRUCTION,
    MORNING,
    NIGHT,
    WIN,
    LOSE
} Gamestate;

//global variable//
extern Gamestate currentState;

#endif