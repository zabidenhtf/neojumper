/* Copyright (C) 2025-2026 Mykyta Polishyk */
/* This project is licensed under the GNU General Public License v3.0 or later. */
/* See the LICENSE file for details. */
#include "utils/system.hpp"
#include "utils/data.hpp"

#include "includes.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include <assimp/postprocess.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#pragma once

using namespace glm;

class GraphicsSystem{
public:
	GLFWwindow *GetWindow(){return Root;};
	float GetTime(){return glfwGetTime();};
	GraphicsSystem();
	void CreateWindowAndContext(); // Creating OpenGL context
	bool ShouldWindowClose(); // Interface for glfwShouldClose()
	void SetOrtho(int w, int h); // Set Ortho
	void SetViewport(int w, int h); // Set Viewport
	void LoadFont(string path, int id); // Loading freetype font
	void PollEvents(); // Updating window and polling events
	void ClearScreen(vec3 Color); // Clear screen with Color
	void EnableTexture(GraphicsTexture texture); // Enable texture
	void DisableTexture(); // Disable texture
	float GetScreenAspect(); // Get Screen aspect in float
	void SetBlendNormal(); // Set blending type on normal
	void SetBlendAdditive(); // Set blending type on additive
	// It not in data.cpp because this is basic premitives
	GraphicsModel LoadPlaneModel(); // Loading simple 3D plane model
	GraphicsModel LoadQuadModel(); // Loading simple 2D quad model
	void DrawModel(GraphicsModel Model, vec3 Position, vec3 Size, vec4 Color, float Pitch, float Yaw, float Roll, bool HaveLighting=true); // Draw 3D model
	void DrawPlane(vec3 Position, vec2 Size, vec4 Color, float Pitch, float Yaw, float Roll, bool HaveLighting=true); // Draw 3D plane (aka 3D quad)
	void DrawBox(vec3 Position, vec3 Size, vec4 Color, bool HaveLighting=true); // Draw 3D box
	void DrawQuad(vec2 Position, vec2 Size, vec4 Color); // Draw 2D quad
	void DrawText(vec2 Position, int TextSize, int TextResolution, string Text, vec4 Color); // Draw freetype text
	int GetTextWidth(int TextSize, string Text); // Getting text width in pixels
	void SetLight(vec3 Position, vec3 LookAt, vec4 Color);
	void SetCamera(vec3 Position, vec3 LookAt);
	void DrawSkybox(); // Drawing big box with sky textures around camera
	int GetWidth(){return Width;};
	int GetHeight(){return Height;};
	void Kill();
private:
	GLuint shader2D; // 2D stuff
	GLuint shader3D; // 3D stuff

	GLFWwindow *Root; // Main Window
	// Important models
	GraphicsModel QuadModel;
	GraphicsModel PlaneModel;
	int Width;
	int Height;
	float Fov;
	bool Fullscreen;
	// Camera
	vec3 CameraPos = vec3(0,0,0);
	vec3 CameraLookAt = vec3(0,0,0);
	vec3 CameraUp = vec3(0,1,0);

	// Lighting
	vec3 LightPos = vec3(16,16,16);
	vec3 LightLookAt = vec3(0,0,0);

	// FT stuff
	FT_Library    library;
	FT_Face       face;
	FT_GlyphSlot  slot;
	FT_Matrix     matrix;
	FT_Vector     pen;
	FT_Error      error;
};

extern GraphicsSystem *Graphics; // Global graphics object