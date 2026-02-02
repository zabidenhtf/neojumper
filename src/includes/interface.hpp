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


#include "system.hpp"
#include "includes.hpp"

using namespace glm;

extern vector<int> key_buffer; // keys buffer, it need to save keys

// Interface INPUT
namespace input
{
    void callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void init(GLFWwindow* window);
    bool button_pressed(int key);
    int last_button_pressed();
    void clear();
}