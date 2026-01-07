/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
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
    void reset();
    void update(double tick);
    vec2 scene_size;
    vec2 scene_pos;
private:
    entity_jumper_player *player;
    scene_environment *environment;
};

extern scene_core* scene;

#endif // GAME_SCENE_H
