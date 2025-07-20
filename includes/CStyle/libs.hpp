#pragma once

// SDL2 includes
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

// Platform-specific OpenGL includes
#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

// Standard C++ library includes
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <stack>
#include <memory>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <cctype>


// Additional useful includes
#include <chrono>
#include <map>
