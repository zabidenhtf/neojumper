#include "scene.hpp"
#include "../data.hpp"

scene::scene(){
    write_dbg("SCENE", "Scene initialisated");
}

void scene::update(double tick){
    static float radius = 3.0f;
    static float angle = 0.0f;
    angle += tick;
    cam_pos_x = radius * cos(angle);
    cam_pos_z = radius * sin(angle);

    render();
}

void scene::render(){
    int width = 300*gfx::screen_aspect();

    gfx::set_viewport(0,0,screen_width, screen_height);
    gfx::set_ortho(0,0, width,300);

    gfx::enable_texture(data2d::textures[NULL_TEX]);
    gfx::draw_2d_quad(vec2(0, 0), vec2(width, 300),vec4(1,1,1,1));

    gfx::set_camera(vec3(cam_pos_x,3,cam_pos_z), vec3(0,0,0), 90);
    gfx::draw_3d_plane(vec3(0,0,0), vec2(1,1),vec4(1,0,0,1), 0,90,0);
    gfx::draw_3d_plane(vec3(0,0,0), vec2(1,1),vec4(0,1,0,1), 90,0,0);
    gfx::draw_3d_plane(vec3(0,0,0), vec2(1,1),vec4(1,0,1,1), 0,0,90);

    gfx::disable_texture();
}
