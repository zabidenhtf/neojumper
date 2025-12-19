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
}

enum{
    DIGIT1,
    DIGIT2,
    DIGIT3,
    MESSAGE_GO
};

#endif // DATA_H
