/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */

#pragma once
#include <string>

void write(std::string msg);
void write_dbg(std::string about, std::string msg);
int randint(int min, int max);
std::string read_file(const char* path);

namespace config{
    bool init();
    const char* load_data(const char* section, const char* key, const char* standart);
}
