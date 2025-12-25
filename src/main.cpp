#include "interface.hpp"
#include "system.hpp"
#include "data.hpp"
#include "game/game.hpp"
#include "includes.hpp"

// Target fps and another configs
const float FPS = 60.00f;
const float frame_time = 1.0 / FPS;
double last_time = glfwGetTime();

game_core* game = nullptr;

namespace data2d {
    vector<string> textures_paths;
    vector<texture> textures;
    void load_textures(){
        for (int i = 0; i<data2d::textures_paths.size(); i++){
            data2d::textures.push_back(gfx::load_texture("assets/" + data2d::textures_paths[i]));
        }
    }
}

int main(){
    config::init();

    screen_width = stoi(string(config::load_data("Options", "screen_width", "800")));
    screen_height = stoi(string(config::load_data("Options", "screen_height", "600")));

    gfx::init();
    input::init(gfx::get_window());
    // Load textures
    data2d::textures_paths.push_back("logo.png");
    data2d::textures_paths.push_back("ui/digit1.png");
    data2d::textures_paths.push_back("ui/digit2.png");
    data2d::textures_paths.push_back("ui/digit3.png");
    data2d::textures_paths.push_back("ui/message_go.png");
    // Action buttons
    data2d::textures_paths.push_back("ui/button_jump.png");
    data2d::textures_paths.push_back("ui/button_flip.png");
    data2d::textures_paths.push_back("ui/button_kick_left.png");
    data2d::textures_paths.push_back("ui/button_kick_right.png");
    data2d::textures_paths.push_back("ui/button_shuffle_forward.png");
    data2d::textures_paths.push_back("ui/button_shuffle_backward.png");
    data2d::textures_paths.push_back("ui/button_arrow.png");
    data2d::textures_paths.push_back("ui/buttons_line.png");
    data2d::load_textures();

    game = new game_core();

    while(!glfwWindowShouldClose(gfx::get_window())){
        gfx::clear(0,0,0);
        double frame_start = glfwGetTime();

        double delta = frame_start - last_time;
        last_time = frame_start;

        game->update(delta);

        key_buffer.clear();
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
}
