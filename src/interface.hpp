#include <GLFW/glfw3.h>
#include "includes.hpp"
#ifndef INTERFACE_H
#define INTERFACE_H

using namespace std;

static int screen_width = 1200;
static int screen_height = 600;

extern vector<int> key_buffer; // keys buffer, it need to save keys

struct texture{
    GLuint texture_id;
    int width;
    int height;
};

// Interface GFX
namespace gfx
{
    // TODO: Make imageloader, and quad drawing stuff

    GLFWwindow *get_window();
    void mapscreen(int x, int y, int w, int h);
    void viewport(int x, int y, int w, int h);
    void init();
    void swap();
    void clear(double r, double g, double b);
    void begin_quads();
    void set_color(double r, double g, double b, double a);
    void draw_2d_quad(double x, double y, double w, double h);
    texture load_texture(const string &filename);
    void enable_texture(texture &txture);
    void disable_texture();
    void end();
    double screen_aspect();
    void kill();
}

namespace input
{
    void callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void init(GLFWwindow* window);
}

#endif // INTERFACE_H
