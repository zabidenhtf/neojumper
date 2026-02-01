/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#pragma once

#include "interface.hpp"
#include "system.hpp"
#include "component.hpp"

class game_warmup : public component
{
public:
    game_warmup();
    virtual void reset();
    virtual void update(double tick);
    virtual void render();
    double timer_time;
private:
    bool active = true;
    int state;
    double time;
    double state_time;
};