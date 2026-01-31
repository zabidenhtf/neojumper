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

int main(){
    config::init();

    screen_width = stoi(string(config::load_data("GFX", "screen_width", "800")));
    screen_height = stoi(string(config::load_data("GFX", "screen_height", "600")));
    fov = stoi(string(config::load_data("GFX", "fov", "90")));
    fullscreen = string(config::load_data("GFX", "fullscreen", "False"));
    shadow_resolution = stoi(string(config::load_data("GFX", "shadow_resolution", "512")));
    sound_volume = stoi(string(config::load_data("AUDIO", "volume", "100")));

    gfx::init();
    gfx::blend_normal();
    audio::init();
    input::init(gfx::get_window());
    // Load textures
    // Game stuff
    data::textures::push_path("menu/logo.png");
    data::textures::push_path("game/digit1.png");
    data::textures::push_path("game/digit2.png");
    data::textures::push_path("game/digit3.png");
    data::textures::push_path("game/message_go.png");
    data::textures::push_path("game/message_excellent.png");
    // Action buttons
    data::textures::push_path("actions/action_kick_left_forward.png");
    data::textures::push_path("actions/action_kick_right_forward.png");
    data::textures::push_path("actions/action_kick_left_backward.png");
    data::textures::push_path("actions/action_kick_right_backward.png");
    data::textures::push_path("actions/action_stand_left.png");
    data::textures::push_path("actions/action_stand_right.png");
    data::textures::push_path("actions/action_flip.png");
    data::textures::push_path("game/button_arrow.png");
    data::textures::push_path("game/buttons_line.png");
    // Skybox
    data::textures::push_path("sky/up.png");
    data::textures::push_path("sky/down.png");
    data::textures::push_path("sky/front.png");
    data::textures::push_path("sky/back.png");
    data::textures::push_path("sky/left.png");
    data::textures::push_path("sky/right.png");
    // Menu
    data::textures::push_path("menu/background_tile.png");
    // Selector stuff
    data::textures::push_path("ui/selection_state1.png");
    data::textures::push_path("ui/selection_state2.png");
    data::textures::push_path("ui/selection_state3.png");
    // Hud stuff
    data::textures::push_path("hud/hud_bar_tile.png");

    // Audio
    // Melodies
    data::audio::push_path("music/SimpleJump.ogg");

    // Fonts
    data::fonts::font_paths.push_back("assets/fonts/eurostile_roman.ttf");

    // Loading all stuff
    gfx::load_font(data::fonts::font_paths[EUROSTILE_ROMAN],0);
    data::textures::load_textures();
    data::audio::load_audio();

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
                melody.stop();
            }
        }

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
