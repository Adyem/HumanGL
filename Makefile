# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# SDL2 flags (requires sdl2-config in PATH)
SDL2_CFLAGS = $(shell sdl2-config --cflags)
SDL2_LDFLAGS = $(shell sdl2-config --libs)

# Source and target
SRC = src/main.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = sdl_app

# Default rule
all: $(TARGET)

# Link object files into the final executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET) $(SDL2_LDFLAGS)

# Compile .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(SDL2_CFLAGS) -c $< -o $@

# Remove object files
clean:
	rm -f $(OBJ)

# Remove object files and executable
fclean: clean
	rm -f $(TARGET)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
