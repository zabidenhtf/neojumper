/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include <AL/al.h>
#include <AL/alc.h>
#include <sndfile.h>
#include <inttypes.h>
#include <AL/alext.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "includes.hpp"
#include "utils/system.hpp"

#pragma once

using namespace glm;

struct vertex2D
{
    vec2 Position;
    vec2 TexturePos;
};

struct vertex3D
{
    vec3 Position;
    vec2 TexturePos;
    vec3 Normal;
};

struct GraphicsTexture{ // 2D texture structure
    GLuint Raw;
    int Width;
    int Height;
};

struct GraphicsModel{ // model structure with draw stuff
    GLuint VAO, VBO, EBO;
};

struct SoundData{ // Sound data with raw audio data and path
    string Path;
    ALuint Raw;
    int BPM; // Beats per min
};

class DataSystem{
public:
    // Load functions
    GraphicsModel LoadModel(const string path); // On some time public, TODO: Add LoadModels function 
    DataSystem();
    // Get functions
    GraphicsTexture GetTextureByID(int ID);
    SoundData GetSoundByID(int ID);
    // Push functions
    void PushTexturePath(string Path);
    void PushSoundPath(string Path);
    // Load functions
    void LoadEverything();
    void LoadTextures();
    void LoadSounds();
private:
    // Load functions
    SoundData LoadSound(string Path); // Loading raw sound using AL
    GraphicsTexture LoadTexture(const string &path); // Loading PNG image using libpng
    // Data
    vector<string> TexturesPaths;
    vector<GraphicsTexture> Textures;
    vector<string> SoundPaths;
    vector<SoundData> Sounds;
    // Assimp importer
    Assimp::Importer importer;
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
