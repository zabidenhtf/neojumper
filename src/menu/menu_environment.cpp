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
    Graphics->SetLight(vec3(3,3,3), vec3(0,0,0), vec4(1,1,1,1));
    Graphics->DrawSkybox();
    Graphics->EnableTexture(Data->GetTextureByID(NULL_TEX));
    Graphics->SetCamera(vec3(cam_pos_x-3,2,cam_pos_z), vec3(-3,0,0));
    Graphics->DrawPlane(vec3(0,0,0), vec2(5,5),vec4(1,0,0,1), 0,90,0);
}
