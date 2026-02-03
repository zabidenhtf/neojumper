/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#pragma once

#include "utils/system.hpp"

#include "component.hpp"

class GameHud : public Component{
public:
	GameHud();
	virtual void Reset(); // Lol, this just a render of score
	virtual void Update(float Tick);
	virtual void Render();
private:
	int TileWidth;
	int TileHeight;
	int Height;
};