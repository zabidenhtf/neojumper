TARGETS = src/main.cpp src/gfx.cpp src/system.cpp src/game/warmup.cpp src/game/game.cpp src/scene/scene.cpp src/game/controls.cpp src/input.cpp

GLFW_INCLUDE = -Ilib/glfw/include
GLFW_LIB_WINDOWS = -Llib/glfw/lib -lglfw3 -lgdi32 -lopengl32
GLFW_LIB_LINUX = -lglfw -lGL -lGLU -lX11 -lpthread -lrt -l dl

GLM_INCLUDE = -Ilib/glm

LODE_PNG_INCLUDE = -Ilib/png
LODE_PNG_TARGETS = lib/png/lodepng/lodepng.cpp

GLAD_INCLUDE = -Ilib/glad/include
GLAD_TARGETS = -Ilib/glad/src

CXX = g++
CXXFLAGS = -Wall
EXEC = openjumper

all:
ifdef PLATFORM
ifeq ($(PLATFORM),WINDOWS)
	$(CXX) $(TARGETS) $(CXXFLAGS) $(GLFW_INCLUDE) \
	$(LODE_PNG_INCLUDE) $(LODE_PNG_TARGETS) $(GLM_INCLUDE)  \
	$(GLAD_INCLUDE) $(GLAD_TARGETS) \
	$(GLFW_LIB_WINDOWS) -o $(EXEC)
else ifeq ($(PLATFORM),LINUX)
	$(CXX) $(TARGETS) $(CXXFLAGS) \
	$(LODE_PNG_INCLUDE) $(LODE_PNG_TARGETS) $(GLM_INCLUDE)  \
	$(GLAD_INCLUDE) $(GLAD_TARGETS) \
	$(GLFW_LIB_LINUX) -o $(EXEC)
else
	$(error Platform is unsupported)
endif
else
	$(error there is no Platform defined)
endif
