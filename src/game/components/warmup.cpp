/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "warmup.hpp"
//#include <iostream>
#include "data.hpp"
#include "graphics.hpp"

#include "../game.hpp"

game_warmup::game_warmup(){
    write_dbg("WARMUP","Timer initialisated");
}

void game_warmup::reset(){
    state = 4;
    time = 0;
    state_time = 0;
    active = true;
}

void game_warmup::update(double tick){
    if (active == true){
        time += tick;
        state_time += tick;
        //write_dbg("WARMUP","updating\n"); // Some debug stuff
        //std::cout << state_time;
        if (time > timer_time){
            active = false;
            write("Game started\n");
            game->game_started = true;
        }
        else if (state_time > timer_time/4){
            state-=1;
            state_time = 0;
        }
        render();
    }
}

void game_warmup::render(){
    int width = 300*Graphics->GetScreenAspect();
    Graphics->SetViewport(Graphics->GetWidth(), Graphics->GetHeight());
    Graphics->SetOrtho(width, 300);

    double digit_size = 150*state_time;

    switch (state){
    case 4:
        Graphics->EnableTexture(Data->GetTextureByID(DIGIT3));
        Graphics->DrawQuad(vec2(width/2-digit_size/2,150-digit_size/2),vec2(digit_size,digit_size), vec4(1,1,1,1));
        Graphics->DisableTexture();
        break;
    case 3:
        Graphics->EnableTexture(Data->GetTextureByID(DIGIT2));
        Graphics->DrawQuad(vec2(width/2-digit_size/2,150-digit_size/2),vec2(digit_size,digit_size), vec4(1,1,1,1));
        Graphics->DisableTexture();
        break;
    case 2:
        Graphics->EnableTexture(Data->GetTextureByID(DIGIT1));
        Graphics->DrawQuad(vec2(width/2-digit_size/2,150-digit_size/2),vec2(digit_size,digit_size), vec4(1,1,1,1));
        Graphics->DisableTexture();
        break;
    case 1:
        // Drawing more long quad than digit quad
        Graphics->EnableTexture(Data->GetTextureByID(MESSAGE_GO));
        Graphics->DrawQuad(vec2(width/2-digit_size,150-digit_size/2),vec2(digit_size*2,digit_size), vec4(1,1,1,1)); // fixed size
        Graphics->DisableTexture();
        break;
    }
}
