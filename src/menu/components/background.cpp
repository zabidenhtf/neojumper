/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "background.hpp"
#include "data.hpp"
#include <cmath>

menu_background::menu_background(){
    write_dbg("MENU BACKGROUND", "Menu background initialisated");
    tile_width = Data->GetTextureByID(BACKGROUND_TILE).width;
    tile_height = Data->GetTextureByID(BACKGROUND_TILE).height;
}

void menu_background::update(double tick){
    render();
}

void menu_background::render(){
    gfx::set_viewport(0,0,ceil(screen_width/2.5), screen_height);
    gfx::set_ortho(0,0, ceil(screen_width/2.5),screen_height);
    // Border near the background (but it dont work and im dont understand why)
    gfx::enable_texture(Data->GetTextureByID(NULL_TEX));
    gfx::draw_2d_quad(vec2(8,0), vec2(screen_width/2.5, screen_height), vec4(0,0,0,1));
    gfx::disable_texture();
    // Background
    for (int y = 0; y < ceil(screen_height/tile_height) + 1; y++){
        for (int x = 0; x < ceil(screen_width/2.5/tile_width); x++){
            gfx::enable_texture(Data->GetTextureByID(BACKGROUND_TILE));
            gfx::draw_2d_quad(vec2(x*tile_width,y*tile_height), vec2(tile_width,tile_height), vec4(1,1,1,1));
            gfx::disable_texture();
        }
    }
}
