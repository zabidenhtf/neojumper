/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#ifndef GAME_CONTROLS_H
#define GAME_CONTROLS_H

#include "interface.hpp"
#include "system.hpp"
#include "component.hpp"

class game_controls : public component
{
public:
    game_controls();
    virtual void reset();
    virtual void update(double tick);
    virtual void render();

    void draw_action_button(vec2 pos);

    double time;
    double step_time;
    double speed;
    int step;
private:
    int size;
    int distance = 35;
    bool press_time;
    bool can_press = true;
    bool combo;
    int combo_step;
};

#endif // GAME_CONTROLS_H
