/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#pragma once

#include "utils/system.hpp"

#include "component.hpp"

class MenuEnvironment : public Component{
public:
    MenuEnvironment();
    virtual void Reset();
    virtual void Update(float Tick);
    virtual void Render();
private:
    // For light debug and render debug
    float cam_pos_x = 1;
    float cam_pos_z = 4;
};