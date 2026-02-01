/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#pragma once

#include "interface.hpp"
#include "system.hpp"
#include "component.hpp"

class game_message : public component{
public:
    game_message();
    void spawn(int txture);
    virtual void reset(){};
    virtual void update(double tick);
    virtual void render();
private:
    double time;
    int txture;
    bool active = false;
    double active_time;
};