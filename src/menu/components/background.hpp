/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#ifndef MENU_BACKGROUND_H
#define MENU_BACKGROUND_H

#include "interface.hpp"
#include "system.hpp"
#include "includes.hpp"
#include "component.hpp"

class menu_background : public component{
public:
    menu_background();
    virtual void reset(){return;};
    virtual void update(double tick);
    virtual void render();
private:
    int tile_width;
    int tile_height;
};

#endif // MENU_BACKGROUND_H
