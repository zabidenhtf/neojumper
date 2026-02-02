/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "graphics.hpp"
#include "data.hpp"

#include <png.h>

GraphicsSystem *Graphics; // Global graphics object

GraphicsSystem::GraphicsSystem(){
	Root = nullptr;
	// Setting params
	Width = stoi(string(config::load_data("GFX", "screen_width", "800")));
	Height = stoi(string(config::load_data("GFX", "screen_height", "800")));
	Fov = stoi(string(config::load_data("GFX", "fov", "90")));
	string FullscreenBuffer = string(config::load_data("GFX", "fullscreen", "False"));
	if (FullscreenBuffer == "True"){ // String -> Bool
   		Fullscreen = true;
    }
    else{
        Fullscreen = false;
    }

    CreateWindowAndContext();

    SetBlendNormal();

    QuadModel = LoadQuadModel();
	PlaneModel = LoadPlaneModel();
}

void GraphicsSystem::CreateWindowAndContext(){
    // GLFW initialization
	if (glfwInit()){
        write_dbg("GFX", "GLFW initialisated");
    }

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	// Creating window
	switch (Fullscreen){
		case true:
			Root = glfwCreateWindow(Width, Height, "Neojumper", glfwGetPrimaryMonitor(), NULL);
			break;
		case false:
			Root = glfwCreateWindow(Width, Height, "Neojumper", NULL, NULL);
			break;
	}
	if (!Root){
		write_dbg("GFX", "Failed to create window");
	}
    glfwMakeContextCurrent(Root);
    // GLAD initialization
    if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        write_dbg("GFX", "GLAD initialisated");
    } 
    else {
        write_dbg("GFX", "Failed to initialize GLAD");
        return;
    }

    error = FT_Init_FreeType(&library);

    // Freetype initialization
    if (!error){
        write_dbg("GFX", "Freetype intialisated");
    }
    else{
        write_dbg("GFX", "Failed to initialisate Freetype");
    }

    // Creating shaders
    shader2D = glCreateProgram();
    shader3D = glCreateProgram();

    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LESS);
   	// 2D stuff
    // Reading raw shaders
    string Vertex2DShaderSource = read_file("shaders/shader2D.vert");
    string Fragment2DShaderSource = read_file("shaders/shader2D.frag");

    GLuint Vertex2DShader = glCreateShader(GL_VERTEX_SHADER);
    const char* Vertex2DShaderSource_cstring = Vertex2DShaderSource.c_str();
    glShaderSource(Vertex2DShader, 1, &Vertex2DShaderSource_cstring, nullptr);
    glCompileShader(Vertex2DShader); // Vertex 2D shader

    GLuint Fragment2DShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* Fragment2DShaderSource_cstring = Fragment2DShaderSource.c_str();
    glShaderSource(Fragment2DShader, 1, &Fragment2DShaderSource_cstring, nullptr);
    glCompileShader(Fragment2DShader); // Fragment 2D shader

    // Attaching shaders
    glAttachShader(shader2D, Vertex2DShader);
    glAttachShader(shader2D, Fragment2DShader);
    glLinkProgram(shader2D);

    // 3D stuff
    // Reading raw shaders
    string Vertex3DShaderSource = read_file("shaders/shader3D.vert");
    string Fragment3DShaderSource = read_file("shaders/shader3D.frag");

    GLuint Vertex3DShader = glCreateShader(GL_VERTEX_SHADER);
    const char* Vertex3DShaderSource_cstring = Vertex3DShaderSource.c_str();
    glShaderSource(Vertex3DShader, 1, &Vertex3DShaderSource_cstring, nullptr);
    glCompileShader(Vertex3DShader); // Vertex 3D shader

    GLuint Fragment3DShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* Fragment3DShaderSource_cstring = Fragment3DShaderSource.c_str();
    glShaderSource(Fragment3DShader, 1, &Fragment3DShaderSource_cstring, nullptr);
    glCompileShader(Fragment3DShader); // Fragment 3D shader

    // Attaching shaders
    glAttachShader(shader3D, Vertex3DShader);
    glAttachShader(shader3D, Fragment3DShader);
    glLinkProgram(shader3D);
}

bool GraphicsSystem::ShouldWindowClose(){
	return glfwWindowShouldClose(Root);
}

