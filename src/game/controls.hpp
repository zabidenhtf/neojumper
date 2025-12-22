#ifndef GAME_CONTROLS_H
#define GAME_CONTROLS_H

#include "../interface.hpp"
#include "../system.hpp"
#include "component.hpp"

class controls : public component
{
public:
    controls();
    virtual void reset(){return;};
    virtual void update(double tick);
    virtual void render();

    double time=0;
    double step_time=0;
    double speed = 0.5;
    int step = 0;
private:
    int size = screen_height/12;
    int distance = 35;
    bool press_time;
    bool can_press = true;
};

#endif // GAME_CONTROLS_H
