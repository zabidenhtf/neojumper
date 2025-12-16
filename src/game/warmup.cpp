#include "warmup.hpp"
//#include <iostream>

warmup::warmup(){
    write_dbg("WARMUP","Timer initialisated");
    gfx::load_texture("assets/ui/digit1.png", digit1);
    gfx::load_texture("assets/ui/digit2.png", digit2);
    gfx::load_texture("assets/ui/digit3.png", digit3);
    gfx::load_texture("assets/ui/message_go.png", message_go);
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

    if (0 < time && time < timer_time/4){
        gfx::enable_texture(digit3);
    }
    else if (timer_time/4 < time && time < timer_time/2){
        gfx::enable_texture(digit2);
    }
    else if (timer_time/2 < time && time < timer_time/1.5){
        gfx::enable_texture(digit1);
    }
    else{
        gfx::enable_texture(message_go);
    }

    gfx::begin_quads();
    gfx::draw_2d_quad(width/2-150/2,150-150/2,150,150);
    gfx::disable_texture();
    gfx::end();
}
