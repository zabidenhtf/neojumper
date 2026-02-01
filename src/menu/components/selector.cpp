/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "selector.hpp"

#include "data.hpp"
#include "graphics.hpp"

#include "../../game/game.hpp"
#include "../../scene/scene.hpp"

menu_selector::menu_selector(){
    write_dbg("SELECTOR", "Selector initialisated");
    reset();
}

void menu_selector::reset(){
    button_selector_max = 3;
    button_selector_min = 0;
    button_selected_now = button_selector_min;
    width = 300*Graphics->GetScreenAspect();
    frame_width = width/3;
    selection_height = 16;
    frame_height = (selection_height+8)*(button_selector_max+1);
    frame_pos = vec2(16,128);
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
                    game->reset();
                    scene->reset();
                    game_enabled = true;
                    break;
                case EXIT:
                    write_dbg("SELECTOR", "Selected exit");
                    Graphics->Kill();
                    break;
                default:
                    write_dbg("SELECTOR", "INDEV");
                    break;

                }
                break;
            }
    }
    render();
    render_selections(tick);
}

vector<int> indecator_textures= {
    SELECTION_STATE1,
    SELECTION_STATE2,
    SELECTION_STATE3
};

void menu_selector::draw_selection(vec2 pos, vec2 size, string text, vec4 color, bool selected, double tick){
    static float timer;
    static int selection_indecator_id = 3;
    static bool direction = false;
    // Drawing text
    float text_x_pos = (size.x-Graphics->GetTextWidth(size.y, text))/2;
    Graphics->DrawText(pos + vec2(text_x_pos,0), size.y, (Graphics->GetHeight()/300)*size.y, text, color);  
    if (selected == true){
        // Updating texture
        timer+=tick;
        if (timer >= 0.1) {
            if (direction) {
                selection_indecator_id++;
                if (selection_indecator_id >= indecator_textures.size()) {
                    selection_indecator_id = indecator_textures.size() - 1;
                    direction = false; // changing direction
                }
            } else {
                if (selection_indecator_id == 0) {
                    direction = true; // here too changing direction
                } else {
                    selection_indecator_id--;
                }
            }
            timer = 0;
        }
        // Draw arrows
        // Left
        Graphics->EnableTexture(Data->GetTextureByID(indecator_textures[selection_indecator_id]));
        Graphics->DrawQuad(pos + vec2(text_x_pos-size.y*2, 0), vec2(size.y*2,size.y), vec4(1,1,1,1));
        // Right
        Graphics->DrawQuad(pos + vec2(text_x_pos+Graphics->GetTextWidth(size.y, text) + size.y*2, 0), vec2(-size.y*2,size.y), vec4(1,1,1,1));
        Graphics->DisableTexture();
    }
}

void menu_selector::render(){
    Graphics->SetViewport(Graphics->GetWidth(), Graphics->GetHeight());
    Graphics->SetOrtho(width, 300);

    Graphics->EnableTexture(Data->GetTextureByID(NULL_TEX));
    // Frame with excellent borders
    Graphics->DrawQuad(frame_pos - vec2(1,1), vec2(frame_width+2,frame_height+2), vec4(0,0,0,1));
    Graphics->DrawQuad(frame_pos, vec2(frame_width,frame_height), vec4(1,1,1,1));
    Graphics->DisableTexture();
}

void menu_selector::render_selections(double tick){
    for (int i = 0; i < button_selector_max + 1; i++){
        // buttons
        vec4 color;
        bool selected;
        // For each selection different text
        string button_labels[4] = {
            "Play",
            "Credits",
            "Settings",
            "Exit"
        };

        // If selected change color
        if (i == button_selected_now){
            color = vec4(0,0.75,0,1);
            selected = true;
        }
        else{
            color = vec4(0,0,0,1);
            selected = false;
        } 
        draw_selection(frame_pos + vec2(0, 4+i*(selection_height+8)), vec2(frame_width, selection_height), button_labels[i], color, selected, tick);
    }
}
