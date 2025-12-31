#ifndef GAME_MESSAGE_H
#define GAME_MESSAGE_H

#include "interface.hpp"
#include "system.hpp"
#include "component.hpp"

class message : public component{
public:
    message();
    void spawn(int txture);
    virtual void reset(){};
    virtual void update(double tick);
    virtual void render();
private:
    double time;
    int txture;
    bool active = false;
    double active_time;
};

#endif // GAME_MESSAGE_H
