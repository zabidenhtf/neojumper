/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#pragma once

#include "utils/system.hpp"

#include "component.hpp"

class GameWarmup : public Component
{
public:
    GameWarmup();
    virtual void Reset();
    virtual void Update(float Tick);
    virtual void Render();
    float WarmupTime;
private:
    bool Active = true;
    int State;
    float Time; // Time global
    float StateTime;
};