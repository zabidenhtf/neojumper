#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "interface.hpp"
#include "system.hpp"
#include "includes.hpp"

// entities
#include "entities/jumper.hpp"

// components
#include "environment.hpp"

class scene_core{ // There is all 3D objects
public:
    scene_core();
    void reset(){return;};
    void update(double tick);
    vec2 scene_size;
    vec2 scene_pos;
private:
    jumper_player *player;
    environment *environment_component;
};

extern scene_core* scene;

#endif // GAME_SCENE_H
