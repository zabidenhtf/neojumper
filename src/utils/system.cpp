/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "utils/system.hpp"
// Some STL includes
#include <iostream>
#include <random>
#include <sstream>

ConsoleSystem Console;

/* CONSOLE SYSTEM */
void ConsoleSystem::Write(string Message){
    cout << Message << "\n";
}

void ConsoleSystem::WriteDebug(string Tag, string Message){
    cout << "[" << Tag << "] " << Message << "\n";
}

int RandomInt(int Min, int Max){
    static mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(Min, Max);
    return dist(rng);
}

string ReadFile(string Path){
    ifstream file(Path.c_str());
    stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}
