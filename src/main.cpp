/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "interface.hpp"
#include "system.hpp"
#include "data.hpp"
#include "game/game.hpp"
#include "scene/scene.hpp"
#include "menu/menu.hpp"
#include "includes.hpp"

// Target fps and another configs
const float FPS = 60.00f;
const float frame_time = 1.0 / FPS;
double last_time = glfwGetTime();

menu_core* menu = nullptr;
game_core* game = nullptr;
scene_core* scene = nullptr;

bool game_enabled = false;

namespace data2d {
    vector<string> textures_paths;
    vector<texture> textures;
    void load_textures(){
        GLuint null_tex_id;
        glGenTextures(1, &null_tex_id);
        glBindTexture(GL_TEXTURE_2D, null_tex_id);

        unsigned char pixel[4] = {255, 255, 255, 255};
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        texture null_tex;
        null_tex.texture_id = null_tex_id;
        null_tex.width = 1;
        null_tex.height = 1;
        data2d::textures.push_back(null_tex);
        for (long long unsigned int i = 0; i<data2d::textures_paths.size(); i++){
            data2d::textures.push_back(gfx::load_texture("assets/" + data2d::textures_paths[i]));
        }
    }
}

int main(){
    config::init();

    screen_width = stoi(string(config::load_data("GFX", "screen_width", "800")));
    screen_height = stoi(string(config::load_data("GFX", "screen_height", "600")));
    fov = stoi(string(config::load_data("GFX", "fov", "90")));
    fullscreen = string(config::load_data("GFX", "fullscreen", "False"));

    gfx::init();
    gfx::blend_normal();
    input::init(gfx::get_window());
    // Load textures
    data2d::textures_paths.push_back("menu/logo.png");
    data2d::textures_paths.push_back("ui/digit1.png");
    data2d::textures_paths.push_back("ui/digit2.png");
    data2d::textures_paths.push_back("ui/digit3.png");
    data2d::textures_paths.push_back("ui/message_go.png");
    data2d::textures_paths.push_back("ui/message_excellent.png");
    // Action buttons
    data2d::textures_paths.push_back("actions/action_kick_left_forward.png");
    data2d::textures_paths.push_back("actions/action_kick_right_forward.png");
    data2d::textures_paths.push_back("actions/action_kick_left_backward.png");
    data2d::textures_paths.push_back("actions/action_kick_right_backward.png");
    data2d::textures_paths.push_back("actions/action_stand_left.png");
    data2d::textures_paths.push_back("actions/action_stand_right.png");
    data2d::textures_paths.push_back("actions/action_flip.png");
    data2d::textures_paths.push_back("ui/button_arrow.png");
    data2d::textures_paths.push_back("ui/buttons_line.png");

    // Skybox
    data2d::textures_paths.push_back("sky/up.png");
    data2d::textures_paths.push_back("sky/down.png");
    data2d::textures_paths.push_back("sky/front.png");
    data2d::textures_paths.push_back("sky/back.png");
    data2d::textures_paths.push_back("sky/left.png");
    data2d::textures_paths.push_back("sky/right.png");

    data2d::textures_paths.push_back("menu/background_tile.png");

    data2d::load_textures();

    scene = new scene_core();
    game = new game_core();
    menu = new menu_core();

    while(!glfwWindowShouldClose(gfx::get_window())){
        gfx::clear(0,0,0);
        double frame_start = glfwGetTime();

        double delta = frame_start - last_time;
        last_time = frame_start;

        switch (game_enabled){
        case true:
            scene->update(delta);
            game->update(delta);
            break;
        case false:
            menu->update(delta);
            break;
        }

        // Exit from game to main menu
        if (game_enabled == true){
            if (input::button_pressed(GLFW_KEY_ESCAPE)){
                game_enabled = false;
            }
        }

        //if (input::button_pressed(GLFW_KEY_ENTER)){
        //    game->reset();
        //    scene->reset();
        //}

        input::clear();
        gfx::swap();

        double frame_end = glfwGetTime();
        double time_taken = frame_end - frame_start;

        if (time_taken < frame_time) {
            // fps limiter
            this_thread::sleep_for(
                chrono::duration<double>(frame_time - time_taken)
            );
        }
    }
    return 0;
}
