/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#ifndef SCENE_ENTITY_H
#define SCENE_ENTITY_H

class entity{
public:
    virtual void reset() = 0;
    virtual void update(double tick) = 0;
    virtual void render() = 0;
};

#endif // SCENE_ENTITY_H
