/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "scene.hpp"

scene_core::scene_core(){
    write_dbg("SCENE", "Scene initialisated");

    player = new entity_jumper_player();
    environment = new scene_environment();
    reset();
}

void scene_core::reset(){
    scene_pos = vec2(0,0);
    scene_size = vec2(5,5);
    player->reset();
    environment->reset();
}

void scene_core::update(double tick){
    environment->update(tick);
    player->update(tick);
}
