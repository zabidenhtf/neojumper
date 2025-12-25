#include "system.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <random>
#include <SimpleIni.h>

static CSimpleIniA ini;

void write(std::string msg){
    std::cout << msg << "\n";
}

void write_dbg(std::string about, std::string msg){
    std::cout << "[" << about << "] " << msg << "\n";
}

int randint(int min, int max){
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

std::string read_file(const char* path){
    std::ifstream file(path);
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

bool config::init() {
    ini.SetUnicode();
    SI_Error rc = ini.LoadFile("config.ini");
    return rc >= 0;
}

const char* config::load_data(const char* section, const char* key, const char* standart) {
    return ini.GetValue(section, key, standart);
}
