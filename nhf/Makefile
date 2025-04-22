# Compiler, és flagek, 11-es c++ standarddal, és bekapcsolt memtrace-el
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -DMEMTRACE

# mappák a forráskódnak, objektumoknak, és binárisnak, hogy átlátható maradjon
SRC_DIR = src
OBJ_DIR = src
BIN_DIR = src

#a forráskódok kiejelölése és konvertálása .o néven objektumokká, 
#azért kell hogy a compile time tudja a g++ miket akart binárisba összerakni
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(OBJ_DIR)/memtrace.o $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(filter-out $(SRC_DIR)/memtrace.cpp, $(SRCS)))

# célfile
TARGET = $(BIN_DIR)/teszt

# megcsinálja a mappát neki ha nincs még, és utána egyesével compilelol elősször .o majd .exe-be
all: create_dirs $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Megcsinálja a mappákat
create_dirs:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

# takarítás
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

# futtatás
run: all
	./$(TARGET)
