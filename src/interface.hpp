#include <GLFW/glfw3.h>
#ifndef INTERFACE_H
#define INTERFACE_H

namespace gfx
{
    GLFWwindow *get_window();
    void init();
    void swap();
}

#endif // INTERFACE_H
