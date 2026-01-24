/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "interface.hpp"
#include "data.hpp"

GLFWwindow *root = nullptr;
GLuint shader2D; // 2D stuff
GLuint shader3D; // 3D stuff

// Camera
vec3 cam_pos = vec3(0,0,0);
vec3 cam_look = vec3(0,0,0);
vec3 cam_up = vec3(0,1,0);

// Lighting
vec3 light_pos = vec3(16,16,16);
vec3 light_look = vec3(0,0,0);

Assimp::Importer importer; // Now assimp do nothing, but im fix it

// FT stuff
FT_Library    library;
FT_Face       face;
FT_GlyphSlot  slot;
FT_Matrix     matrix;
FT_Vector     pen;
FT_Error      error;

GLuint quadVAO, quadVBO, quadEBO;
GLuint quad3dVAO, quad3dVBO, quad3dEBO;

// For render and native mod
GLFWwindow *gfx::get_window(){
    return root;
}

void gfx::set_ortho(int x, int y, int w, int h){
    glUseProgram(shader2D);
    mat4 proj2D = ortho<float>(x, x + w, y + h, y);
    mat4 view2D = mat4(1.0f);
    glUniformMatrix4fv(glGetUniformLocation(shader2D, "projection"),
                   1, GL_FALSE, value_ptr(proj2D));
    glUniformMatrix4fv(glGetUniformLocation(shader2D, "view"),
                   1, GL_FALSE, value_ptr(view2D));
}

void gfx::set_viewport(int x, int y, int w, int h){
    glViewport(x, y, w, h);
}

void gfx::init(){
    // GLFW initialisation
    if (glfwInit()){
        write_dbg("GFX", "GLFW initialisated");
    }
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    if (fullscreen == "True"){
        root = glfwCreateWindow(screen_width, screen_height, "Neojumper", glfwGetPrimaryMonitor(), NULL);
    }
    else{
        root = glfwCreateWindow(screen_width, screen_height, "Neojumper", NULL, NULL);
    }

    if (!root){
        write_dbg("GFX", "Failed to create window");
    }
    glfwMakeContextCurrent(root);

    // GLAD initialisation
    if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        write_dbg("GFX", "GLAD initialisated");
    } else {
        write_dbg("GFX", "Failed to initialize GLAD");
        return;
    }
    error = FT_Init_FreeType(&library);

    // Freetype initialisation
    if (!error){
        write_dbg("GFX", "Freetype intialisated");
    }
    else{
        write_dbg("GFX", "Failed to initialisate Freetype");
    }

    shader2D = glCreateProgram();
    shader3D = glCreateProgram();

    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LESS);
    // After window init stuff 2D shaders stuff (because GL 3.3) (yep, a bit of AI code here)
    string vertex2d_shader_source = read_file("shaders/shader2D.vert");
    string fragment2d_shader_source = read_file("shaders/shader2D.frag");

    GLuint vertex2d_shader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertex2d_shader_source_cstring = vertex2d_shader_source.c_str();
    glShaderSource(vertex2d_shader, 1, &vertex2d_shader_source_cstring, nullptr);
    glCompileShader(vertex2d_shader); // Vertex 2D shader

    GLuint fragment2d_shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragment2d_shader_source_cstring = fragment2d_shader_source.c_str();
    glShaderSource(fragment2d_shader, 1, &fragment2d_shader_source_cstring, nullptr);
    glCompileShader(fragment2d_shader); // Fragment 2D shader

    glAttachShader(shader2D, vertex2d_shader);
    glAttachShader(shader2D, fragment2d_shader);

    glLinkProgram(shader2D);
    // 3D stuff
    string vertex3d_shader_source = read_file("shaders/shader3D.vert");
    string fragment3d_shader_source = read_file("shaders/shader3D.frag");

    GLuint vertex3d_shader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertex3d_shader_source_cstring = vertex3d_shader_source.c_str();
    glShaderSource(vertex3d_shader, 1, &vertex3d_shader_source_cstring, nullptr);
    glCompileShader(vertex3d_shader); // Vertex 3D shader

    GLuint fragment3d_shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragment3d_shader_source_cstring = fragment3d_shader_source.c_str();
    glShaderSource(fragment3d_shader, 1, &fragment3d_shader_source_cstring, nullptr);
    glCompileShader(fragment3d_shader); // Fragment 3D shader

    glAttachShader(shader3D, vertex3d_shader);
    glAttachShader(shader3D, fragment3d_shader);

    glLinkProgram(shader3D);

    // Quad draw
    vertex2D quad_vertices[4] = {
    {{0.0f, 0.0f}, {0.0f, 0.0f}},
    {{1.0f, 0.0f}, {1.0f, 0.0f}},
    {{1.0f, 1.0f}, {1.0f, 1.0f}},
    {{0.0f, 1.0f}, {0.0f, 1.0f}}
    };

    vertex3D quad_vertices_3d[4] = {
        {{-0.5f, -0.5f, 0.0f}, {0.0f,0.0f}, {0,0,1}},
        {{ 0.5f, -0.5f, 0.0f}, {1.0f,0.0f}, {0,0,1}},
        {{ 0.5f,  0.5f, 0.0f}, {1.0f,1.0f}, {0,0,1}},
        {{-0.5f,  0.5f, 0.0f}, {0.0f,1.0f}, {0,0,1}}
    };
    unsigned int quadIndices[6] = {0, 1, 2, 2, 3, 0};

    // 2D quads, to bottom right
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glGenBuffers(1, &quadEBO);

    glBindVertexArray(quadVAO);

    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), quad_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex2D), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex2D), (void*)offsetof(vertex2D, tex));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    // 3D quads from center
    glGenVertexArrays(1, &quad3dVAO);
    glGenBuffers(1, &quad3dVBO);
    glGenBuffers(1, &quad3dEBO);

    glBindVertexArray(quad3dVAO);

    glBindBuffer(GL_ARRAY_BUFFER, quad3dVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices_3d), quad_vertices_3d, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad3dEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex3D), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex3D), (void*)offsetof(vertex3D, tex));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertex3D), (void*)offsetof(vertex3D, normal));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void gfx::load_font(string path, int id){
    // Creating face
    error = FT_New_Face(library, path.c_str(), 0, &face);

    if (!error){
        write_dbg("GFX", "Loaded "+path+" font");
    }
    else{
        write_dbg("GFX", "Failed to load font");
    }
}

