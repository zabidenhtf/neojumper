/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#ifndef GAME_WARMUP_H
#define GAME_WARMUP_H

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
    bool active = true;
    int state;
    double time;
    double state_time;
    double timer_time;
};

#endif // GAME_WARMUP_H
