#pragma once

#ifdef __APPLE__
	#define GL_SILENCE_DEPRECATION

#elif defined(_WIN32)

#else //Linux
	#define M_PI 3.14159265358979323846
#endif

// Application constants
#define HUMANGL_DEFAULT_WINDOW_WIDTH 800
#define HUMANGL_DEFAULT_WINDOW_HEIGHT 600
#define HUMANGL_WINDOW_TITLE "HumanGL - Skeletal Animation"

// OpenGL constants
#define HUMANGL_OPENGL_MAJOR_VERSION 2
#define HUMANGL_OPENGL_MINOR_VERSION 1
#define HUMANGL_DEPTH_BUFFER_SIZE 24

// Animation constants
#define HUMANGL_TARGET_FPS 60
#define HUMANGL_FRAME_DELAY 16  // ~60 FPS (1000ms / 60fps ≈ 16ms)

// Math utility macros
#define DEGREES_TO_RADIANS(degrees) ((degrees) * M_PI / 180.0f)
#define RADIANS_TO_DEGREES(radians) ((radians) * 180.0f / M_PI)

// Color constants (RGB values 0.0f - 1.0f)
#define HUMANGL_BACKGROUND_COLOR_R 0.2f
#define HUMANGL_BACKGROUND_COLOR_G 0.3f
#define HUMANGL_BACKGROUND_COLOR_B 0.4f
#define HUMANGL_BACKGROUND_COLOR_A 1.0f

// Default body part colors
#define HUMANGL_DEFAULT_SKIN_R 0.9f
#define HUMANGL_DEFAULT_SKIN_G 0.7f
#define HUMANGL_DEFAULT_SKIN_B 0.6f

#define HUMANGL_DEFAULT_CLOTHING_R 0.2f
#define HUMANGL_DEFAULT_CLOTHING_G 0.4f
#define HUMANGL_DEFAULT_CLOTHING_B 0.8f

// Camera and perspective constants
#define HUMANGL_DEFAULT_FOV 45.0f
#define HUMANGL_NEAR_PLANE 0.1f
#define HUMANGL_FAR_PLANE 100.0f
#define HUMANGL_CAMERA_DISTANCE -8.0f

// Animation timing constants
#define HUMANGL_WALKING_SPEED 0.08f
#define HUMANGL_JUMPING_SPEED 0.15f
#define HUMANGL_DANCING_SPEED 0.12f
#define HUMANGL_KUNGFU_SPEED 0.10f
