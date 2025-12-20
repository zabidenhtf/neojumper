#include "warmup.hpp"
//#include <iostream>
#include "game.hpp"
#include "../data.hpp"

warmup::warmup(){
    write_dbg("WARMUP","Timer initialisated");
    reset();
}

void warmup::reset(){
    write_dbg("WARMUP","Timer reset");
    time = 0;
    active = true;
}

void warmup::update(double tick){
    if (active == true){
        time += tick;
        //write_dbg("WARMUP","updating\n"); // Some debug stuff
        //std::cout << time;
        if (time > timer_time){
            active = false;
            write("Game started\n");
            game->game_started = true;
        }
        render();
    }
}

void warmup::render(){
    int width = 300*gfx::screen_aspect();
    gfx::viewport(0,0,screen_width, screen_height);
    gfx::mapscreen(0,0, width,300);

    // TODO: Make cool animation
    gfx::set_color(1,1,1,1);

    int state;

    if (0 < time && time < timer_time/4){
        state = 4;
    }
    else if (timer_time/4 < time && time < timer_time/2){
        state = 3;
    }
    else if (timer_time/2 < time && time < timer_time/1.5){
        state = 2;
    }
    else{
        state = 1;
    }

    switch (state){
    case 4:
        gfx::enable_texture(data2d::textures[DIGIT3]);
        gfx::begin_quads();
        gfx::draw_2d_quad(width/2-150/2,150-150/2,150,150);
        gfx::disable_texture();
        gfx::end();
        break;
    case 3:
        gfx::enable_texture(data2d::textures[DIGIT2]);
        gfx::begin_quads();
        gfx::draw_2d_quad(width/2-150/2,150-150/2,150,150);
        gfx::disable_texture();
        gfx::end();
        break;
    case 2:
        gfx::enable_texture(data2d::textures[DIGIT1]);
        gfx::begin_quads();
        gfx::draw_2d_quad(width/2-150/2,150-150/2,150,150);
        gfx::disable_texture();
        gfx::end();
        break;
    case 1:
        gfx::enable_texture(data2d::textures[MESSAGE_GO]);
        gfx::begin_quads();
        gfx::draw_2d_quad(width/2-300/2,150-150/2,300,150); // fixed size
        gfx::disable_texture();
        gfx::end();
        break;
    }
}
