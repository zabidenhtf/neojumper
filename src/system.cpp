#include "system.hpp"
#include <iostream>
#include <random>

void write(string msg){
    cout << msg << "\n";
}

void write_dbg(string about, string msg){
    cout << "[" << about << "] " << msg << "\n";
}

int randint(int min, int max){
    static mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}
