# Compiler and Flags
CCXX = g++
PROCESSORS = -j 4
DEBUG_SYMBOLS = -g3
OPT_LEVEL ?= 0
RM = rm -r

# Project Name
NAME = humangl

# Optimization flags based on level
ifeq ($(OPT_LEVEL),0)
	OPT_FLAGS = -O0 $(DEBUG_SYMBOLS)
else ifeq ($(OPT_LEVEL),1)
	OPT_FLAGS = -O1 -flto -s -ffunction-sections -fdata-sections -Wl,--gc-sections
else ifeq ($(OPT_LEVEL),2)
	OPT_FLAGS = -O2 -flto -s -ffunction-sections -fdata-sections -Wl,--gc-sections
else ifeq ($(OPT_LEVEL),3)
	OPT_FLAGS = -O3 -flto -s -ffunction-sections -fdata-sections -Wl,--gc-sections
else
	$(error Unsupported OPT_LEVEL=$(OPT_LEVEL))
endif

# Platform detection
ifeq ($(OS),Windows_NT)
    EXE_EXT := .exe
    MKDIR   = mkdir
    RMDIR   = rmdir /S /Q
    RM_FILE = del /F /Q
else
    EXE_EXT :=
    MKDIR   = mkdir -p
    RMDIR   = rm -rf
    RM_FILE = rm -f
endif

# SDL2 paths (cross-platform)
ifeq ($(OS),Windows_NT)
    SDL2_PREFIX = /usr/local
    INCLUDE_FLAGS = -I$(SDL2_PREFIX)/include
    LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -lopengl32 -lglu32
else ifeq ($(shell uname -s),Darwin)
    # macOS (Homebrew)
    SDL2_PREFIX = $(shell brew --prefix sdl2 2>/dev/null || echo /usr/local)
    INCLUDE_FLAGS = -I$(SDL2_PREFIX)/include
    LDFLAGS = -L$(SDL2_PREFIX)/lib -lSDL2 -framework OpenGL
else
    # Linux
    INCLUDE_FLAGS = $(shell pkg-config --cflags sdl2 2>/dev/null || echo -I/usr/include/SDL2)
    LDFLAGS = $(shell pkg-config --libs sdl2 2>/dev/null || echo -lSDL2) -lGL -lGLU
endif

# Compilation flags
COMPLETE_FLAGS = -Wno-unused-parameter -Wno-missing-field-initializers -Wno-sign-conversion -Wno-unknown-pragmas -Wno-unknown-warning-option \
				 -Wno-unused-function -Wno-unused-variable -Wno-unused-but-set-variable -Wmissing-declarations -Wold-style-cast -Wconversion \
				 -Wformat=2 -Wundef -Wfloat-equal -Wzero-as-null-pointer-constant -Wshadow $(OPT_FLAGS)
FLAGS = -std=c++14 -Wall -Wextra -Werror $(INCLUDE_FLAGS) $(EXTRA_FLAGS) #$(COMPLETE_FLAGS)

# Directories
OBJECTS = objects
OBJECTS_DEBUG = objects_debug
SOURCES = sources
INCLUDES = includes

# Debug mode configuration
DEBUG_MODE ?= 0
ifeq ($(DEBUG_MODE),1)
    OBJ_DIR = $(OBJECTS_DEBUG)
    TARGET_NAME = $(NAME)_debug$(EXE_EXT)
    EXTRA_FLAGS = -DDEBUG=1
else
    OBJ_DIR = $(OBJECTS)
    TARGET_NAME = $(NAME)$(EXE_EXT)
    EXTRA_FLAGS =
endif

# Subdirectories for Source and Header files
APPLICATION_SUBDIRS = Application
HUMAN_SUBDIRS = Human
INPUT_SUBDIRS = Input
MATRIX_SUBDIRS = Matrix
MENUS_SUBDIRS = Menus
SIMULATION_SUBDIRS = Simulation

