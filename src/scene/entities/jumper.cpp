/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "jumper.hpp"
#include "../../game/game.hpp"

entity_jumper_player::entity_jumper_player(){
    write_dbg("JUMPER", "Added to scene");
}

void entity_jumper_player::reset(){
    pos = vec3(0,0,0);
    direction = 45;
}

void entity_jumper_player::move_forward(double tick, double speed){
    pos += vec3(cos(direction)*tick*speed,0,sin(direction)*tick*speed);
}

void entity_jumper_player::move_backward(double tick, double speed){
    pos += vec3(cos(direction)*-tick*speed,0,sin(direction)*-tick*speed);
}

void entity_jumper_player::update(double tick){
    DANCE_MOVEMENTS move_now = game->now_dance.movements[game->controls->step];
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
    render();
}

void entity_jumper_player::render(){
    gfx::draw_3d_box(pos+vec3(0,1,0), vec3(1,2,1), vec4(0.75,0.75,0.75,1));
}
