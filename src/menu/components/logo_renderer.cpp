/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "logo_renderer.hpp"

#include "utils/data.hpp"
#include "utils/graphics.hpp"

MenuLogo::MenuLogo(){
    Console.WriteDebug("MENU LOGO", "Menu logo initialisated");
}

void MenuLogo::Update(float Tick){
    Render();
}

void MenuLogo::Render(){
    int width = 300*Graphics->GetScreenAspect();
    Graphics->SetViewport(Graphics->GetWidth(), Graphics->GetHeight());
    Graphics->SetOrtho(width, 300);
    // Last commit in 2025 year
    float image_aspect = static_cast<double>(Data->GetTextureByID(LOGO).Width) /  static_cast<double>(Data->GetTextureByID(LOGO).Height);
    float i_height = 300/3;
    float i_width = i_height*image_aspect;

    Graphics->EnableTexture(Data->GetTextureByID(LOGO));
    Graphics->DrawQuad(vec2(8,15), vec2(i_width,i_height), vec4(1,1,1,1));
    Graphics->DisableTexture();
}
