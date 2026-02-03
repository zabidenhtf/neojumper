/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */

#include "utils/system.hpp"
#include "utils/graphics.hpp"
#include "utils/audio.hpp"
#include "utils/data.hpp"
#include "utils/input.hpp"
#include "utils/config.hpp"

#include "game/game.hpp"
#include "scene/scene.hpp"
#include "menu/menu.hpp"
#include "includes.hpp"

// Target fps and another configs
const float FPS = 60.00f;
const float frame_time = 1.0 / FPS;
double last_time = glfwGetTime();

// Cores global objects
MenuCore* Menu = nullptr;
GameCore* Game = nullptr;
SceneCore* Scene = nullptr;

bool GameEnabled = false;

int main(){
    Console.Write("Launched NeoJumper " + string(GAME_MILESTONE));
    // Initializating systems
    Config = new ConfigureSystem();
    Data = new DataSystem();
    Graphics = new GraphicsSystem();
    Audio = new AudioSystem();
    Input::Init(); // TODO: make it objective

    // Load textures
    // Game stuff
    Data->PushTexturePath("menu/logo.png");
    Data->PushTexturePath("game/digit1.png");
    Data->PushTexturePath("game/digit2.png");
    Data->PushTexturePath("game/digit3.png");
    Data->PushTexturePath("game/message_go.png");
    Data->PushTexturePath("game/message_excellent.png");
    // Action buttons
    Data->PushTexturePath("actions/action_kick_left_forward.png");
    Data->PushTexturePath("actions/action_kick_right_forward.png");
    Data->PushTexturePath("actions/action_kick_left_backward.png");
    Data->PushTexturePath("actions/action_kick_right_backward.png");
    Data->PushTexturePath("actions/action_stand_left.png");
    Data->PushTexturePath("actions/action_stand_right.png");
    Data->PushTexturePath("actions/action_flip.png");
    Data->PushTexturePath("game/button_arrow.png");
    Data->PushTexturePath("game/buttons_line.png");
    // Skybox
    Data->PushTexturePath("sky/up.png");
    Data->PushTexturePath("sky/down.png");
    Data->PushTexturePath("sky/front.png");
    Data->PushTexturePath("sky/back.png");
    Data->PushTexturePath("sky/left.png");
    Data->PushTexturePath("sky/right.png");
    // Menu
    Data->PushTexturePath("menu/background_tile.png");
    // Selector stuff
    Data->PushTexturePath("ui/selection_state1.png");
    Data->PushTexturePath("ui/selection_state2.png");
    Data->PushTexturePath("ui/selection_state3.png");
    // Hud stuff
    Data->PushTexturePath("hud/hud_bar_tile.png");

    // Audio
    // Melodies
    Data->PushSoundPath("music/SimpleJump.wav");

    // On some time abonded
    // Fonts
    //data::fonts::font_paths.push_back("assets/fonts/eurostile_roman.ttf");

    // Loading all stuff
    Graphics->LoadFont("assets/fonts/eurostile_roman.ttf",0);
    Data->LoadEverything();

    Scene = new SceneCore();
    Game = new GameCore();
    Menu = new MenuCore();

    while(!Graphics->ShouldWindowClose()){
        Graphics->ClearScreen(vec3(0,0,0));
        double frame_start = Graphics->GetTime();

        double delta = frame_start - last_time;
        last_time = frame_start;

        switch (GameEnabled){
        case true:
            Scene->Update(delta);
            Game->Update(delta);
            break;
        case false:
            Menu->Update(delta);
            break;
        }

        // Exit from game to main menu
        if (GameEnabled == true){
            if (Input::ButtonPressed(GLFW_KEY_ESCAPE)){
                GameEnabled = false;
                Melody.Stop();
            }
        }

        Input::Clear();
        Graphics->PollEvents();

        double frame_end = Graphics->GetTime();
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
