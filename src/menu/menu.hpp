/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#pragma once

#include "utils/system.hpp"

#include "includes.hpp"

#include "components/logo_renderer.hpp"
#include "components/background.hpp"
#include "components/selector.hpp"
#include "components/copyright.hpp"
#include "menu_environment.hpp"

enum MENU_STATES{
    MENU_MAIN,
    MENU_NEWGAME
};

class MenuCore{
public:
    MenuCore();
    void Update(float Tick);
    MENU_STATES state = MENU_MAIN;
    // Components
    MenuEnvironment *Environment;
    MenuSelector *Selector;
    MenuLogo *Logo;
    MenuBackground *Background;
    MenuCopyright *Copyright;
};

extern MenuCore* Menu; // Global pointer