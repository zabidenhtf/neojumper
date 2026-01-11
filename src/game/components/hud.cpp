/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "hud.hpp"
#include "../game.hpp"

game_hud::game_hud(){
	write_dbg("GAME HUD", "Hud initialisated");
}

void game_hud::update(double tick){
	render();
}

void game_hud::render(){
    gfx::set_viewport(0,0,screen_width, screen_height);
    gfx::set_ortho(0,0, screen_width,screen_height);
	// Just drawing text
	string score_string = "Score:" + to_string(game->score);
	gfx::draw_2d_text(vec2(0,0), 24, score_string, vec4(1,1,1,1));
}