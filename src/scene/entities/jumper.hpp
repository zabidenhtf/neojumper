#ifndef SCENE_JUMPER_H
#define SCENE_JUMPER_H

#include "interface.hpp"
#include "system.hpp"
#include "../entity.hpp"

class entity_jumper_player : public entity{
public:
    entity_jumper_player();
    virtual void reset();
    virtual void update(double tick);
    virtual void render();
private:
    void move_forward(double tick);
    void move_backward(double tick);
    vec3 pos;
    float direction;
};

#endif // SCENE_JUMPER_H
