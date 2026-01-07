/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#ifndef GAME_COMPONENT_H
#define GAME_COMPONENT_H

class component{
public:
    virtual void reset() = 0;
    virtual void update(double tick) = 0;
    virtual void render() = 0;
};

#endif // GAME_COMPONENT_H
