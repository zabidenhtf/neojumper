#include "jumper.hpp"
#include "../../game/game.hpp"

entity_jumper_player::entity_jumper_player(){
    write_dbg("JUMPER", "Added to scene");
    direction = 45;
    reset();
}

void entity_jumper_player::reset(){
    pos = vec3(0,0,0);
}

void entity_jumper_player::move_forward(double tick){
    pos += vec3(cos(direction)*tick,0,sin(direction) * tick);
}

void entity_jumper_player::move_backward(double tick){
    pos += vec3(cos(direction)*-tick,0,sin(direction) * -tick);
}

void entity_jumper_player::update(double tick){
    DANCE_MOVEMENTS move_now = game->now_dance.movements[game->controls->step];
    if (move_now == SHUFFLE_FORWARD){ // Check movement's now
        move_forward(tick);
    }
    else if (move_now == SHUFFLE_BACKWARD){
        move_backward(tick);
    }
    else{
        // Do nothing (on some time)
    }
    render();
}

void entity_jumper_player::render(){
    gfx::draw_3d_box(pos+vec3(0,1,0), vec3(1,2,1), vec4(0.75,0.75,0.75,1));
}
