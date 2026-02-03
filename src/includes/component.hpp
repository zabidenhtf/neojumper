/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#pragma once

class Component{
public:
    virtual void Reset() = 0;
    virtual void Update(float Tick) = 0;
    virtual void Render() = 0;
};
