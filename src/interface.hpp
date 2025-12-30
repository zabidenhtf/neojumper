#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <lodepng/lodepng.h>

#include "system.hpp"
#include "includes.hpp"
#ifndef INTERFACE_H
#define INTERFACE_H

using namespace glm;

inline int screen_width;
inline int screen_height;
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
};

struct texture{
    GLuint texture_id;
    int width;
    int height;
};

// Interface GFX
namespace gfx
{
    GLFWwindow *get_window();
    void set_ortho(int x, int y, int w, int h);
    void set_viewport(int x, int y, int w, int h);
    void init();
    void swap();
    void clear(double r, double g, double b);
    void draw_2d_quad(vec2 pos, vec2 size, vec4 color);
    texture load_texture(const string &filename);
    void enable_texture(texture &txture);
    void disable_texture();
    double screen_aspect();
    void kill();
    // 3D stuff of my 3D Openjumper engine
    void set_camera(vec3 pos, vec3 look_at, double fov);
    void draw_3d_plane(vec3 pos, vec2 size, vec4 color, double pitch, double yaw, double roll); // Just quad, but in 3D
    void draw_3d_box(vec3 pos, vec3 size, vec4 color);
    void draw_skybox();
}

// Interface INPUT
namespace input
{
    void callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void init(GLFWwindow* window);
}

#endif // INTERFACE_H
