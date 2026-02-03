/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#pragma once

#include "utils/system.hpp"

#include "component.hpp"

class GameMessage : public Component{
public:
    GameMessage();
    void Add(int Texture); // Spawning message on screen
    virtual void Reset(){};
    virtual void Update(float Tick);
    virtual void Render();
private:
    float Time;
    int Texture;
    bool Active = false;
    float ActiveTime;
};