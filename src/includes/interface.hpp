/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#pragma once
// Third party AUDIO libs
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <AL/al.h>
#include <AL/alc.h>
#include <sndfile.h>
#include <inttypes.h>
#include <AL/alext.h>

#include "system.hpp"
#include "includes.hpp"

using namespace glm;

inline string fullscreen;
inline int sound_volume;

extern vector<int> key_buffer; // keys buffer, it need to save keys

struct sound_data{
    string path;
    ALuint sound_buffer;
};

struct sound{
    sound_data data;
    ALuint sound_source;
    void play_global(){
        // Sound configuration
        alGenSources(1, &sound_source);
        alSourcef(sound_source, AL_PITCH, 1.0f);
        alSourcef(sound_source, AL_GAIN, static_cast<float>(sound_volume/100));
        alSourcei(sound_source, AL_SOURCE_RELATIVE, AL_TRUE); // Global sound
        alSource3f(sound_source, AL_POSITION, 0.0f, 0.0f, 0.0f);
        alSourcei(sound_source, AL_BUFFER, data.sound_buffer);
        alSourcePlay(sound_source);
        write_dbg("AUDIO", "Playing global " + data.path);
    };
    void play(vec3 pos){
        // Sound configuration
        alGenSources(1, &sound_source);
        alSourcef(sound_source, AL_PITCH, 1.0f);
        alSourcef(sound_source, AL_GAIN, static_cast<float>(sound_volume/100));
        alSource3f(sound_source, AL_POSITION, pos.x, pos.y, pos.z);
        alSourcei(sound_source, AL_BUFFER, data.sound_buffer);
        alSourcePlay(sound_source);
        write_dbg("AUDIO", "Playing " + data.path);
    };
    void stop(){
        alSourceStop(sound_source);
    };
};

// Interface INPUT
namespace input
{
    void callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void init(GLFWwindow* window);
    bool button_pressed(int key);
    int last_button_pressed();
    void clear();
}

// Interface AUDIO
namespace audio{
    void init();
    sound_data load_sound(string path);
    void play_sound();
    void kill();
}