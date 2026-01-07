#ifndef GAME_CORE_H
#define GAME_CORE_H

#define WARMUP_TIME 4

// Components
#include "components/warmup.hpp"
#include "components/controls.hpp"
#include "components/message.hpp"

#include "interface.hpp"
#include "system.hpp"
#include "includes.hpp"


enum DANCE_MOVEMENTS{
KICK_LEFT_FORWARD,
KICK_RIGHT_FORWARD,
KICK_LEFT_BACKWARD,
KICK_RIGHT_BACKWARD,
STAND_LEFT,
STAND_RIGHT,
FLIP
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
    void reset();
    void update(double tick);
    bool game_started;
    dance_sequence now_dance;
    int score = 0;

    game_warmup *warmup;
    game_controls *controls;
    game_message *message;
};

extern game_core *game;

#endif // GAME_CORE_H
