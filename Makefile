TARGETS = $(wildcard src/*.cpp)
GAME_TARGETS = $(wildcard src/game/*.cpp)
SCENE_TARGETS = $(wildcard src/scene/*.cpp)

GLFW_INCLUDE = -Ilib/glfw/include

GLFW_LIB_WINDOWS = -Llib/glfw/lib -lglfw3 -lgdi32 -lopengl32
GLFW_LIB_LINUX = -lglfw -lGL -lGLU -lX11 -lpthread -lrt -l dl

FREETYPE_INCLUDE = -Ilib/freetype/include
FREETYPE_LIB_WINDOWS = -Llib/freetype/lib -lfreetype
FREETYPE_LIB_LINUX = -lfreetype

BINARIES_GLFW_WIN64 = lib/bin/win64/glfw3.dll
BINARIES_GLFW_WIN32 = lib/bin/win32/glfw3.dll 

GLM_INCLUDE = -Ilib/glm

SIMPLE_INI_INCLUDE = -Ilib/simpleini

LODE_PNG_INCLUDE = -Ilib/png
LODE_PNG_TARGETS = lib/png/lodepng/lodepng.cpp

GLAD_INCLUDE = -Ilib/glad/include
GLAD_TARGETS = lib/glad/src/glad.c

CXX = g++
CXXFLAGS = -Wall -g -O0
EXEC = openjumper

all:
ifdef PLATFORM
ifeq ($(PLATFORM),WINDOWS)
	$(CXX) $(TARGETS) $(GAME_TARGETS) $(SCENE_TARGETS) $(CXXFLAGS) \
	$(GLFW_INCLUDE) $(GLFW_LIB_WINDOWS) \
	$(FREETYPE_INCLUDE) $(FREETYPE_LIB_WINDOWS) \
	$(LODE_PNG_INCLUDE) $(LODE_PNG_TARGETS) \
	$(GLM_INCLUDE)  \
	$(GLAD_INCLUDE) $(GLAD_TARGETS) \
	$(SIMPLE_INI_INCLUDE) \
	-o $(EXEC)
	cmd copy $(BINARIES_GLFW_WIN64) %CD%

else ifeq ($(PLATFORM),LINUX)
	$(CXX) $(TARGETS) $(GAME_TARGETS) $(SCENE_TARGETS) $(CXXFLAGS) \
	$(GLFW_INCLUDE) $(GLFW_LIB_LINUX) \
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
