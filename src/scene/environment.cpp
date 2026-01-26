/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "environment.hpp"
#include "scene.hpp"
#include "../game/game.hpp"
#include "data.hpp"

scene_environment::scene_environment(){
    write_dbg("ENVIRONMENT", "Environment initialisated");
}

void scene_environment::reset(){
    cam_pos_x = 4;
    cam_pos_z = 4;
}

void scene_environment::update(double tick){
    static float radius = 4.0f;
    // When warmup spin camera
    if (game->game_started == false){
        static float angle = 0.0f;
        float period = WARMUP_TIME;
        float angular_speed = 2.0f * 3.1415926f / period;

        angle += angular_speed * tick;
        cam_pos_x = radius * cos(angle);
        cam_pos_z = radius * sin(angle);
    }
    else{
        cam_pos_x = radius * cos(360);
        cam_pos_z = radius * sin(360);
    }

    render();
}
void scene_environment::render(){
    gfx::set_light(vec3(3,3,3), vec3(0,0,0), vec4(1,1,1,1));
    gfx::draw_skybox();
    gfx::enable_texture(data2d::textures[NULL_TEX]);
    gfx::set_camera(vec3(cam_pos_x,2,cam_pos_z), vec3(0,0,0), fov);
    gfx::draw_3d_plane(vec3(scene->scene_pos.x,0,scene->scene_pos.y), scene->scene_size,vec4(1,0,0,1), 0,90,0);

    // Debug model render
    model3D teapot = gfx::load_model("assets/models/teapot/teapot.obj");
    gfx::draw_3d_model(teapot ,vec3(2,1.3,2),vec3(1,1,1), vec4(0,1,0,1), 0,0,0);
}
