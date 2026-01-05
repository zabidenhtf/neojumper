#include "message.hpp"
#include "data.hpp"

game_message::game_message(){
    write_dbg("MESSAGE", "Message system initialisated");
}

void game_message::spawn(int txture){
    this->txture = txture;
    this->active = true;
    this->time = 0;
}

void game_message::update(double tick){
    if (active == true){
        time += tick;
        if (time > 1){
            active = false;
        }
        render();
    }
}

void game_message::render(){
    int width = 300*gfx::screen_aspect();
    gfx::set_viewport(0,0,screen_width, screen_height);
    gfx::set_ortho(0,0, width,300);

    // Small animation
    float m_height = 150*time;
    float m_width = m_height*2;

    gfx::enable_texture(data2d::textures[txture]);
    gfx::draw_2d_quad(vec2(width/2-m_width/2,150-m_height/2),vec2(m_width,m_height), vec4(1,1,1,1));
    gfx::disable_texture();
}
