/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#ifndef MENU_SELECTOR_H
#define MENU_SELECTOR_H

#include "interface.hpp"
#include "system.hpp"
#include "includes.hpp"
#include "component.hpp"

extern bool game_enabled;

enum{
    PLAY,
    CREDITS,
    SETTINGS,
    EXIT
};

class menu_selector : public component{
public:
    menu_selector();
    void draw_button(vec2 pos, float height, int lenght, string text, vec4 color);
    virtual void reset();
    virtual void update(double tick);
    virtual void render();
private:
    int button_selector_max;
    int button_selector_min;
    int button_selected_now;
};
#endif
