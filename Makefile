TARGETS = src/main.cpp src/gfx.cpp src/system.cpp src/game/timer.cpp
GLFW_INCLUDE = -Ilib/glfw/include
GLFW_LIB = -Llib/glfw/lib -lglfw3 -lgdi32 -lopengl32
LODE_PNG_INCLUDE = -Ilib/png
LODE_PNG_TARGETS = lib/png/lodepng/lodepng.cpp
CXX = g++
CXXFLAGS = -Wall
EXEC = openjumper

all:
	$(CXX) $(TARGETS) $(CXXFLAGS) $(GLFW_INCLUDE) $(GLFW_LIB) -o $(EXEC)
