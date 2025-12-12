#include <iostream>
#include "interface.hpp"

using namespace std;

int main(){
    gfx::init();
    while(!glfwWindowShouldClose(gfx::get_window())){
        gfx::swap();
    }
}
