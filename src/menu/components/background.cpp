/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "background.hpp"

#include "utils/data.hpp"
#include "utils/graphics.hpp"

#include <cmath>

MenuBackground::MenuBackground(){
    Console.WriteDebug("MENU BACKGROUND", "Menu background initialisated");
    TileWidth = Data->GetTextureByID(BACKGROUND_TILE).Width;
    TileHeight = Data->GetTextureByID(BACKGROUND_TILE).Height;
}

void MenuBackground::Update(float Tick){
    Render();
}

void MenuBackground::Render(){
    Graphics->SetViewport(ceil(Graphics->GetWidth()/2.5), Graphics->GetHeight());
    Graphics->SetOrtho(ceil(Graphics->GetWidth()/2.5),Graphics->GetHeight());
    // Border near the background (but it dont work and im dont understand why)
    Graphics->EnableTexture(Data->GetTextureByID(NULL_TEX));
    Graphics->DrawQuad(vec2(8,0), vec2(Graphics->GetWidth()/2.5, Graphics->GetHeight()), vec4(0,0,0,1));
    Graphics->DisableTexture();
    // Background
    for (int y = 0; y < ceil(Graphics->GetHeight()/TileHeight) + 1; y++){
        for (int x = 0; x < ceil(Graphics->GetWidth()/2.5/TileWidth); x++){
            Graphics->EnableTexture(Data->GetTextureByID(BACKGROUND_TILE));
            Graphics->DrawQuad(vec2(x*TileWidth,y*TileHeight), vec2(TileWidth,TileHeight), vec4(1,1,1,1));
            Graphics->DisableTexture();
        }
    }
}
