#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "../interface.hpp"
#include "../system.hpp"
#include "../includes.hpp"
#include "../game/component.hpp"

class scene : public component{ // There is all 3D objects
public:
    scene();
    virtual void reset(){return;};
    virtual void update(double tick);
    virtual void render();

    // For light debug and render debug
    float cam_pos_x = 0;
    float cam_pos_z = 0;
};

#endif // GAME_SCENE_H
