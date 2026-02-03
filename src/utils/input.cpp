/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "utils/input.hpp"
#include "utils/system.hpp"
#include "utils/graphics.hpp"

//#include <iostream>

vector<int> KeyBuffer;

void Input::Callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (action == GLFW_PRESS) {
        //cout << "Pressed:" << key << "\n";
        KeyBuffer.push_back(key);
    }
}

void Input::Init(){
    Console.WriteDebug("INPUT", "Input initialisated");
    glfwSetKeyCallback(Graphics->GetWindow(), Callback);
}

bool Input::ButtonPressed(int key){
    if (!KeyBuffer.empty()){
        if (KeyBuffer.back() == key){
            return true;
        }
    }
    return false;
}
int Input::LastButtonPressed(){
    if (!KeyBuffer.empty()){
        return KeyBuffer.back();
    }
    else{
        return -1;
    }
}

void Input::Clear(){
    KeyBuffer.clear();
}
