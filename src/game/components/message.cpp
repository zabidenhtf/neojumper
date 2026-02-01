/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "message.hpp"

#include "data.hpp"
#include "graphics.hpp"

game_message::game_message(){
    write_dbg("MESSAGE", "Message system initialisated");
}

void game_message::spawn(int txture){
    this->txture = txture;
    this->active = true;
    this->time = 0;
}

void game_message::update(double tick){
    if (active == true){
        time += tick;
        if (time > 1){
            active = false;
        }
        render();
    }
}

void game_message::render(){
    int width = 300*Graphics->GetScreenAspect();
    Graphics->SetViewport(Graphics->GetWidth(), Graphics->GetHeight());
    Graphics->SetOrtho(width, 300);

    // Small animation
    float m_height = 150*time;
    float m_width = m_height*2;

    Graphics->EnableTexture(Data->GetTextureByID(txture));
    Graphics->DrawQuad(vec2(width/2-m_width/2,150-m_height/2),vec2(m_width,m_height), vec4(1,1,1,1));
    Graphics->DisableTexture();
}
