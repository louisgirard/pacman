CXX=g++
CXXFLAGS=-lsfml-graphics -lsfml-audio -lsfml-system -lsfml-window -std=c++11 -Iinclude -g
EXEC=main
BUILD_DIR = $(addprefix build/,$(MODULES)) build
OBJ = build/character.o build/pacman.o build/ghost.o build/astar.o build/maze.o build/map.o build/display_information.o build/information.o build/title_screen.o build/main.o

all: checkdirs $(EXEC)

main: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)
	
build/%.o: src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(EXEC)
