/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "data.hpp"

void data::textures::load_textures(){
    // Simple null texture
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
    data::textures::textures.push_back(null_tex); // Pushing to vector null texture
    for (int i = 0; i<data::textures::textures_paths.size(); i++){
        data::textures::textures.push_back(gfx::load_texture("assets/" + data::textures::textures_paths[i])); // Loading another stuff
    }
}

// Interface for push back for simpler code
void data::textures::push_path(string path){
    data::textures::textures_paths.push_back(path);
}

// Interface for push back for simpler code
void data::audio::push_path(string path){
    data::audio::sounds_paths.push_back(path);
}

void data::audio::load_audio(){
    for (int i = 0; i<data::audio::sounds_paths.size(); i++){
        data::audio::sounds.push_back(::audio::load_sound("sounds/" + data::audio::sounds_paths[i])); // Pushing audio datas to vector
    }
}