void gfx::swap(){
    glfwPollEvents();
    glfwSwapBuffers(root);
}

void gfx::clear(double r, double g, double b){
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void gfx::draw_2d_quad(vec2 pos, vec2 size, vec4 color){
    glDisable(GL_DEPTH_TEST);
    glUseProgram(shader2D);

    glUniform4f(glGetUniformLocation(shader2D, "uColor"),
                color.x, color.y, color.z, color.w);

    mat4 model = translate(mat4(1.0f), vec3(pos, 0.0f));
    model = scale(model, vec3(size, 1.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader2D, "model"), 1, GL_FALSE, value_ptr(model));

    // VAO/VBO/EBO
    glBindVertexArray(quadVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void gfx::draw_2d_text(vec2 pos, int text_size, int text_resolution, string text, vec4 color){
    for (int i = 0; i<text.length(); i++){
        FT_Set_Pixel_Sizes(face, 0, text_resolution);
        // rendering char
        FT_Load_Char(face, text[i], FT_LOAD_RENDER);
        FT_GlyphSlot g = face->glyph;
        // Generating texture
        texture char_texture;
        glGenTextures(1, &char_texture.texture_id);
        glBindTexture(GL_TEXTURE_2D, char_texture.texture_id);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            g->bitmap.width,
            g->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            g->bitmap.buffer
        );
        // Texture params 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_ONE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_ONE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_ONE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_RED);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Finally render (with size)
        FT_Set_Pixel_Sizes(face, 0, text_size);
        FT_Load_Char(face, text[i], FT_LOAD_RENDER);
        g = face->glyph; // Updating glyph to get correct sizes

        int x = g->bitmap_left;
        int y = g->bitmap_top;
        int w = g->bitmap.width;
        int h = g->bitmap.rows;

        gfx::enable_texture(char_texture);
        gfx::draw_2d_quad(pos + vec2(x+i*text_size/1.5,-y+text_size), vec2(w,h), color);
        gfx::disable_texture();
    }
}

int gfx::text_2d_width(int text_size, string text){
    return text.length() * text_size/1.5;
}

texture gfx::load_texture(const string &filename)
{
    texture txture = {};

    // Reading PNG
    ifstream file(filename, ios::binary);
    if (!file) {
        write_dbg("GFX", "Failed to open " + filename + " image");
        return txture;
    }
    vector<unsigned char> file_data((istreambuf_iterator<char>(file)),
                                         istreambuf_iterator<char>());
    file.close();

    // Check PNG
    if (file_data.size() < 8 || png_sig_cmp(file_data.data(), 0, 8)) {
        write_dbg("GFX", "File " + filename + " is not a PNG");
        return txture;
    }

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return txture;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) { png_destroy_read_struct(&png_ptr, nullptr, nullptr); return txture; }

    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        write_dbg("GFX", "Error reading PNG " + filename);
        return txture;
    }

    struct MemReader { const unsigned char* data; size_t size; size_t offset; };
    MemReader reader = { file_data.data() + 8, file_data.size() - 8, 0 }; // Signature check
    png_set_sig_bytes(png_ptr, 8);
    // Reading PNG
    auto png_read_from_memory = [](png_structp png_ptr, png_bytep out_bytes, png_size_t byte_count_to_read) {
        MemReader* r = (MemReader*)png_get_io_ptr(png_ptr);
        if (r->offset + byte_count_to_read > r->size)
            png_error(png_ptr, "Read beyond end of buffer");
        memcpy(out_bytes, r->data + r->offset, byte_count_to_read);
        r->offset += byte_count_to_read;
    };

    png_set_read_fn(png_ptr, &reader, png_read_from_memory);
    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);

    txture.width  = png_get_image_width(png_ptr, info_ptr);
    txture.height = png_get_image_height(png_ptr, info_ptr);
    png_byte color_type = png_get_color_type(png_ptr, info_ptr);
    png_byte bit_depth  = png_get_bit_depth(png_ptr, info_ptr);

    if (bit_depth == 16) png_set_strip_16(png_ptr);
    if (color_type == PNG_COLOR_TYPE_PALETTE) png_set_palette_to_rgb(png_ptr);
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) png_set_expand_gray_1_2_4_to_8(png_ptr);
    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) png_set_tRNS_to_alpha(png_ptr);
    if (color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY) png_set_filler(png_ptr, 0xFF, PNG_FILLER_AFTER);
    if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) png_set_gray_to_rgb(png_ptr);

    png_read_update_info(png_ptr, info_ptr);

    std::vector<png_byte> image_data(txture.width * txture.height * 4);
    std::vector<png_bytep> row_pointers(txture.height);
    for (int y = 0; y < txture.height; y++)
        row_pointers[y] = image_data.data() + y * txture.width * 4;

    png_read_image(png_ptr, row_pointers.data());
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

    // GL Textures
    glGenTextures(1, &txture.texture_id);
    glBindTexture(GL_TEXTURE_2D, txture.texture_id);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, txture.width, txture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data.data());

    write_dbg("GFX", "Loaded " + filename + " image");
    return txture;
}

