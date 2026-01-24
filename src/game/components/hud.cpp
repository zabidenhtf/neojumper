/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "hud.hpp"
#include "data.hpp"
#include "../game.hpp"

game_hud::game_hud(){
	write_dbg("GAME HUD", "Hud initialisated");
}

void game_hud::reset(){
	tile_width = data2d::textures[HUD_BAR_TILE].width;
	tile_height = data2d::textures[HUD_BAR_TILE].height;
	height = 2;
}

void game_hud::update(double tick){
	render();
}

void game_hud::render(){
    gfx::set_viewport(0,0,screen_width, screen_height);
    gfx::set_ortho(0,0, screen_width,screen_height);

    // Drawing tiled bar at top
	gfx::enable_texture(data2d::textures[HUD_BAR_TILE]);
	for (int y = 0; y<height; y++){
		for (int x = 0; x<screen_width/tile_width; x++){
			gfx::draw_2d_quad(vec2(x*tile_width,y*tile_height), vec2(tile_width, tile_height), vec4(1,1,1,1));
		}
	}	
	// Drawing score text
	string score_string = "Score:" + to_string(game->score);
	gfx::draw_2d_text(vec2(height/2,height/2), tile_height*height-(height*2), tile_height*height-(height*2), score_string, vec4(1,1,1,1));
}