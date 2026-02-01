/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "hud.hpp"

#include "data.hpp"
#include "graphics.hpp"

#include "../game.hpp"

game_hud::game_hud(){
	write_dbg("GAME HUD", "Hud initialisated");
}

void game_hud::reset(){
	tile_width = Data->GetTextureByID(HUD_BAR_TILE).Width;
	tile_height = Data->GetTextureByID(HUD_BAR_TILE).Height;
	height = 2;
}

void game_hud::update(double tick){
	render();
}

void game_hud::render(){
    Graphics->SetViewport(Graphics->GetWidth(), Graphics->GetHeight());
    Graphics->SetOrtho(Graphics->GetWidth(), Graphics->GetHeight());

    // Drawing tiled bar at top
	Graphics->EnableTexture(Data->GetTextureByID(HUD_BAR_TILE));
	for (int y = 0; y<height; y++){
		for (int x = 0; x<Graphics->GetWidth()/tile_width; x++){
			Graphics->DrawQuad(vec2(x*tile_width,y*tile_height), vec2(tile_width, tile_height), vec4(1,1,1,1));
		}
	}	
	// Drawing score text
	string ScoreString = "Score:" + to_string(game->score);
	Graphics->DrawText(vec2(height/2,height/2), tile_height*height-(height*2), tile_height*height-(height*2), ScoreString, vec4(1,1,1,1));
}