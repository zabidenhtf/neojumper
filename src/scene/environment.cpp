#include "environment.hpp"
#include "data.hpp"

environment::environment(){
    write_dbg("ENVIRONMENT", "Environment initialisated");
    reset();
}

void environment::reset(){
    return;
}

void environment::update(double tick){
    static float radius = 4.0f;
    static float angle = 0.0f;
    angle += tick;
    cam_pos_x = radius * cos(angle);
    cam_pos_z = radius * sin(angle);
    render();
}

void environment::render(){
    gfx::draw_skybox();
    gfx::enable_texture(data2d::textures[NULL_TEX]);
    gfx::set_camera(vec3(cam_pos_x,2,cam_pos_z), vec3(0,0,0), fov);
    gfx::draw_3d_plane(vec3(0,0,0), vec2(5,5),vec4(0,0,0,1), 0,90,0);
}
