TARGETS = $(wildcard src/*.cpp)
GAME_TARGETS = $(wildcard src/game/*.cpp)
GAME_COMPONENTS_TARGETS = $(wildcard src/game/components/*.cpp)
SCENE_TARGETS = $(wildcard src/scene/*.cpp)
SCENE_ENTITIES_TARGETS = $(wildcard src/scene/entities/*.cpp)
INCLUDES = -Isrc/includes

GLFW_INCLUDE = -Ilib/glfw/include
GLFW_LIB_WIN64 = -Llib/glfw/lib -lglfw3 -lgdi32 -lopengl32
GLFW_LIB_WIN32 = -Llib/glfw/lib32 -lglfw3 -lgdi32 -lopengl32
GLFW_LIB_LINUX = -lglfw -lGL -lGLU -lX11 -lpthread -lrt -l dl

ZLIB_INCLUDE = -Ilib/zlib/include
ZLIB_LIB_WIN64 = -Llib/zlib/lib -lz
ZLIB_LIB_LINUX = -lz

ASSIMP_INCLUDE = -Ilib/assimp/include
ASSIMP_LIB_WIN64 = -Llib/assimp/lib -lassimp

FREETYPE_INCLUDE = -Ilib/freetype/include
FREETYPE_LIB_WIN64 = -Llib/freetype/lib -lfreetype
FREETYPE_LIB_WIN32 = -Llib/freetype/lib32 -lfreetype
FREETYPE_LIB_LINUX = -lfreetype

BINARIES_GLFW_WIN64 = lib/bin/win64/glfw3.dll lib/bin/win64/zlib1.dll lib/bin/win64/libassimp-6.dll
BINARIES_GLFW_WIN32 = lib/bin/win32/glfw3.dll

GLM_INCLUDE = -Ilib/glm

SIMPLE_INI_INCLUDE = -Ilib/simpleini

PNG_INCLUDE = -Ilib/png/include
PNG_LIB_WIN64 = -Llib/png/lib -lpng -lpng16

GLAD_INCLUDE = -Ilib/glad/include
GLAD_TARGETS = lib/glad/src/glad.c

CXX = g++
CXXFLAGS = -Wall -g -O0
EXEC = openjumper

all:
ifdef PLATFORM
ifeq ($(PLATFORM),WIN64)
	$(CXX) $(TARGETS) $(GAME_TARGETS) $(SCENE_TARGETS) $(GAME_COMPONENTS_TARGETS) $(SCENE_ENTITIES_TARGETS) $(INCLUDES) \
	$(CXXFLAGS) \
	$(GLFW_INCLUDE) $(GLFW_LIB_WIN64) \
	$(FREETYPE_INCLUDE) $(FREETYPE_LIB_WIN64) \
	$(ZLIB_INCLUDE) $(ZLIB_LIB_WIN64) \
	$(ASSIMP_INCLUDE) $(ASSIMP_LIB_WIN64) \
	$(PNG_INCLUDE) $(PNG_LIB_WIN64) \
	$(GLM_INCLUDE)  \
	$(GLAD_INCLUDE) $(GLAD_TARGETS) \
	$(SIMPLE_INI_INCLUDE) \
	-o $(EXEC)
else ifeq ($(PLATFORM),WIN32)
	$(CXX) $(TARGETS) $(GAME_TARGETS) $(SCENE_TARGETS) $(GAME_COMPONENTS_TARGETS) $(SCENE_ENTITIES_TARGETS) $(INCLUDES) \
	$(CXXFLAGS) \
	$(GLFW_INCLUDE) $(GLFW_LIB_WIN32) \
	$(FREETYPE_INCLUDE) $(FREETYPE_LIB_WIN32) \
	$(LODE_PNG_INCLUDE) $(LODE_PNG_TARGETS) \
	$(GLM_INCLUDE)  \
	$(GLAD_INCLUDE) $(GLAD_TARGETS) \
	$(SIMPLE_INI_INCLUDE) \
	-o $(EXEC)
else ifeq ($(PLATFORM),LINUX)
	$(CXX) $(TARGETS) $(GAME_TARGETS) $(SCENE_TARGETS) $(GAME_COMPONENTS_TARGETS) $(SCENE_ENTITIES_TARGETS) \
	$(CXXFLAGS) \
	$(GLFW_INCLUDE) $(GLFW_LIB_LINUX) \
	$(ZLIB_INCLUDE) $(ZLIB_LIB_LINUX) \
	$(FREETYPE_INCLUDE) $(FREETYPE_LIB_LINUX) \
	$(LODE_PNG_INCLUDE) $(LODE_PNG_TARGETS) \
	$(GLM_INCLUDE)  \
	$(GLAD_INCLUDE) $(GLAD_TARGETS) \
	$(SIMPLE_INI_INCLUDE) \
	-o $(EXEC)
else
	$(error Platform is unsupported)
endif
else
	$(error there is no Platform defined)
endif
