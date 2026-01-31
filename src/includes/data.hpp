/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "interface.hpp"
#include "includes.hpp"

#pragma once

class DataSystem{
public:
    DataSystem();
    // Get functions
    texture GetTextureByID(int ID);
    sound_data GetSoundByID(int ID);
    // Push functions
    void PushTexturePath(string Path);
    void PushSoundPath(string Path);
    // Load functions
    void LoadEverything();
    void LoadTextures();
    void LoadSounds();
private:
    // Data
    vector<string> TexturesPaths;
    vector<texture> Textures;
    vector<string> SoundPaths;
    vector<sound_data> Sounds;
};

extern DataSystem *Data; // Global data pointer

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
