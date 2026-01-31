/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#ifndef DATA_H
#define DATA_H

#include "interface.hpp"
#include "includes.hpp"

namespace data{
    namespace textures{
        inline vector<string> textures_paths;
        inline vector<texture> textures; // TODO: rename as data
        extern void push_path(string path);
        extern void load_textures();
    }
    namespace fonts{
        inline vector<string> font_paths;
    }
    namespace audio{
        inline vector<string> sounds_paths;
        inline vector<sound_data> sounds;
        extern void push_path(string path);
        extern void load_audio();
    }
}

enum{ // Textures
    NULL_TEX,
    LOGO,
    DIGIT1,
    DIGIT2,
    DIGIT3,
    MESSAGE_GO,
    MESSAGE_EXCELLENT,
    ACTION_KICK_LEFT_FORWARD,
    ACTION_KICK_RIGHT_FORWARD,
    ACTION_KICK_LEFT_BACKWARD,
    ACTION_KICK_RIGHT_BACKWARD,
    ACTION_STAND_LEFT,
    ACTION_STAND_RIGHT,
    ACTION_FLIP,
    BUTTON_ARROW,
    BUTTONS_LINE,

    // 3D Textures
    SKYBOX_UP,
    SKYBOX_DOWN,
    SKYBOX_FRONT,
    SKYBOX_BACK,
    SKYBOX_LEFT,
    SKYBOX_RIGHT,

    // Menu textures
    BACKGROUND_TILE,

    // Selector stuff
    SELECTION_STATE1,
    SELECTION_STATE2,
    SELECTION_STATE3,

    // Hud stuff
    HUD_BAR_TILE
};

enum{ // Fonts
    EUROSTILE_ROMAN
};

enum{ // Sounds
    INGAME_MELODY1
};

#endif // DATA_H
