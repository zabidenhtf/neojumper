#include "controls.hpp"
#include "../game.hpp"
#include "data.hpp"

game_controls::game_controls(){
    write_dbg("CONTROLS","initialisated");
}

void game_controls::reset(){
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
                case KICK_LEFT_FORWARD:
                    gfx::enable_texture(data2d::textures[ACTION_KICK_LEFT_FORWARD]);
                    break;
                case KICK_RIGHT_FORWARD:
                    gfx::enable_texture(data2d::textures[ACTION_KICK_RIGHT_FORWARD]);
                    break;
                case KICK_LEFT_BACKWARD:
                    gfx::enable_texture(data2d::textures[ACTION_KICK_LEFT_BACKWARD]);
                    break;
                case KICK_RIGHT_BACKWARD:
                    gfx::enable_texture(data2d::textures[ACTION_KICK_RIGHT_BACKWARD]);
                    break;
                case STAND_LEFT:
                    gfx::enable_texture(data2d::textures[ACTION_STAND_LEFT]);
                    break;
                case STAND_RIGHT:
                    gfx::enable_texture(data2d::textures[ACTION_STAND_RIGHT]);
                    break;
                case FLIP:
                    gfx::enable_texture(data2d::textures[ACTION_FLIP]);
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
