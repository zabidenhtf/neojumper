/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "selector.hpp"
#include "data.hpp"

menu_selector::menu_selector(){
    write_dbg("SELECTOR", "Selector initialisated");
    reset();
}

void menu_selector::reset(){
    button_selector_max = 3;
    button_selector_min = 0;
    button_selected_now = button_selector_min;
}

void menu_selector::update(double tick){
    // Selector update
    if (!key_buffer.empty()){
            switch(key_buffer.back()){
            case GLFW_KEY_DOWN:
                if (button_selected_now != button_selector_max){
                    button_selected_now += 1;
                    write_dbg("SELECTOR", "Selector down");
                }
                break;
            case GLFW_KEY_UP:
                if (button_selected_now != button_selector_min){
                    button_selected_now -= 1;
                    write_dbg("SELECTOR", "Selector up");

                }
                break;
            case GLFW_KEY_ENTER:
                switch (button_selected_now){
                case PLAY:
                    write_dbg("SELECTOR", "Selected play");
                    game_enabled = true;
                    break;
                case EXIT:
                    write_dbg("SELECTOR", "Selected exit");
                    gfx::kill();
                    break;
                default:
                    write_dbg("SELECTOR", "INDEV");
                    break;

                }
                break;
            }
    }
    render();
}

void menu_selector::render(){
    int width = 300*gfx::screen_aspect();
    gfx::set_viewport(0,0,screen_width, screen_height);
    gfx::set_ortho(0,0, width,300);
    float frame_width = width/3;
    float button_height = 24;
    float frame_height = (button_height+8)*(button_selector_max+1);

    vec2 frame_pos = vec2(16,128);

    gfx::enable_texture(data2d::textures[NULL_TEX]);
    // Frame with excellent borders
    gfx::draw_2d_quad(frame_pos - vec2(1,1), vec2(frame_width+2,frame_height+2), vec4(0,0,0,1));
    gfx::draw_2d_quad(frame_pos, vec2(frame_width,frame_height), vec4(1,1,1,1));
    gfx::disable_texture();

    for (int i = 0; i < button_selector_max + 1; i++){
        // buttons
        gfx::enable_texture(data2d::textures[NULL_TEX]);
        vec4 color;
        // If selected change color
        if (i == button_selected_now){
            color = vec4(1,0,0,1);
        }
        else{
            color = vec4(0.5,0.5,0.5,1);
        }
        gfx::draw_2d_quad(frame_pos + vec2(2, 4+(i*(button_height+8))), vec2(frame_width-4,button_height), color);
        gfx::disable_texture();
    }
}
