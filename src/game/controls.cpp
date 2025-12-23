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
    gfx::viewport(0,0,screen_width, screen_height);
    gfx::mapscreen(0,0, width,300);

    gfx::set_color(1,1,1,1);

    // pretty line
    for (int i = 0; i<screen_width/64; i++){
            gfx::enable_texture(data2d::textures[BUTTONS_LINE]);
        gfx::begin_quads();
        gfx::draw_2d_quad(i*64, 300-size/2-8, 64, 16);
        gfx::end();
        gfx::disable_texture();
    }

    // Small animation
    if (step == 0){
        gfx::set_color(1,1,1,step_time * 4);
    }
    else{
        gfx::set_color(1,1,1,1);
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
        gfx::begin_quads();
        gfx::draw_2d_quad((i*(size+distance) - (time*(size+distance)/speed)) + size/2, 300-size, size, size);
        gfx::end();
        gfx::disable_texture();
    }
    // helpfull arrow
    gfx::enable_texture(data2d::textures[BUTTON_ARROW]);
    gfx::begin_quads();
    gfx::draw_2d_quad(size/8, 300-size, size/4, size/4);
    gfx::end();
    gfx::disable_texture();
}
