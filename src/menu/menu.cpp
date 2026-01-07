/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "menu.hpp"

menu_core::menu_core(){
    write_dbg("MENU", "Menu initialisated");
    environment = new menu_environment();
    selector = new menu_selector();
    logo = new menu_logo();
    background = new menu_background();
}

void menu_core::update(double tick){
    // Updating all stuff
    environment->update(tick);
    background->update(tick);
    logo->update(tick);
    selector->update(tick);
}
