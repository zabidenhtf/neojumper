#include "controls.hpp"
#include "game.hpp"
#include "../data.hpp"

controls::controls(){
    write_dbg("CONTROLS","initialisated");
}


void controls::update(double tick){
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

        if (!key_buffer.empty()){
            if (key_buffer.back() == dance_binds[game->now_dance.movements[step]] && press_time == true){
                //write("Pressed");
                if (step%5 == 0){
                    game->message_component->spawn(MESSAGE_EXCELLENT);
                }
                press_time = false;
                can_press = false;
                game->score += 20;
            }
        }

        if (step >= game->now_dance.level){
            game->game_started = false;
        }
        render();
    }
}

void controls::render(){
    int width = 300*gfx::screen_aspect();
    gfx::set_viewport(0,0,screen_width, screen_height);
    gfx::set_ortho(0,0, width,300);

    // pretty line
    for (int i = 0; i<screen_width/64; i++){
        gfx::enable_texture(data2d::textures[BUTTONS_LINE]);
        gfx::draw_2d_quad(vec2(i*64, 300-size/2-4), vec2(64, 8),vec4(1,1,1,1));
        gfx::disable_texture();
    }

    // Making many buttons of dance, and then animate it
    for (int i = 0; i < game->now_dance.level; i++){
        switch (game->now_dance.movements[i]){
        case JUMP:
            gfx::enable_texture(data2d::textures[BUTTON_JUMP]);
            break;
        case FLIP:
            gfx::enable_texture(data2d::textures[BUTTON_FLIP]);
            break;
        case KICK_LEFT:
            gfx::enable_texture(data2d::textures[BUTTON_KICK_LEFT]);
            break;
        case KICK_RIGHT:
            gfx::enable_texture(data2d::textures[BUTTON_KICK_RIGHT]);
            break;
        case SHUFFLE_FORWARD:
            gfx::enable_texture(data2d::textures[BUTTON_SHUFFLE_FORWARD]);
            break;
        case SHUFFLE_BACKWARD:
            gfx::enable_texture(data2d::textures[BUTTON_SHUFFLE_BACKWARD]);
            break;
        }
        gfx::draw_2d_quad(vec2((i*(size+distance) - (time*(size+distance)/speed)) + size/2, 300-size), vec2(size, size),vec4(1,1,1,1)); // TODO: Optimisate
        gfx::disable_texture();
    }
    // helpfull arrow
    gfx::enable_texture(data2d::textures[BUTTON_ARROW]);
    gfx::draw_2d_quad(vec2(size/8, 300-size), vec2(size/4, size/4),vec4(1,1,1,1));
    gfx::disable_texture();
}
