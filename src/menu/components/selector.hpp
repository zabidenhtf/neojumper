/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#pragma once

#include "utils/system.hpp"
#include "utils/graphics.hpp"

#include "includes.hpp"
#include "component.hpp"

extern bool GameEnabled;

enum{
    PLAY,
    CREDITS,
    SETTINGS,
    EXIT
};

class MenuSelector : public Component{
public:
    MenuSelector();
    void DrawSelection(vec2 pos, vec2 size, string text, vec4 color, bool selected, float Tick);
    virtual void Reset();
    virtual void Update(float Tick);
    virtual void Render();
    void RenderSelection(float Tick);
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