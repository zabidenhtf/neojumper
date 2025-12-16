#ifndef GAME_WARMUP_H
#define GAME_WARMUP_H

#include "../interface.hpp"
#include "../system.hpp"

class warmup{
public:
    warmup();
    void reset();
    void update(double tick);
    void render();
    bool active = true;
    double time = 0;
    double timer_time;

    // TODO: move to data.hpp and data.cpp
    texture digit1;
    texture digit2;
    texture digit3;
    texture message_go;
};

#endif // GAME_WARMUP_H
