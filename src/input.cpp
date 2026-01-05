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
int last_button_pressed(){
    if (!key_buffer.empty()){
        return key_buffer.back();
    }
    return -1;
}
