/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#ifndef INTERFACE_H
#define INTERFACE_H

// Third party GFX libs
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <png.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <ft2build.h>
#include FT_FREETYPE_H
// Third party AUDIO libs
#include <AL/al.h>
#include <AL/alc.h>
#include <sndfile.h>
#include <inttypes.h>
#include <AL/alext.h>

#include "system.hpp"
#include "includes.hpp"

using namespace glm;

inline int screen_width;
inline int screen_height;
inline int shadow_resolution;
inline float fov;
inline string fullscreen;

extern vector<int> key_buffer; // keys buffer, it need to save keys

struct vertex2D
{
    vec2 pos;
    vec2 tex;
};

struct vertex3D
{
    vec3 pos;
    vec2 tex;
    vec3 normal;
};

struct texture{
    GLuint texture_id;
    int width;
    int height;
};

struct sound{
    string path;
    ALuint sound_buffer;
    ALuint sound_source;
    void play_global(){
        // Sound configuration
        alGenSources(1, &sound_source);
        alSourcef(sound_source, AL_PITCH, 1.0f);
        alSourcef(sound_source, AL_GAIN, 1.0f);
        alSourcei(sound_source, AL_SOURCE_RELATIVE, AL_TRUE); // Global sound
        alSource3f(sound_source, AL_POSITION, 0.0f, 0.0f, 0.0f);
        alSourcei(sound_source, AL_BUFFER, this->sound_buffer);
        alSourcePlay(sound_source);
        write_dbg("AUDIO", "Playing " + path);
    };
    void play(vec3 pos){
        // Sound configuration
        alGenSources(1, &sound_source);
        alSourcef(sound_source, AL_PITCH, 1.0f);
        alSourcef(sound_source, AL_GAIN, 1.0f);
        alSource3f(sound_source, AL_POSITION, pos.x, pos.y, pos.z);
        alSourcei(sound_source, AL_BUFFER, this->sound_buffer);
        alSourcePlay(sound_source);
        write_dbg("AUDIO", "Playing " + path);
    };
    void stop(){
        alSourceStop(sound_source);
    };
};

// Interface GFX
namespace gfx
{
    GLFWwindow *get_window();
    void set_ortho(int x, int y, int w, int h);
    void set_viewport(int x, int y, int w, int h);
    void init();
    void load_font(string path, int id);
    void swap();
    void clear(double r, double g, double b);
    void draw_2d_quad(vec2 pos, vec2 size, vec4 color);
    void draw_2d_text(vec2 pos, int text_size, int text_resolution, string text, vec4 color);
    int text_2d_width(int text_size, string text);
    texture load_texture(const string &filename);
    void enable_texture(texture &txture);
    void disable_texture();
    double screen_aspect();
    void blend_normal();
    void blend_additive();
    void kill();
    // 3D stuff of my 3D Neojumper engine
    void set_camera(vec3 pos, vec3 look_at, double fov);
    void draw_3d_plane(vec3 pos, vec2 size, vec4 color, double pitch, double yaw, double roll, bool have_lighting=true); // Just quad, but in 3D
    void draw_3d_box(vec3 pos, vec3 size, vec4 color);
    void set_light(vec3 pos, vec3 look_at, vec4 color);
    void draw_skybox();
}

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
    sound load_sound(string path);
    void play_sound();
    void kill();
}

#endif // INTERFACE_H
