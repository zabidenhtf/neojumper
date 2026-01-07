/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#ifndef SCENE_ENVIRONMENT_H
#define SCENE_ENVIRONMENT_H

#include "interface.hpp"
#include "system.hpp"
#include "component.hpp"

class scene_environment : public component{
public:
    scene_environment();
    virtual void reset();
    virtual void update(double tick);
    virtual void render();
private:
    // For light debug and render debug
    float cam_pos_x;
    float cam_pos_z;
};

#endif // SCENE_ENVIRONMENT_H
