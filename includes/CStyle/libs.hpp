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


// Additional useful includes for future expansion
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include <functional>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <deque>
#include <array>
#include <tuple>
#include <utility>
#include <limits>
#include <random>