void GraphicsSystem::SetOrtho(int w, int h){
	// Setting in shader ortho
	glUseProgram(shader2D);
    mat4 proj2D = ortho<float>(0, w, h, 0);
    mat4 view2D = mat4(1.0f);
    // Setting projection mode and view in shaders
    glUniformMatrix4fv(glGetUniformLocation(shader2D, "projection"),
                   1, GL_FALSE, value_ptr(proj2D));
    glUniformMatrix4fv(glGetUniformLocation(shader2D, "view"),
                   1, GL_FALSE, value_ptr(view2D));
}

void GraphicsSystem::SetViewport(int w, int h){
	glViewport(0, 0, w, h);
}

void GraphicsSystem::LoadFont(string path, int id){
    // Creating face
    error = FT_New_Face(library, path.c_str(), 0, &face);
    
    // If error returning
    if (!error){
        write_dbg("GFX", "Loaded "+path+" font");
    }
    else{
        write_dbg("GFX", "Failed to load font");
        return;
    }
}


GraphicsTexture GraphicsSystem::LoadTexture(const string &path)
{
    GraphicsTexture Texture = {};

    // Reading PNG
    ifstream file(path, ios::binary);
    if (!file) {
        write_dbg("GFX", "Failed to open " + path + " image");
        return Texture;
    }
    vector<unsigned char> file_data((istreambuf_iterator<char>(file)),
                                         istreambuf_iterator<char>());
    file.close();

    // Check PNG
    if (file_data.size() < 8 || png_sig_cmp(file_data.data(), 0, 8)) {
        write_dbg("GFX", "File " + path + " is not a PNG");
        return Texture;
    }

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return Texture;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) { png_destroy_read_struct(&png_ptr, nullptr, nullptr); return Texture; }

    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        write_dbg("GFX", "Error reading PNG " + path);
        return Texture;
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

    // Setting image paramgs
    Texture.Width  = png_get_image_width(png_ptr, info_ptr);
    Texture.Height = png_get_image_height(png_ptr, info_ptr);
    png_byte color_type = png_get_color_type(png_ptr, info_ptr);
    png_byte bit_depth  = png_get_bit_depth(png_ptr, info_ptr);

    if (bit_depth == 16) png_set_strip_16(png_ptr);
    if (color_type == PNG_COLOR_TYPE_PALETTE) png_set_palette_to_rgb(png_ptr);
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) png_set_expand_gray_1_2_4_to_8(png_ptr);
    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) png_set_tRNS_to_alpha(png_ptr);
    if (color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY) png_set_filler(png_ptr, 0xFF, PNG_FILLER_AFTER);
    if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) png_set_gray_to_rgb(png_ptr);

    png_read_update_info(png_ptr, info_ptr);

    vector<png_byte> image_data(Texture.Width * Texture.Height * 4);
    vector<png_bytep> row_pointers(Texture.Height);
    for (int y = 0; y < Texture.Height; y++)
        row_pointers[y] = image_data.data() + y * Texture.Width * 4;

    png_read_image(png_ptr, row_pointers.data());
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

    // Creating GL texture
    glGenTextures(1, &Texture.Raw);
    glBindTexture(GL_TEXTURE_2D, Texture.Raw);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Texture.Width, Texture.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data.data());

    write_dbg("GFX", "Loaded " + path + " image");
    return Texture;
}

void GraphicsSystem::PollEvents(){
	glfwPollEvents();
    glfwSwapBuffers(Root);
}

