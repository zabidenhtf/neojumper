/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "warmup.hpp"
//#include <iostream>

#include "utils/data.hpp"
#include "utils/graphics.hpp"

#include "../game.hpp"

GameWarmup::GameWarmup(){
    Console.WriteDebug("WARMUP","Timer initialisated");
}

void GameWarmup::Reset(){
    State = 4;
    Time = 0;
    StateTime = 0;
    Active = true;
}

void GameWarmup::Update(float Tick){
    if (Active == true){
        Time += Tick;
        StateTime += Tick;
        //write_dbg("WARMUP","updating\n"); // Some debug stuff
        //std::cout << state_time;
        // If global time bigger than warmup time starting game
        if (Time > WarmupTime){
            Active = false;
            Console.Write("Game started\n");
            Game->GameStarted = true;
        }
        else if (StateTime > WarmupTime/4){
            State-=1;
            StateTime = 0;
        }
        Render();
    }
}

void GameWarmup::Render(){
    int width = 300*Graphics->GetScreenAspect();
    Graphics->SetViewport(Graphics->GetWidth(), Graphics->GetHeight());
    Graphics->SetOrtho(width, 300);

    float DigitSize = 150*StateTime;

    switch (State){
    case 4:
        Graphics->EnableTexture(Data->GetTextureByID(DIGIT3));
        Graphics->DrawQuad(vec2(width/2-DigitSize/2,150-DigitSize/2),vec2(DigitSize,DigitSize), vec4(1,1,1,1));
        Graphics->DisableTexture();
        break;
    case 3:
        Graphics->EnableTexture(Data->GetTextureByID(DIGIT2));
        Graphics->DrawQuad(vec2(width/2-DigitSize/2,150-DigitSize/2),vec2(DigitSize,DigitSize), vec4(1,1,1,1));
        Graphics->DisableTexture();
        break;
    case 2:
        Graphics->EnableTexture(Data->GetTextureByID(DIGIT1));
        Graphics->DrawQuad(vec2(width/2-DigitSize/2,150-DigitSize/2),vec2(DigitSize,DigitSize), vec4(1,1,1,1));
        Graphics->DisableTexture();
        break;
    case 1:
        // Drawing more long quad than digit quad
        Graphics->EnableTexture(Data->GetTextureByID(MESSAGE_GO));
        Graphics->DrawQuad(vec2(width/2-DigitSize,150-DigitSize/2),vec2(DigitSize*2,DigitSize), vec4(1,1,1,1)); // fixed size
        Graphics->DisableTexture();
        break;
    }
}
