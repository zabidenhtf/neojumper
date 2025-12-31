#include "message.hpp"
#include "data.hpp"

message::message(){
    write_dbg("MESSAGE", "Message system initialisated");
}

void message::spawn(int txture){
    this->txture = txture;
    this->active = true;
}

void message::update(double tick){
    if (active == true){
        time += tick;
        if (time > 1){
            active = false;
        }
        render();
    }
}

void message::render(){
    int width = 300*gfx::screen_aspect();
    gfx::set_viewport(0,0,screen_width, screen_height);
    gfx::set_ortho(0,0, width,300);

    gfx::enable_texture(data2d::textures[txture]);
    gfx::draw_2d_quad(vec2(width/2-300/2,150-150/2),vec2(300,150), vec4(1,1,1,1)); // fixed size
    gfx::disable_texture();
}
