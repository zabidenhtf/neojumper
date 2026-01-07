/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "logo_renderer.hpp"
#include "data.hpp"

menu_logo::menu_logo(){
    write_dbg("MENU LOGO", "Menu logo initialisated");
}

void menu_logo::update(double tick){
    render();
}

void menu_logo::render(){
    int width = 300*gfx::screen_aspect();
    gfx::set_viewport(0,0,screen_width, screen_height);
    gfx::set_ortho(0,0, width,300);
    // Last commit in 2025 year
    float image_aspect = static_cast<double>(data2d::textures[LOGO].width) /  static_cast<double>(data2d::textures[LOGO].height);
    float i_height = 300/3;
    float i_width = i_height*image_aspect;

    gfx::enable_texture(data2d::textures[LOGO]);
    gfx::draw_2d_quad(vec2(8,15), vec2(i_width,i_height), vec4(1,1,1,1));
    gfx::disable_texture();
}
