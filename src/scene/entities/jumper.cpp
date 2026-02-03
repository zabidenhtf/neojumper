/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "jumper.hpp"

#include "utils/data.hpp"

#include "../../game/game.hpp"

EntityJumper::EntityJumper(){
    Console.WriteDebug("JUMPER", "Added to scene");
}

void EntityJumper::Reset(){
    pos = vec3(0,0,0);
    direction = 45;
}

void EntityJumper::Update(float Tick){
    DANCE_MOVEMENTS MoveNow = Game->NowDance.Movements[Game->Controls->Step]; // Getting from game core movement now
    /*if (move_now == SHUFFLE_FORWARD){ // Check movement's now ON SOME TIME COMMENTED
        move_forward(tick, 3);
    }
    else if (move_now == SHUFFLE_BACKWARD){
        move_backward(tick, 2);
    }
    else if (move_now == FLIP){
        direction += randint(45,360);
    }
    else{
        // Do nothing
    }*/
    Render();
}

void EntityJumper::Render(){
    Graphics->DrawBox(pos+vec3(0,1,0), vec3(1,2,1), vec4(0.75,0.75,0.75,1));
}
