/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "controls.hpp"

#include "data.hpp"
#include "graphics.hpp"

#include "../game.hpp"

game_controls::game_controls(){
    write_dbg("CONTROLS","initialisated");
}

void game_controls::reset(){
    size = Graphics->GetHeight()/12;
    time=0;
    step_time=0;
    speed = 0.5;
    step = 0;
    combo_step = 0;
    combo = true;
}

void game_controls::update(double tick){
    if (game->game_started == true){
        time += tick;
        step_time += tick;

        if (step_time >= speed){
            step++;
            step_time = 0;
            can_press = true;
        }
        // Time to press key
        if (step_time <= size / ((size+distance)/speed) && can_press == true){
            //write("PRESS");
            press_time = true;
        }
        else{
            press_time = false;
        }
        if (press_time == true){
            if (!key_buffer.empty()){
                if (key_buffer.back() == dance_binds[game->now_dance.movements[step]]){
                    //write("Pressed");
                    if (combo == true){
                        game->message->spawn(MESSAGE_EXCELLENT);
                    }
                    switch (combo){
                        case true:
                            game->score += 40;
                            break;
                        case false:
                            game->score += 20;
                            break;
                    }

                    if (combo_step == 5){
                        combo = true;
                    }
                    else{
                        combo_step ++;
                    }
                    press_time = false;
                    can_press = false;
                }
                else{
                    combo_step = 0;
                    combo = false;
                }
            }
        }

        if (step >= game->now_dance.movements_count){
            game->game_started = false;
        }
        render();
    }
}

void game_controls::render(){
    float width = Graphics->GetWidth() / 1.5;
    float height = Graphics->GetHeight() / 1.5;
    Graphics->SetViewport(Graphics->GetWidth(), Graphics->GetHeight());
    Graphics->SetOrtho(width, height);
    // pretty line
    for (int i = 0; i<Graphics->GetWidth()/64; i++){
        Graphics->EnableTexture(Data->GetTextureByID(BUTTONS_LINE));
        Graphics->DrawQuad(vec2(i*64, height-size/2-4), vec2(64, 8),vec4(1,1,1,1));
        Graphics->DisableTexture();
    }

    // Making many buttons of dance, and then animate it
    for (int i = 0; i < width/(distance+size)+1; i++){ // Optimisated
        if (i + step < game->now_dance.movements.size()){
            switch (game->now_dance.movements[i+step]){
                case KICK_LEFT_FORWARD:
                    Graphics->EnableTexture(Data->GetTextureByID(ACTION_KICK_LEFT_FORWARD));
                    break;
                case KICK_RIGHT_FORWARD:
                    Graphics->EnableTexture(Data->GetTextureByID(ACTION_KICK_RIGHT_FORWARD));
                    break;
                case KICK_LEFT_BACKWARD:
                    Graphics->EnableTexture(Data->GetTextureByID(ACTION_KICK_LEFT_BACKWARD));
                    break;
                case KICK_RIGHT_BACKWARD:
                    Graphics->EnableTexture(Data->GetTextureByID(ACTION_KICK_RIGHT_BACKWARD));
                    break;
                case STAND_LEFT:
                    Graphics->EnableTexture(Data->GetTextureByID(ACTION_STAND_LEFT));
                    break;
                case STAND_RIGHT:
                    Graphics->EnableTexture(Data->GetTextureByID(ACTION_STAND_RIGHT));
                    break;
                case FLIP:
                    Graphics->EnableTexture(Data->GetTextureByID(ACTION_FLIP));
                    break;
            }
            float x = i*(size+distance);
            float time_x = step_time*(size+distance)/speed;
            Graphics->DrawQuad(vec2(x - time_x + size/2, height-size), vec2(size, size),vec4(1,1,1,1));
            Graphics->DisableTexture();
        }
    }
    // helpfull arrow
    Graphics->EnableTexture(Data->GetTextureByID(BUTTON_ARROW));
    Graphics->DrawQuad(vec2(size/8, height-size), vec2(size/4, size/4),vec4(1,1,1,1));
    Graphics->DisableTexture();
}
