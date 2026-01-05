#ifndef GAME_MENU_H
#define GAME_MENU_H

#include "interface.hpp"
#include "system.hpp"
#include "includes.hpp"

#include "components/logo_renderer.hpp"
#include "components/background.hpp"
#include "components/selector.hpp"
#include "menu_environment.hpp"

enum MENU_STATES{
    MENU_MAIN,
    MENU_NEWGAME
};

class menu_core{
public:
    menu_core();
    void update(double tick);
    MENU_STATES state = MENU_MAIN;
    menu_environment *environment;
    menu_selector *selector;
    menu_logo *logo;
    menu_background *background;
};

extern menu_core* menu;

#endif // GAME_MENU_H
