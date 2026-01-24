/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "interface.hpp"
#include "system.hpp"
//#include <iostream>

vector<int> key_buffer;

void input::callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (action == GLFW_PRESS) {
        //cout << "Pressed:" << key << "\n";
        key_buffer.push_back(key);
    }
}

void input::init(GLFWwindow* window){
    write_dbg("INPUT", "Input initialisated");
    glfwSetKeyCallback(window, callback);
}

bool input::button_pressed(int key){
    if (!key_buffer.empty()){
        if (key_buffer.back() == key){
            return true;
        }
    }
    return false;
}
int input::last_button_pressed(){
    if (!key_buffer.empty()){
        return key_buffer.back();
    }
    return -1;
}

void input::clear(){
    key_buffer.clear();
}
