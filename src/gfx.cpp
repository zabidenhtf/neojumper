#include "system.hpp"
#include "interface.hpp"
#include "lodepng/lodepng.h"

using namespace std;

GLFWwindow *root = nullptr;

// For render and native mod
GLFWwindow *gfx::get_window(){
    return root;
}

void gfx::mapscreen(int x, int y, int w, int h){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(x, x + w, y + h, y, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void gfx::viewport(int x, int y, int w, int h){
    glViewport(x, y, w, h);
}

void gfx::init(){
    if (glfwInit()){
        write_dbg("GFX", "Graphics initialisated");
    }

    root = glfwCreateWindow(screen_width, screen_height, "Openjumper", NULL, NULL);

    if (!root){
        write_dbg("GFX", "Failed to create window");
    }
    glfwMakeContextCurrent(root);
}

void gfx::swap(){
    glfwPollEvents();
    glfwSwapBuffers(root);
}

void gfx::clear(float r, float g, float b){
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void gfx::begin_quads(){
    glBegin(GL_QUADS);
}

void gfx::set_color(float r, float g, float b, float a){
    glColor4f(r,g,b,a);
}

// TODO: add 3D stuff
void gfx::draw_2d_quad(int x, int y, int w, int h){
    glTexCoord2f(0.f, 0.f); glVertex2f(x,     y);
    glTexCoord2f(1.f, 0.f); glVertex2f(x + w, y);
    glTexCoord2f(1.f, 1.f); glVertex2f(x + w, y + h);
    glTexCoord2f(0.f, 1.f); glVertex2f(x,     y + h);
}

texture gfx::load_texture(const string &filename)
{
    texture txture;
    std::vector<unsigned char> image;
    unsigned int w, h;
    unsigned error = lodepng::decode(image, w, h, filename.c_str()); // decompiling with
    // if image not found

    txture.width  = (int)w;
    txture.height = (int)h;

    if (error)
    {
        string buffer = "Failed to open " + filename + " image";
        write_dbg("GFX", buffer);
    }
    else{
        string buffer = "Opened " + filename + " image";
        write_dbg("GFX", buffer);
    }

    glGenTextures(1, &txture.texture_id);
    glBindTexture(GL_TEXTURE_2D, txture.texture_id);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Maybe im change to GL_LINEAR_NEARLEST_LINEAR
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, txture.width, txture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());

    return txture;
}

void gfx::enable_texture(texture &txture){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, txture.texture_id);
}

void gfx::disable_texture(){
    glDisable(GL_TEXTURE_2D);
}

void gfx::end(){
    glEnd();
}

float gfx::screen_aspect(){
    return screen_width/screen_height;
}

void gfx::kill(){
    glfwTerminate();
}
