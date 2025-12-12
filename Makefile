TARGETS = src/main.cpp src/gfx.cpp src/load.cpp src/model.cpp
GLFW_INCLUDE = -Ilib/glfw/include
GLFW_LIB = -Llib/glfw/lib -lglfw3 -lgdi32 -lopengl32
CXX = g++
CXXFLAGS = -Wall
EXEC = openjumper

all:
	$(CXX) $(TARGETS) $(CXXFLAGS) $(GLFW_INCLUDE) $(GLFW_LIB) -o $(EXEC)
