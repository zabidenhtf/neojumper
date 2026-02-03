/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */

#pragma once

#include "utils/system.hpp"
#include "utils/graphics.hpp"

#include "../entity.hpp"

class EntityJumper : public Entity{
public:
    EntityJumper();
    virtual void Reset();
    virtual void Update(float Tick);
    virtual void Render();
private:
    vec3 pos; // Position of jumper
    float direction; // Direction of jumper
};