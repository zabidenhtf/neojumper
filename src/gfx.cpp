#include <iostream>
#include "interface.hpp"

using namespace std;

GLFWwindow *root = nullptr;
static int screen_width = 800;
static int screen_height = 600;
static bool fullscreen = false;

GLFWwindow *gfx::get_window(){
    return root;
}

void gfx::init(){
    if (glfwInit()){
        cout << "[GL] initialisated";
    }

    root = glfwCreateWindow(screen_width, screen_height, "Openjumper", NULL, NULL);

    if (!root){
        cout << "[GFX] Failed to create window";
    }
    glfwMakeContextCurrent(root);
    glfwSwapInterval(1);
}

void gfx::swap(){
    glfwPollEvents();
    glfwSwapBuffers(root);
}
