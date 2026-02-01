/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#pragma once

#include "interface.hpp"
#include "system.hpp"
#include "component.hpp"

class menu_environment : public component{
public:
    menu_environment();
    virtual void reset();
    virtual void update(double tick);
    virtual void render();
private:
    // For light debug and render debug
    float cam_pos_x = 1;
    float cam_pos_z = 4;
};