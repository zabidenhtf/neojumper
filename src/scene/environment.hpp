#ifndef SCENE_ENVIRONMENT_H
#define SCENE_ENVIRONMENT_H

#include "interface.hpp"
#include "system.hpp"
#include "component.hpp"

class environment : public component{
public:
    environment();
    virtual void reset();
    virtual void update(double tick);
    virtual void render();
private:
    // For light debug and render debug
    float cam_pos_x = 4;
    float cam_pos_z = 4;
};

#endif // SCENE_ENVIRONMENT_H
