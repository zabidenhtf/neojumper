/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "controls.hpp"

#include "utils/input.hpp"
#include "utils/data.hpp"
#include "utils/graphics.hpp"

#include "../game.hpp"

GameControls::GameControls(){
    Console.WriteDebug("CONTROLS","initialisated");
}

void GameControls::Reset(){
    Size = Graphics->GetHeight()/12;
    Time=0;
    StepTime=0;
    Speed = 0.5;
    Step = 0;
    ComboStep = 0;
    Combo = true;
}

void GameControls::Update(float Tick){
    if (Game->GameStarted == true){
        // Updating timers
        Time += Tick;
        StepTime += Tick;

        if (StepTime >= Speed){
            Step++;
            StepTime = 0;
            CanPress = true;
        }
        // Time to press key
        if (StepTime <= Size / ((Size+Distance)/Speed) && CanPress == true){
            //write("PRESS");
            PressTime = true;
        }
        else{
            PressTime = false;
        }
        // If time to press key
        if (PressTime == true){
            // If pressed CORRECT Button
            if (Input::LastButtonPressed() == DanceBinds[Game->NowDance.Movements[Step]]){
                //write("Pressed");
                if (Combo == true){
                    Game->Message->Add(MESSAGE_EXCELLENT);
                }
                // Adding score
                switch (Combo){
                    case true:
                        Game->AddScore(40);
                        break;
                    case false:
                        Game->AddScore(40);
                        break;
                }

                if (ComboStep == 5){
                    Combo = true;
                }
                else{
                    ComboStep ++;
                }
                PressTime = false;
                CanPress = false;
            }
            else{
                ComboStep = 0;
                Combo = false;
            }
        }

        if (Step >= Game->NowDance.MovementsCount){
            Game->GameStarted = false;
        }
        Render();
    }
}

void GameControls::Render(){
    float width = Graphics->GetWidth() / 1.5;
    float height = Graphics->GetHeight() / 1.5;
    Graphics->SetViewport(Graphics->GetWidth(), Graphics->GetHeight());
    Graphics->SetOrtho(width, height);
    // pretty line
    for (int i = 0; i<Graphics->GetWidth()/64; i++){
        Graphics->EnableTexture(Data->GetTextureByID(BUTTONS_LINE));
        Graphics->DrawQuad(vec2(i*64, height-Size/2-4), vec2(64, 8),vec4(1,1,1,1));
        Graphics->DisableTexture();
    }

    // Making many buttons of dance, and then animate it
    for (int i = 0; i < width/(Distance+Size)+1; i++){ // Optimisated
        if (i + Step < Game->NowDance.Movements.size()){
            switch (Game->NowDance.Movements[i+Step]){
                // Selecting texture
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
            // Drawing action button
            float x = i*(Size+Distance);
            float time_x = StepTime*(Size+Distance)/Speed;
            Graphics->DrawQuad(vec2(x - time_x + Size/2, height-Size), vec2(Size, Size),vec4(1,1,1,1));
            Graphics->DisableTexture();
        }
    }
    // helpfull arrow
    Graphics->EnableTexture(Data->GetTextureByID(BUTTON_ARROW));
    Graphics->DrawQuad(vec2(Size/8, height-Size), vec2(Size/4, Size/4),vec4(1,1,1,1));
    Graphics->DisableTexture();
}
