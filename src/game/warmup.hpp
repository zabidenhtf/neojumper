#ifndef GAME_WARMUP_H
#define GAME_WARMUP_H

#include "../interface.hpp"
#include "../system.hpp"
#include "component.hpp"

class warmup : public component
{
public:
    warmup();
    virtual void reset();
    virtual void update(double tick);
    virtual void render();
    bool active = true;
    double time = 0;
    double timer_time;
};

#endif // GAME_WARMUP_H
