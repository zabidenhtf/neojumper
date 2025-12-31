#ifndef DATA_H
#define DATA_H

#include "interface.hpp"
#include "includes.hpp"

// 2D stuff
namespace data2d {
    extern vector<string> textures_paths;
    extern vector<texture> textures;
    extern void load_textures();
}

enum{
    NULL_TEX,
    LOGO,
    DIGIT1,
    DIGIT2,
    DIGIT3,
    MESSAGE_GO,
    MESSAGE_EXCELLENT,
    BUTTON_JUMP,
    BUTTON_FLIP,
    BUTTON_KICK_LEFT,
    BUTTON_KICK_RIGHT,
    BUTTON_SHUFFLE_FORWARD,
    BUTTON_SHUFFLE_BACKWARD,
    BUTTON_ARROW,
    BUTTONS_LINE,

    // 3D Textures
    SKYBOX_UP,
    SKYBOX_DOWN,
    SKYBOX_FRONT,
    SKYBOX_BACK,
    SKYBOX_LEFT,
    SKYBOX_RIGHT
};

#endif // DATA_H
