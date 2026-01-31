/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "menu_environment.hpp"
#include "data.hpp"

menu_environment::menu_environment(){
    write_dbg("MENU ENVIRONMENT", "Menu environment initialisated");
    reset();
}

void menu_environment::reset(){
    return;
}

void menu_environment::update(double tick){
    render();
}
void menu_environment::render(){
    gfx::set_light(vec3(3,3,3), vec3(0,0,0), vec4(1,1,1,1));
    gfx::draw_skybox();
    gfx::enable_texture(data::textures::textures[NULL_TEX]);
    gfx::set_camera(vec3(cam_pos_x-3,2,cam_pos_z), vec3(-3,0,0), fov);
    gfx::draw_3d_plane(vec3(0,0,0), vec2(5,5),vec4(1,0,0,1), 0,90,0);
}
