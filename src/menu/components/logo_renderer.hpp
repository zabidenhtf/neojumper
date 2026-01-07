/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#ifndef MENU_LOGO_H
#define MENU_LOGO_H

#include "interface.hpp"
#include "system.hpp"
#include "includes.hpp"
#include "component.hpp"

class menu_logo : public component{
public:
    menu_logo();
    virtual void reset(){return;};
    virtual void update(double tick);
    virtual void render();
};

#endif // MENU_LOGO_H
