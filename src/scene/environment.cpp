/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "environment.hpp"

#include "utils/data.hpp"
#include "utils/graphics.hpp"

#include "scene.hpp"
#include "../game/game.hpp"

SceneEnvironment::SceneEnvironment(){
    Console.WriteDebug("ENVIRONMENT", "Environment initialisated");
}

void SceneEnvironment::Reset(){
    cam_pos_x = 4;
    cam_pos_z = 4;
}

void SceneEnvironment::Update(float Tick){
    static float radius = 4.0f;
    // When warmup spin camera
    if (Game->GameStarted == false){
        static float Angle = 0.0f;
        float period = WARMUP_TIME;
        float AngularSpeed = 2.0f * 3.1415926f / period;

        Angle += AngularSpeed * Tick;
        cam_pos_x = radius * cos(Angle);
        cam_pos_z = radius * sin(Angle);
    }
    else{
        cam_pos_x = radius * cos(360);
        cam_pos_z = radius * sin(360);
    }

    Render();
}
void SceneEnvironment::Render(){
    Graphics->SetLight(vec3(3,3,3), vec3(0,0,0), vec4(1,1,1,1));
    Graphics->DrawSkybox();
    Graphics->EnableTexture(Data->GetTextureByID(NULL_TEX));
    Graphics->SetCamera(vec3(cam_pos_x,2,cam_pos_z), vec3(0,0,0));
    Graphics->DrawPlane(vec3(Scene->ScenePosition.x,0,Scene->ScenePosition.y), Scene->SceneSize,vec4(1,0,0,1), 0,90,0);

    // Debug model render
    GraphicsModel teapot = Data->LoadModel("assets/models/teapot/teapot.obj");
    Graphics->DrawModel(teapot ,vec3(2,1.3,2),vec3(1,1,1), vec4(0,1,0,1), 0,0,0);
}
