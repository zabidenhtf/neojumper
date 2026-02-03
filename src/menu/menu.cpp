/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "menu.hpp"

MenuCore::MenuCore(){
    Console.WriteDebug("MENU", "Menu initialisated");
    Environment = new MenuEnvironment();
    Selector = new MenuSelector();
    Logo = new MenuLogo();
    Background = new MenuBackground();
    Copyright = new MenuCopyright();
}

void MenuCore::Update(float Tick){
    // Updating all stuff
    Environment->Update(Tick);
    Background->Update(Tick);
    Logo->Update(Tick);
    Selector->Update(Tick);
    Copyright->Update(Tick);
}
