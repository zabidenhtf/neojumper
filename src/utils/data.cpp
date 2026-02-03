/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "utils/data.hpp"

DataSystem *Data; // Global object initialization

// Constructor
DataSystem::DataSystem(){
    // Cleaning vectors
    TexturesPaths.clear();
    Textures.clear();
    SoundPaths.clear();
    Sounds.clear();
}

// Get functions
GraphicsTexture DataSystem::GetTextureByID(int ID){
    return Textures[ID];
}
SoundData DataSystem::GetSoundByID(int ID){
    return Sounds[ID];
}

// Push functions
void DataSystem::PushTexturePath(string Path){
    TexturesPaths.push_back(Path);
}
void DataSystem::PushSoundPath(string Path){
    SoundPaths.push_back(Path);
}

void DataSystem::LoadEverything(){
    LoadTextures();
    LoadSounds();
}

// Load functions
void DataSystem::LoadTextures(){
    // Simple null texture
    // TODO: Add load_null_texture function
    GLuint NullTexRaw;
    glGenTextures(1, &NullTexRaw);
    glBindTexture(GL_TEXTURE_2D, NullTexRaw);

    // Drawing 1 white pixel
    unsigned char pixel[4] = {255, 255, 255, 255};
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    GraphicsTexture NullTex;
    NullTex.Raw = NullTexRaw;
    NullTex.Width = 1;
    NullTex.Height = 1;
    Textures.push_back(NullTex); // Pushing to vector null texture
    for (int i = 0; i<TexturesPaths.size(); i++){
        Textures.push_back(Graphics->LoadTexture("assets/" + TexturesPaths[i])); // Loading another stuff
    }
}
void DataSystem::LoadSounds(){
    for (int i = 0; i<SoundPaths.size(); i++){
        Sounds.push_back(Audio->LoadSound("sounds/" + SoundPaths[i])); // Pushing audio datas to vector
    }
}