CXX=g++
CXXFLAGS=-lsfml-graphics -lsfml-system -lsfml-window -std=c++11 -Iinclude
EXEC=main
BUILD_DIR = $(addprefix build/,$(MODULES)) build
OBJ = build/sprite_pacman.o build/map.o build/affichage_infos.o build/infos.o build/title_screen.o build/main.o

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
