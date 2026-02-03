/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "scene.hpp"

SceneCore::SceneCore(){
    Console.WriteDebug("SCENE", "Scene initialisated");

    Player = new EntityJumper();
    Environment = new SceneEnvironment();
    Reset();
}

void SceneCore::Reset(){
    ScenePosition = vec2(0,0);
    SceneSize = vec2(5,5);
    // Reseting entities and components
    Player->Reset();
    Environment->Reset();
}

void SceneCore::Update(float Tick){
    Environment->Update(Tick);
    Player->Update(Tick);
}
