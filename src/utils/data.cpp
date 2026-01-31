/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "data.hpp"

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
texture DataSystem::GetTextureByID(int ID){
    return Textures[ID];
}
sound_data DataSystem::GetSoundByID(int ID){
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
    GLuint null_tex_raw;
    glGenTextures(1, &null_tex_raw);
    glBindTexture(GL_TEXTURE_2D, null_tex_raw);

    unsigned char pixel[4] = {255, 255, 255, 255};
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    texture null_tex;
    null_tex.texture_id = null_tex_raw;
    null_tex.width = 1;
    null_tex.height = 1;
    Textures.push_back(null_tex); // Pushing to vector null texture
    for (int i = 0; i<TexturesPaths.size(); i++){
        Textures.push_back(gfx::load_texture("assets/" + TexturesPaths[i])); // Loading another stuff
    }
}
void DataSystem::LoadSounds(){
    for (int i = 0; i<SoundPaths.size(); i++){
        Sounds.push_back(audio::load_sound("sounds/" + SoundPaths[i])); // Pushing audio datas to vector
    }
}