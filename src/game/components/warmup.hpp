#ifndef GAME_WARMUP_H
#define GAME_WARMUP_H

#include "interface.hpp"
#include "system.hpp"
#include "component.hpp"

class game_warmup : public component
{
public:
    game_warmup();
    virtual void reset();
    virtual void update(double tick);
    virtual void render();
    bool active = true;
    int state = 4;
    double time = 0;
    double state_time = 0;
    double timer_time;
};

#endif // GAME_WARMUP_H