void GraphicsSystem::ClearScreen(vec3 Color){
	// Just cleaning with color
	glClearColor(Color.x, Color.y, Color.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GraphicsSystem::EnableTexture(GraphicsTexture texture){
    glUseProgram(shader2D);
    glActiveTexture(GL_TEXTURE0);
    // Binding texture from argument
    glBindTexture(GL_TEXTURE_2D, texture.Raw);
    glUniform1i(glGetUniformLocation(shader2D, "tex"), 0);
}
void GraphicsSystem::DisableTexture(){
	glUseProgram(shader2D);
    glActiveTexture(GL_TEXTURE0);
    // Binding NOTHING
    glBindTexture(GL_TEXTURE_2D, 0);
    glUniform1i(glGetUniformLocation(shader2D, "tex"), 0);
}

float GraphicsSystem::GetScreenAspect(){
    return static_cast<float>(Width) / static_cast<float>(Height);
}

void GraphicsSystem::SetBlendNormal(){
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void GraphicsSystem::SetBlendAdditive(){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
}

GraphicsModel GraphicsSystem::LoadPlaneModel(){
	GraphicsModel Buffer; // Buffer to return

	// Vertices of plane
	vertex3D PlaneVertices[4] = {
        {{-0.5f, -0.5f, 0.0f}, {0.0f,0.0f}, {0,0,1}},
        {{ 0.5f, -0.5f, 0.0f}, {1.0f,0.0f}, {0,0,1}},
        {{ 0.5f,  0.5f, 0.0f}, {1.0f,1.0f}, {0,0,1}},
        {{-0.5f,  0.5f, 0.0f}, {0.0f,1.0f}, {0,0,1}}
    };
    GLuint quadIndices[6] = {0, 1, 2, 2, 3, 0};

    // Binding buffers
    glGenVertexArrays(1, &Buffer.VAO);
    glGenBuffers(1, &Buffer.VBO);
    glGenBuffers(1, &Buffer.EBO);

    glBindVertexArray(Buffer.VAO);

    // Setting up data into VBO and EBO
    glBindBuffer(GL_ARRAY_BUFFER, Buffer.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(PlaneVertices), PlaneVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffer.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex3D), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex3D), (void*)offsetof(vertex3D, TexturePos));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertex3D), (void*)offsetof(vertex3D, Normal));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0); // Unbinding arrays and buffers

    return Buffer;
}

GraphicsModel GraphicsSystem::LoadQuadModel(){
	GraphicsModel Buffer; // Buffer to return

	// Vertices of plane
    vertex2D QuadVertices[4] = {
	    {{0.0f, 0.0f}, {0.0f, 0.0f}},
	    {{1.0f, 0.0f}, {1.0f, 0.0f}},
	    {{1.0f, 1.0f}, {1.0f, 1.0f}},
	    {{0.0f, 1.0f}, {0.0f, 1.0f}}
    };
    GLuint quadIndices[6] = {0, 1, 2, 2, 3, 0};

    // Binding buffers
    glGenVertexArrays(1, &Buffer.VAO);
    glGenBuffers(1, &Buffer.VBO);
    glGenBuffers(1, &Buffer.EBO);

    glBindVertexArray(Buffer.VAO);

    glBindVertexArray(Buffer.VAO);

    // Setting up data into VBO and EBO
    glBindBuffer(GL_ARRAY_BUFFER, Buffer.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(QuadVertices), QuadVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffer.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex2D), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex2D), (void*)offsetof(vertex2D, TexturePos));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbinding arrays and buffers

    return Buffer;
}

GraphicsModel GraphicsSystem::LoadModel(const string path){
	GraphicsModel Buffer;
    
    vector<vertex3D> vertices;
    vector<GLuint> indices;

    // Creating VAO
    glGenVertexArrays(1, &Buffer.VAO);
    glBindVertexArray(Buffer.VAO);
    glGenBuffers(1, &Buffer.VBO);
    glGenBuffers(1, &Buffer.EBO);

    glBindVertexArray(Buffer.VAO);

    // Reading model
    const aiScene* scene = importer.ReadFile(path.c_str(), aiProcess_Triangulate);
    aiMesh* mesh;
    if (scene){
        mesh = scene->mMeshes[0];
    }
    else{
        write_dbg("GFX", "Failed to parsing model");
        return Buffer;
    }
    // Put mesh's vertices into vertices vector
    for(GLuint i = 0; i < mesh->mNumVertices; i++){
        vertex3D vertex_buff;
        vertex_buff.Position = vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z); // Writing position
        if (mesh->HasNormals()){
            vertex_buff.Normal = vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z); // Writing normals
        }
        if (mesh->mTextureCoords[0]){
            vertex_buff.TexturePos = vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y); // Writing texture coords
        }
        vertices.push_back(vertex_buff);
    }
    // Put mesh's faces into indices vector
    for (GLuint i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (GLuint j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    glBindBuffer(GL_ARRAY_BUFFER, Buffer.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex3D), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffer.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex3D), (void*)0);
    // Normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex3D), (void*)offsetof(vertex3D, Normal));
    // TexCoords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex3D), (void*)offsetof(vertex3D, TexturePos));

    // Closing
    glBindVertexArray(0);
    return Buffer;
}