void gfx::enable_texture(texture &txture){
    glUseProgram(shader2D);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, txture.texture_id);
    glUniform1i(glGetUniformLocation(shader2D, "tex"), 0);
}

void gfx::disable_texture(){
    glUseProgram(shader2D);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0); // Nothing
    glUniform1i(glGetUniformLocation(shader2D, "tex"), 0);
}

double gfx::screen_aspect(){
    return static_cast<double>(screen_width) / static_cast<double>(screen_height);;
}

void gfx::blend_normal(){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void gfx::blend_additive(){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
}

void gfx::kill(){
    glfwTerminate();
}

// There is 3D stuff
void gfx::set_camera(vec3 pos, vec3 look_at, double fov){
    glUseProgram(shader3D);
    cam_pos = pos;
    cam_look = look_at;

    mat4 proj3D = glm::perspective(radians(static_cast<float>(fov)), static_cast<float>(gfx::screen_aspect()), 0.1f, 100.0f);
    mat4 view3D = glm::lookAt(cam_pos, cam_look, cam_up);

    glUniformMatrix4fv(glGetUniformLocation(shader3D, "projection"), 1, GL_FALSE, value_ptr(proj3D));
    glUniformMatrix4fv(glGetUniformLocation(shader3D, "view"), 1, GL_FALSE, value_ptr(view3D));
}

void gfx::draw_3d_plane(vec3 pos, vec2 size, vec4 color, double pitch, double yaw, double roll, bool have_lighting) {
    glEnable(GL_DEPTH_TEST);
    glUseProgram(shader3D);

    glUniform1i(glGetUniformLocation(shader3D, "tex"), 0);

    // Shader params
    glUniform4fv(glGetUniformLocation(shader3D, "objectColor"), 1, value_ptr(color));
    glUniform3fv(glGetUniformLocation(shader3D, "lightPos"), 1, value_ptr(light_pos));
    glUniform3fv(glGetUniformLocation(shader3D, "viewPos"), 1, value_ptr(cam_pos));

    int buffer;
    // Bool -> int
    if (have_lighting == true){
        buffer = 1;
    }
    else{
        buffer = 0;
    }

    glUniform1i(glGetUniformLocation(shader3D, "HaveLighting"), buffer);

    // model
    mat4 model = mat4(1.0f);
    model = translate(model, pos);
    model = rotate(model, float(radians(roll)), vec3(0, 0, 1));
    model = rotate(model, float(radians(yaw)), vec3(1, 0, 0));
    model = rotate(model, float(radians(pitch)), vec3(0, 1, 0));
    model = scale(model, vec3(size.x, size.y, 1.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader3D, "model"), 1, GL_FALSE, value_ptr(model));

    // Render
    glBindVertexArray(quad3dVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void gfx::draw_3d_box(vec3 pos, vec3 size, vec4 color) {
    vec3 half = size * 0.5f;
    draw_3d_plane(pos + vec3(0,-half.y,0), vec2(size.x, size.z), color, 0, 90, 0); // bottom
    draw_3d_plane(pos + vec3(0,half.y,0), vec2(size.x, size.z), color, 0, 90, 0); // top
    draw_3d_plane(pos + vec3(0,0,half.z), vec2(size.x, size.y), color, 0, 0, 0); // front
    draw_3d_plane(pos + vec3(0,0,-half.z), vec2(size.x, size.y), color, 0, 0, 0); // back
    draw_3d_plane(pos + vec3(-half.x,0,0), vec2(size.z, size.y), color, 90, 0, 0); // left
    draw_3d_plane(pos + vec3(half.x,0,0), vec2(size.z, size.y), color, 90, 0, 0); // right
}

void gfx::set_light(vec3 pos, vec3 look_at, vec4 color){
    light_pos = pos;
    light_look = look_at;
    // TODO: Add colorfull lighting
}

void gfx::draw_skybox(){
    vec3 size = vec3(16,16,16);
    vec3 half = size * 0.5f;

    enable_texture(data2d::textures[SKYBOX_DOWN]);
    draw_3d_plane(cam_pos + vec3(0,-half.y,0), vec2(size.x, size.z), vec4(1,1,1,1), 0, 90, 180, false); // bottom
    enable_texture(data2d::textures[SKYBOX_UP]);
    draw_3d_plane(cam_pos + vec3(0,half.y,0), vec2(size.x, size.z), vec4(1,1,1,1), 0, 90, 180, false); // top
    enable_texture(data2d::textures[SKYBOX_FRONT]);
    draw_3d_plane(cam_pos + vec3(0,0,half.z), vec2(size.x, size.y), vec4(1,1,1,1), 0, 0, 180, false); // front
    enable_texture(data2d::textures[SKYBOX_BACK]);
    draw_3d_plane(cam_pos + vec3(0,0,-half.z), vec2(size.x, size.y), vec4(1,1,1,1), 0, 180, 0, false); // back
    enable_texture(data2d::textures[SKYBOX_LEFT]);
    draw_3d_plane(cam_pos + vec3(-half.x,0,0), vec2(size.z, size.y), vec4(1,1,1,1), 90, 0, 180, false); // left
    enable_texture(data2d::textures[SKYBOX_RIGHT]);
    draw_3d_plane(cam_pos + vec3(half.x,0,0), vec2(size.z, size.y), vec4(1,1,1,1), 90, 180, 0, false); // right
    disable_texture();
}
