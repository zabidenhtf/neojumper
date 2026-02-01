/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "background.hpp"

#include "data.hpp"
#include "graphics.hpp"

#include <cmath>

menu_background::menu_background(){
    write_dbg("MENU BACKGROUND", "Menu background initialisated");
    tile_width = Data->GetTextureByID(BACKGROUND_TILE).Width;
    tile_height = Data->GetTextureByID(BACKGROUND_TILE).Height;
}

void menu_background::update(double tick){
    render();
}

void menu_background::render(){
    Graphics->SetViewport(ceil(Graphics->GetWidth()/2.5), Graphics->GetHeight());
    Graphics->SetOrtho(ceil(Graphics->GetWidth()/2.5),Graphics->GetHeight());
    // Border near the background (but it dont work and im dont understand why)
    Graphics->EnableTexture(Data->GetTextureByID(NULL_TEX));
    Graphics->DrawQuad(vec2(8,0), vec2(Graphics->GetWidth()/2.5, Graphics->GetHeight()), vec4(0,0,0,1));
    Graphics->DisableTexture();
    // Background
    for (int y = 0; y < ceil(Graphics->GetHeight()/tile_height) + 1; y++){
        for (int x = 0; x < ceil(Graphics->GetWidth()/2.5/tile_width); x++){
            Graphics->EnableTexture(Data->GetTextureByID(BACKGROUND_TILE));
            Graphics->DrawQuad(vec2(x*tile_width,y*tile_height), vec2(tile_width,tile_height), vec4(1,1,1,1));
            Graphics->DisableTexture();
        }
    }
}
