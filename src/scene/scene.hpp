/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#pragma once

#include "utils/system.hpp"

#include "includes.hpp"

// entities
#include "entities/jumper.hpp"

// components
#include "environment.hpp"

class SceneCore{ // There is all 3D objects
public:
    SceneCore();
    void Reset();
    void Update(float Tick);
    // Scene params
    vec2 SceneSize;
    vec2 ScenePosition;
private:
    EntityJumper *Player;
    SceneEnvironment *Environment;
};

extern SceneCore* Scene;