SUBDIRS = $(APPLICATION_SUBDIRS) $(HUMAN_SUBDIRS) $(INPUT_SUBDIRS) $(MATRIX_SUBDIRS) $(MENUS_SUBDIRS) $(SIMULATION_SUBDIRS)
# PUT IN ALPHABETICAL ORDER
# Header Files (without paths)
APPLICATION_HEADERS = Application.hpp BaseMenu.hpp CreditsMenu.hpp InstructionsMenu.hpp \
					  MainMenu.hpp MenuSystem.hpp SettingsMenu.hpp

HUMAN_HEADERS = Arm.hpp BodyPart.hpp DrawPerson.hpp Head.hpp Leg.hpp Shoulder.hpp

INPUT_HEADERS = KeyboardHandler.hpp MenuInput.hpp MouseHandler.hpp

MATRIX_HEADERS = Matrix4.hpp MatrixStack.hpp

MENUS_HEADERS = CreditsMenuRenderer.hpp InstructionsMenuRenderer.hpp MainMenuRenderer.hpp \
				MenuRenderer.hpp SettingsMenuRenderer.hpp TextRenderer.hpp

SIMULATION_HEADERS = AnimationManager.hpp EventHandler.hpp SimulationRenderer.hpp

# Combine Header Files
HEADERS = $(APPLICATION_HEADERS) $(HUMAN_HEADERS) $(INPUT_HEADERS) $(MATRIX_HEADERS) \
		  $(MENUS_HEADERS) $(SIMULATION_HEADERS)

CSTYLE_HEADERS = humangl.hpp CStyle/defines.hpp CStyle/enums.hpp CStyle/libs.hpp CStyle/structs.hpp

# Generate Source Files by replacing .hpp with .cpp
SUBDIR_SRCS = $(patsubst %.hpp,%.cpp,$(HEADERS))

# Include main.cpp as it's not in a subdirectory
MAIN = main.cpp
SRCS = $(SUBDIR_SRCS) $(MAIN)

# Use vpath to search for sources and headers in the respective subdirectories
vpath %.cpp $(addprefix $(SOURCES)/,$(SUBDIRS)) $(SOURCES)
vpath %.hpp $(addprefix $(INCLUDES)/,$(SUBDIRS)) $(INCLUDES)

# Generate Object File Paths
OBJ_SUBDIRS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SUBDIR_SRCS))
OBJ_MAIN = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(MAIN))
OBJ = $(OBJ_SUBDIRS) $(OBJ_MAIN)

# Rules
all: $(TARGET_NAME)

$(TARGET_NAME): $(OBJ) $(HEADERS) $(addprefix $(INCLUDES)/,$(CSTYLE_HEADERS))
	$(CCXX) $(FLAGS) $(OBJ) -o $(TARGET_NAME) $(LDFLAGS)

$(OBJ_DIR)/%.o: %.cpp
	@$(MKDIR) $(dir $@)
	$(CCXX) $(FLAGS) -c $< -o $@

debug:
	@make all DEBUG_MODE=1 $(PROCESSORS) --no-print-directory 2>/dev/null

clean:
	@test -d $(OBJECTS) && $(RMDIR) $(OBJECTS) && echo "Removed $(OBJECTS)" || echo "$(OBJECTS) does not exist, skipping."
	@test -d $(OBJECTS_DEBUG) && $(RMDIR) $(OBJECTS_DEBUG) && echo "Removed $(OBJECTS_DEBUG)" || echo "$(OBJECTS_DEBUG) does not exist, skipping."

fclean: clean
	@test -f $(NAME)$(EXE_EXT) && $(RM_FILE) $(NAME)$(EXE_EXT) && echo "Removed $(NAME)$(EXE_EXT)" || echo "$(NAME)$(EXE_EXT) does not exist, skipping."
	@test -f $(NAME)_debug$(EXE_EXT) && $(RM_FILE) $(NAME)_debug$(EXE_EXT) && echo "Removed $(NAME)_debug$(EXE_EXT)" || echo "$(NAME)_debug$(EXE_EXT) does not exist, skipping."

re: fclean
	@make all $(PROCESSORS) --no-print-directory 2>/dev/null

.PHONY: all clean fclean re debug
