/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#pragma once

#include "utils/system.hpp"

#include "component.hpp"

class GameControls : public Component
{
public:
    GameControls();
    virtual void Reset();
    virtual void Update(float Tick);
    virtual void Render();

    float Time; // Global time after warmup
    float StepTime; // Step time
    float Speed; // Speed of buttons
    int Step; // Step now
private:
    int Size; // Size of action buttons
    int Distance = 35; // Gap between buttons
    bool PressTime;
    bool CanPress = true;
    bool Combo;
    int ComboStep;
};