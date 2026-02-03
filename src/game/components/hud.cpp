/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "hud.hpp"

#include "utils/data.hpp"
#include "utils/graphics.hpp"

#include "../game.hpp"

GameHud::GameHud(){
	Console.WriteDebug("GAME HUD", "Hud initialisated");
}

void GameHud::Reset(){
	TileWidth = Data->GetTextureByID(HUD_BAR_TILE).Width;
	TileHeight = Data->GetTextureByID(HUD_BAR_TILE).Height;
	Height = 2;
}

void GameHud::Update(float Tick){
	Render();
}

void GameHud::Render(){
    Graphics->SetViewport(Graphics->GetWidth(), Graphics->GetHeight());
    Graphics->SetOrtho(Graphics->GetWidth(), Graphics->GetHeight());

    // Drawing tiled bar at top
	Graphics->EnableTexture(Data->GetTextureByID(HUD_BAR_TILE));
	for (int y = 0; y<Height; y++){
		for (int x = 0; x<Graphics->GetWidth()/TileWidth; x++){
			Graphics->DrawQuad(vec2(x*TileWidth,y*TileHeight), vec2(TileWidth, TileHeight), vec4(1,1,1,1));
		}
	}	
	// Drawing score text
	string ScoreString = "Score:" + to_string(Game->GetScore());
	Graphics->DrawText(vec2(Height/2,Height/2), TileHeight*Height-(Height*2), TileHeight*Height-(Height*2), ScoreString, vec4(1,1,1,1));
}