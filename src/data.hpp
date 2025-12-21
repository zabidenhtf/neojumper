#ifndef DATA_H
#define DATA_H

#include "interface.hpp"
#include <vector>
#include <string>

using namespace std;

// 2D stuff
namespace data2d {
    extern vector<string> textures_paths;
    extern vector<texture> textures;
    extern void load_textures();
}

enum{
    LOGO,
    DIGIT1,
    DIGIT2,
    DIGIT3,
    MESSAGE_GO,
    BUTTON_JUMP,
    BUTTON_FLIP,
    BUTTON_KICK_LEFT,
    BUTTON_KICK_RIGHT,
    BUTTON_SHUFFLE_FORWARD,
    BUTTON_SHUFFLE_BACKWARD,
    BUTTON_ARROW
};

#endif // DATA_H
