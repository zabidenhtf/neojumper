/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "message.hpp"

#include "utils/data.hpp"
#include "utils/graphics.hpp"

GameMessage::GameMessage(){
    Console.WriteDebug("MESSAGE", "Message system initialisated");
}

void GameMessage::Add(int Texture){
    this->Texture = Texture;
    this->Active = true;
    this->Time = 0;
}

void GameMessage::Update(float Tick){
    if (Active == true){
        Time += Tick;
        if (Time > 1){
            Active = false;
        }
        Render();
    }
}

void GameMessage::Render(){
    int Width = 300*Graphics->GetScreenAspect();
    Graphics->SetViewport(Graphics->GetWidth(), Graphics->GetHeight());
    Graphics->SetOrtho(Width, 300);

    // Small animation
    float m_height = 150*Time;
    float m_width = m_height*2;

    Graphics->EnableTexture(Data->GetTextureByID(Texture));
    Graphics->DrawQuad(vec2(Width/2-m_width/2,150-m_height/2),vec2(m_width,m_height), vec4(1,1,1,1));
    Graphics->DisableTexture();
}
