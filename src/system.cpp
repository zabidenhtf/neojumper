#include "system.hpp"
#include <iostream>

void write(string msg){
    cout << msg << "\n";
}

void write_dbg(string about, string msg){
    cout << "[" << about << "] " << msg << "\n";
}
