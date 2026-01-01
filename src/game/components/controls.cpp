#include "controls.hpp"
#include "../game.hpp"
#include "data.hpp"

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
    float width = screen_width / 1.5;
    float height = screen_height / 1.5;
    gfx::set_viewport(0,0,screen_width, screen_height);
    gfx::set_ortho(0,0, width,height);

    // pretty line
    for (int i = 0; i<screen_width/64; i++){
        gfx::enable_texture(data2d::textures[BUTTONS_LINE]);
        gfx::draw_2d_quad(vec2(i*64, height-size/2-4), vec2(64, 8),vec4(1,1,1,1));
        gfx::disable_texture();
    }

    // Making many buttons of dance, and then animate it
    for (int i = 0; i < width/(distance+size)+1; i++){ // Optimisated
        if (i + step < game->now_dance.movements.size()){
            switch (game->now_dance.movements[i+step]){
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
            float x = i*(size+distance);
            float time_x = step_time*(size+distance)/speed;
            gfx::draw_2d_quad(vec2(x - time_x + size/2, height-size), vec2(size, size),vec4(1,1,1,1));
            gfx::disable_texture();
        }
    }
    // helpfull arrow
    gfx::enable_texture(data2d::textures[BUTTON_ARROW]);
    gfx::draw_2d_quad(vec2(size/8, height-size), vec2(size/4, size/4),vec4(1,1,1,1));
    gfx::disable_texture();
}