void GraphicsSystem::DrawModel(GraphicsModel Model, vec3 Position, vec3 Size, vec4 Color, float Pitch, float Yaw, float Roll, bool HaveLighting){
	glEnable(GL_DEPTH_TEST);
    glUseProgram(shader3D);

    glUniform1i(glGetUniformLocation(shader3D, "tex"), 0);

    // Shader params
    glUniform4fv(glGetUniformLocation(shader3D, "objectColor"), 1, value_ptr(Color));
    glUniform3fv(glGetUniformLocation(shader3D, "lightPos"), 1, value_ptr(LightPos));
    glUniform3fv(glGetUniformLocation(shader3D, "viewPos"), 1, value_ptr(CameraPos));

    int LightingBuffer;
    // Bool -> int
    if (HaveLighting == true){
        LightingBuffer = 1;
    }
    else{
        LightingBuffer = 0;
    }

    // Setting lighting params
    glUniform1i(glGetUniformLocation(shader3D, "HaveLighting"), LightingBuffer);

    // model
    mat4 model = mat4(1.0f);
    model = translate(model, Position);
    // Rotating
    model = rotate(model, float(radians(Roll)), vec3(0, 0, 1));
    model = rotate(model, float(radians(Yaw)), vec3(1, 0, 0));
    model = rotate(model, float(radians(Pitch)), vec3(0, 1, 0));
    // Scaling
    model = scale(model, Size);
    glUniformMatrix4fv(glGetUniformLocation(shader3D, "model"), 1, GL_FALSE, value_ptr(model));

    // Rendering
    glBindVertexArray(Model.VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void GraphicsSystem::DrawPlane(vec3 Position, vec2 Size, vec4 Color, float Pitch, float Yaw, float Roll, bool HaveLighting){
	glEnable(GL_DEPTH_TEST);
    glUseProgram(shader3D);

    glUniform1i(glGetUniformLocation(shader3D, "tex"), 0);

    // Shader params
    glUniform4fv(glGetUniformLocation(shader3D, "objectColor"), 1, value_ptr(Color));
    glUniform3fv(glGetUniformLocation(shader3D, "lightPos"), 1, value_ptr(LightPos));
    glUniform3fv(glGetUniformLocation(shader3D, "viewPos"), 1, value_ptr(CameraPos));

    int buffer;
    // Bool -> int
    if (HaveLighting == true){
        buffer = 1;
    }
    else{
        buffer = 0;
    }

    // Shader lighting params
    glUniform1i(glGetUniformLocation(shader3D, "HaveLighting"), buffer);

    // model
    mat4 model = mat4(1.0f);
    model = translate(model, Position);
    // Rotating
    model = rotate(model, float(radians(Roll)), vec3(0, 0, 1));
    model = rotate(model, float(radians(Yaw)), vec3(1, 0, 0));
    model = rotate(model, float(radians(Pitch)), vec3(0, 1, 0));
    // Scaling
    model = scale(model, vec3(Size.x, Size.y, 1.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader3D, "model"), 1, GL_FALSE, value_ptr(model));

    // Rendering
    glBindVertexArray(PlaneModel.VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void GraphicsSystem::DrawBox(vec3 Position, vec3 Size, vec4 Color, bool HaveLighting){
	vec3 half = Size * 0.5f;
    DrawPlane(Position + vec3(0,-half.y,0), vec2(Size.x, Size.z), Color, 0, 90, 0, HaveLighting); // bottom
    DrawPlane(Position + vec3(0,half.y,0), vec2(Size.x, Size.z), Color, 0, 90, 0, HaveLighting); // top
    DrawPlane(Position + vec3(0,0,half.z), vec2(Size.x, Size.y), Color, 0, 0, 0, HaveLighting); // front
    DrawPlane(Position + vec3(0,0,-half.z), vec2(Size.x, Size.y), Color, 0, 0, 0, HaveLighting); // back
    DrawPlane(Position + vec3(-half.x,0,0), vec2(Size.z, Size.y), Color, 90, 0, 0, HaveLighting); // left
    DrawPlane(Position + vec3(half.x,0,0), vec2(Size.z, Size.y), Color, 90, 0, 0, HaveLighting); // right
}

void GraphicsSystem::DrawQuad(vec2 Position, vec2 Size, vec4 Color){
	glDisable(GL_DEPTH_TEST);
    glUseProgram(shader2D);

    glUniform4f(glGetUniformLocation(shader2D, "uColor"),
                Color.x, Color.y, Color.z, Color.w);

    mat4 model = translate(mat4(1.0f), vec3(Position, 0.0f));
    // Scaling
    model = scale(model, vec3(Size, 1.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader2D, "model"), 1, GL_FALSE, value_ptr(model));

    // Rendering
    glBindVertexArray(QuadModel.VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void GraphicsSystem::DrawText(vec2 Position, int TextSize, int TextResolution, string Text, vec4 Color){
	for (int i = 0; i<Text.length(); i++){ // Drawing each char of string
        FT_Set_Pixel_Sizes(face, 0, TextResolution);
        // rendering char
        FT_Load_Char(face, Text[i], FT_LOAD_RENDER);
        FT_GlyphSlot g = face->glyph;
        // Generating texture
        GraphicsTexture CharTexture;
        glGenTextures(1, &CharTexture.Raw);
        glBindTexture(GL_TEXTURE_2D, CharTexture.Raw);
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
        FT_Set_Pixel_Sizes(face, 0, TextSize);
        FT_Load_Char(face, Text[i], FT_LOAD_RENDER);
        g = face->glyph; // Updating glyph to get correct sizes

        int x = g->bitmap_left;
        int y = g->bitmap_top;
        int w = g->bitmap.width;
        int h = g->bitmap.rows;

        EnableTexture(CharTexture);
        DrawQuad(Position + vec2(x+i*TextSize/1.5,-y+TextSize), vec2(w,h), Color);
        DisableTexture();
    }
}

int GraphicsSystem::GetTextWidth(int TextSize, string Text){
    return Text.length() * TextSize/1.5; // TODO: Remove magic numbers
}

void GraphicsSystem::SetCamera(vec3 Position, vec3 LookAt){
	glUseProgram(shader3D); // Enabling shader
    CameraPos = Position;	// Setting position and look point
    CameraLookAt = LookAt;

    mat4 proj3D = glm::perspective(radians(Fov), GetScreenAspect(), 0.1f, 100.0f);
    mat4 view3D = glm::lookAt(CameraPos, CameraLookAt, CameraUp);

    // Setting projection and view into shaders (also converting from GLM vec3 format to float)
    glUniformMatrix4fv(glGetUniformLocation(shader3D, "projection"), 1, GL_FALSE, value_ptr(proj3D));
    glUniformMatrix4fv(glGetUniformLocation(shader3D, "view"), 1, GL_FALSE, value_ptr(view3D));
}

void GraphicsSystem::SetLight(vec3 Position, vec3 LookAt, vec4 Color){
	LightPos = Position;
    LightLookAt = LookAt;
    // TODO: Add colorfull lighting
}

void GraphicsSystem::DrawSkybox(){
    vec3 size = vec3(16,16,16);
    vec3 half = size * 0.5f;

    // Draw sky with sky textures
    EnableTexture(Data->GetTextureByID(SKYBOX_DOWN));
    DrawPlane(CameraPos + vec3(0,-half.y,0), vec2(size.x, size.z), vec4(1,1,1,1), 0, 90, 180, false); // bottom

    EnableTexture(Data->GetTextureByID(SKYBOX_UP));
    DrawPlane(CameraPos + vec3(0,half.y,0), vec2(size.x, size.z), vec4(1,1,1,1), 0, 90, 180, false); // top

    EnableTexture(Data->GetTextureByID(SKYBOX_FRONT));
    DrawPlane(CameraPos + vec3(0,0,half.z), vec2(size.x, size.y), vec4(1,1,1,1), 0, 0, 180, false); // front

    EnableTexture(Data->GetTextureByID(SKYBOX_BACK));
    DrawPlane(CameraPos + vec3(0,0,-half.z), vec2(size.x, size.y), vec4(1,1,1,1), 0, 180, 0, false); // back

    EnableTexture(Data->GetTextureByID(SKYBOX_LEFT));
    DrawPlane(CameraPos + vec3(-half.x,0,0), vec2(size.z, size.y), vec4(1,1,1,1), 90, 0, 180, false); // left

    EnableTexture(Data->GetTextureByID(SKYBOX_RIGHT));
    DrawPlane(CameraPos + vec3(half.x,0,0), vec2(size.z, size.y), vec4(1,1,1,1), 90, 180, 0, false); // right

    DisableTexture();
}

void GraphicsSystem::Kill(){
	// For first destroying window, after terminating GLFW
	glfwDestroyWindow(Root);
	glfwTerminate();
}