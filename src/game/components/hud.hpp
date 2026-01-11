/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#ifndef GAME_HUD_H
#define GAME_HUD_H

#include "interface.hpp"
#include "system.hpp"
#include "component.hpp"

class game_hud : public component{
public:
	game_hud();
	virtual void reset(){return;}; // Lol, this just a render of score
	virtual void update(double tick);
	virtual void render();
};

#endif