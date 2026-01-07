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
    ACTION_KICK_LEFT_FORWARD,
    ACTION_KICK_RIGHT_FORWARD,
    ACTION_KICK_LEFT_BACKWARD,
    ACTION_KICK_RIGHT_BACKWARD,
    ACTION_STAND_LEFT,
    ACTION_STAND_RIGHT,
    ACTION_FLIP,
    BUTTON_ARROW,
    BUTTONS_LINE,

    // 3D Textures
    SKYBOX_UP,
    SKYBOX_DOWN,
    SKYBOX_FRONT,
    SKYBOX_BACK,
    SKYBOX_LEFT,
    SKYBOX_RIGHT,

    // Menu textures
    BACKGROUND_TILE
};

#endif // DATA_H
