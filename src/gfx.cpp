#include "interface.hpp"
#include "data.hpp"

GLFWwindow *root = nullptr;
GLuint shader2D; // 2D stuff
GLuint shader3D; // 3D stuff
// Camera
vec3 cam_pos = vec3(0.0f,0.0f,3.0f);
vec3 cam_look = vec3(0,0,0);
vec3 cam_up = vec3(0,1,0);

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
    // Loading window data using config
    string buffer = "Zlib version - " + string(zlibVersion());
    write_dbg("GFX", buffer);
    if (glfwInit()){
        write_dbg("GFX", "GLFW initialisated");
    }
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    if (fullscreen == "True"){
        root = glfwCreateWindow(screen_width, screen_height, "Openjumper", glfwGetPrimaryMonitor(), NULL);
    }
    else{
        root = glfwCreateWindow(screen_width, screen_height, "Openjumper", NULL, NULL);
    }

    if (!root){
        write_dbg("GFX", "Failed to create window");
    }
    glfwMakeContextCurrent(root);

    if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        write_dbg("GFX", "GLAD initialisated");
    } else {
        write_dbg("GFX", "Failed to initialize GLAD");
        return;
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

    vertex2D quad_vertices_3d[4] = {
        {{-0.5f, -0.5f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f}, {0.0f, 1.0f}}
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

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex2D), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex2D), (void*)offsetof(vertex2D, tex));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
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

texture gfx::load_texture(const string &filename)
{
    texture txture;
    std::vector<unsigned char> image;
    unsigned int w, h;
    unsigned error = lodepng::decode(image, w, h, filename.c_str()); // decompiling with

    // if image not found

    txture.width  = (int)w;
    txture.height = (int)h;

    if (error)
    {
        string buffer = "Failed to open " + filename + " image";
        write_dbg("GFX", buffer);
    }
    else{
        string buffer = "Opened " + filename + " image";
        write_dbg("GFX", buffer);
    }

    glGenTextures(1, &txture.texture_id);
    glBindTexture(GL_TEXTURE_2D, txture.texture_id);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Maybe im change to GL_LINEAR_NEARLEST_LINEAR
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, txture.width, txture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());

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

    glUniformMatrix4fv(glGetUniformLocation(shader3D, "projection"),
                   1, GL_FALSE, glm::value_ptr(proj3D));
    glUniformMatrix4fv(glGetUniformLocation(shader3D, "view"),
                   1, GL_FALSE, glm::value_ptr(view3D));
}

void gfx::draw_3d_plane(vec3 pos, vec2 size, vec4 color, double pitch, double yaw, double roll) {
    glEnable(GL_DEPTH_TEST);
    glUseProgram(shader3D);

    glUniform4f(glGetUniformLocation(shader3D, "uColor"),
                color.x, color.y, color.z, color.w);

    float r_pitch = radians(pitch);
    float r_yaw   = radians(yaw);
    float r_roll  = radians(roll);

    mat4 model = mat4(1.0f);
    model = translate(model, pos);
    model = rotate(model, r_roll, vec3(0, 0, 1));
    model = rotate(model, r_yaw,   vec3(1, 0, 0));
    model = rotate(model, r_pitch, vec3(0, 1, 0));
    model = scale(model, vec3(size.x, size.y, 1.0f));

    glUniformMatrix4fv(glGetUniformLocation(shader3D, "model"), 1, GL_FALSE, value_ptr(model));

    glBindVertexArray(quad3dVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void gfx::draw_3d_box(vec3 pos, vec3 size, vec4 color) {
    vec3 half = size * 0.5f;
    draw_3d_plane(pos + vec3(0,-half.y,0), vec2(size.x, size.z), color, 0, 90, 0); // bottom
    draw_3d_plane(pos + vec3(0,half.y,0), vec2(size.x, size.z), vec4(0,0,1,1), 0, 90, 0); // top
    draw_3d_plane(pos + vec3(0,0,half.z), vec2(size.x, size.y), vec4(1,0,1,1), 0, 0, 0); // front
    draw_3d_plane(pos + vec3(0,0,-half.z), vec2(size.x, size.y), vec4(1,1,0,1), 0, 0, 0); // back
    draw_3d_plane(pos + vec3(-half.x,0,0), vec2(size.z, size.y), vec4(0,1,0,1), 90, 0, 0); // left
    draw_3d_plane(pos + vec3(half.x,0,0), vec2(size.z, size.y), vec4(0,1,1,1), 90, 0, 0); // right
}

void gfx::draw_skybox(){
    vec3 size = vec3(16,16,16);
    vec3 half = size * 0.5f;

    enable_texture(data2d::textures[SKYBOX_DOWN]);
    draw_3d_plane(cam_pos + vec3(0,-half.y,0), vec2(size.x, size.z), vec4(1,1,1,1), 0, 90, 180); // bottom
    enable_texture(data2d::textures[SKYBOX_UP]);
    draw_3d_plane(cam_pos + vec3(0,half.y,0), vec2(size.x, size.z), vec4(1,1,1,1), 0, 90, 180); // top
    enable_texture(data2d::textures[SKYBOX_FRONT]);
    draw_3d_plane(cam_pos + vec3(0,0,half.z), vec2(size.x, size.y), vec4(1,1,1,1), 0, 0, 180); // front
    enable_texture(data2d::textures[SKYBOX_BACK]);
    draw_3d_plane(cam_pos + vec3(0,0,-half.z), vec2(size.x, size.y), vec4(1,1,1,1), 0, 180, 0); // back
    enable_texture(data2d::textures[SKYBOX_LEFT]);
    draw_3d_plane(cam_pos + vec3(-half.x,0,0), vec2(size.z, size.y), vec4(1,1,1,1), 90, 0, 180); // left
    enable_texture(data2d::textures[SKYBOX_RIGHT]);
    draw_3d_plane(cam_pos + vec3(half.x,0,0), vec2(size.z, size.y), vec4(1,1,1,1), 90, 180, 0); // right
    disable_texture();
}
