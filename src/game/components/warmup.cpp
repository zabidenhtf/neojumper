#include "warmup.hpp"
//#include <iostream>
#include "../game.hpp"
#include "data.hpp"

game_warmup::game_warmup(){
    write_dbg("WARMUP","Timer initialisated");
    reset();
}

void game_warmup::reset(){
    write_dbg("WARMUP","Timer reset");
    time = 0;
    active = true;
}

void game_warmup::update(double tick){
    if (active == true){
        time += tick;
        state_time += tick;
        //write_dbg("WARMUP","updating\n"); // Some debug stuff
        //std::cout << state_time;
        if (time > timer_time){
            active = false;
            write("Game started\n");
            game->game_started = true;
        }
        else if (state_time > timer_time/4){
            state-=1;
            state_time = 0;
        }
        render();
    }
}

void game_warmup::render(){
    int width = 300*gfx::screen_aspect();
    gfx::set_viewport(0,0,screen_width, screen_height);
    gfx::set_ortho(0,0, width,300);

    double digit_size = 150*state_time;

    switch (state){
    case 4:
        gfx::enable_texture(data2d::textures[DIGIT3]);
        gfx::draw_2d_quad(vec2(width/2-digit_size/2,150-digit_size/2),vec2(digit_size,digit_size), vec4(1,1,1,1));
        gfx::disable_texture();
        break;
    case 3:
        gfx::enable_texture(data2d::textures[DIGIT2]);
        gfx::draw_2d_quad(vec2(width/2-digit_size/2,150-digit_size/2),vec2(digit_size,digit_size), vec4(1,1,1,1));
        gfx::disable_texture();
        break;
    case 2:
        gfx::enable_texture(data2d::textures[DIGIT1]);
        gfx::draw_2d_quad(vec2(width/2-digit_size/2,150-digit_size/2),vec2(digit_size,digit_size), vec4(1,1,1,1));
        gfx::disable_texture();
        break;
    case 1:
        gfx::enable_texture(data2d::textures[MESSAGE_GO]);
        gfx::draw_2d_quad(vec2(width/2-digit_size,150-digit_size/2),vec2(digit_size*2,digit_size), vec4(1,1,1,1)); // fixed size
        gfx::disable_texture();
        break;
    }
}
