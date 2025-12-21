#include "controls.hpp"
#include <iostream>
#include "game.hpp"
#include "../data.hpp"

controls::controls(){
    write_dbg("CONTROLS","initialisated");
}


void controls::update(double tick){
    if (game->game_started == true){
        time += tick;
        step_time += tick;

        if (step_time >= 0.5){
            step++;
            step_time = 0;
            cout << "STEP:" << step << "after " << 1 << "\n";
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

    // Making many buttons of dance, and animate it
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
        gfx::draw_2d_quad(i*(size+distance) - (time*(size+distance)/0.5), 300-size, size, size);
        gfx::end();
        gfx::disable_texture();
    }
    // helpfull arrow
    gfx::enable_texture(data2d::textures[BUTTON_ARROW]);
    gfx::begin_quads();
    gfx::draw_2d_quad(size/8, 300-size*1.5, size/4, size/4);
    gfx::end();
    gfx::disable_texture();
}
