/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "menu_environment.hpp"

#include "utils/data.hpp"
#include "utils/graphics.hpp"

MenuEnvironment::MenuEnvironment(){
    Console.WriteDebug("MENU ENVIRONMENT", "Menu environment initialisated");
    Reset();
}

void MenuEnvironment::Reset(){
    return;
}

void MenuEnvironment::Update(float Tick){
    Render();
}
void MenuEnvironment::Render(){
    Graphics->SetLight(vec3(3,3,3), vec3(0,0,0), vec4(1,1,1,1));
    Graphics->DrawSkybox();
    Graphics->EnableTexture(Data->GetTextureByID(NULL_TEX));
    Graphics->SetCamera(vec3(cam_pos_x-3,2,cam_pos_z), vec3(-3,0,0));
    Graphics->DrawPlane(vec3(0,0,0), vec2(5,5),vec4(1,0,0,1), 0,90,0);
}
