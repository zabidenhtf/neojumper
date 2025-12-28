#ifndef GAME_CORE_H
#define GAME_CORE_H

#define WARMUP_TIME 4

// Components
#include "warmup.hpp"
#include "controls.hpp"
#include "message.hpp"

#include "../interface.hpp"
#include "../system.hpp"
#include "../includes.hpp"


enum DANCE_MOVEMENTS{ // TODO: Make keyboard movement
JUMP,
KICK_LEFT,
KICK_RIGHT,
FLIP,
SHUFFLE_FORWARD,
SHUFFLE_BACKWARD
};

enum DANCE_LEVELS{
EASY=20,
NORMAL=50,
HARD=70
};

extern int dance_binds[]; //binds

struct dance_sequence{
vector<DANCE_MOVEMENTS> movements;
DANCE_LEVELS level;
double beat_speed = 1; // Speed of movements
};

// main core, there is all game content
class game_core{
public:
    dance_sequence generate_dance(DANCE_LEVELS level);
    game_core();
    void update(double tick);
    bool game_started = false;
    dance_sequence now_dance;
    int score = 0;

    warmup *warmup_component;
    controls *controls_component;
    message *message_component;
};

extern game_core *game;

#endif // GAME_CORE_H
