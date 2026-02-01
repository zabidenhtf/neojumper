/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#pragma once

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
    void draw_selection(vec2 pos, vec2 size, string text, vec4 color, bool selected, double tick);
    virtual void reset();
    virtual void update(double tick);
    virtual void render();
    void render_selections(double tick);
private:
    int width;
    int button_selector_max;
    int button_selector_min;
    int button_selected_now;
    float frame_width;
    float selection_height;
    float frame_height;
    vec2 frame_pos;
};