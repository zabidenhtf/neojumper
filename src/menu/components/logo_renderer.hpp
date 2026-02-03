/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#pragma once

#include "utils/system.hpp"
#include "includes.hpp"
#include "component.hpp"

class MenuLogo : public Component{
public:
    MenuLogo();
    virtual void Reset(){return;};
    virtual void Update(float Tick);
    virtual void Render();
};