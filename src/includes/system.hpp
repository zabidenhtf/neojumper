// OpenJumper base lib
#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>

void write(std::string msg);
void write_dbg(std::string about, std::string msg);
int randint(int min, int max);
std::string read_file(const char* path);

namespace config{
    bool init();
    const char* load_data(const char* section, const char* key, const char* standart);
}

#endif // SYSTEM_H
