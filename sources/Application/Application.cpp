#include "../../includes/Application/Application.hpp"

Application::Application()
    : window(nullptr), glContext(nullptr), running(false),
      windowWidth(HUMANGL_DEFAULT_WINDOW_WIDTH), windowHeight(HUMANGL_DEFAULT_WINDOW_HEIGHT),
      currentState(MAIN_MENU),
      keyboardHandler(drawPerson),
      animationManager(drawPerson),
      simulationRenderer(drawPerson, keyboardHandler, windowWidth, windowHeight),
      eventHandler(animationManager, keyboardHandler, menuSystem, simulationRenderer, 
                   &currentState, windowWidth, windowHeight),
      currentAnimation(NONE), animationTime(0.0f), jumpHeight(0.0f),
      keyboardState(nullptr) {
    // Set up the connection between KeyboardHandler and AnimationManager
    keyboardHandler.setAnimationManager(&animationManager);
}

Application::~Application() {
    cleanup();
}

bool Application::initialize() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Set OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, HUMANGL_OPENGL_MAJOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, HUMANGL_OPENGL_MINOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, HUMANGL_DEPTH_BUFFER_SIZE);

    // Create window
    window = SDL_CreateWindow(HUMANGL_WINDOW_TITLE,
                             SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                             windowWidth, windowHeight,
                             SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create OpenGL context
    glContext = SDL_GL_CreateContext(window);
    if (glContext == nullptr) {
        std::cerr << "OpenGL context could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Enable VSync
    if (SDL_GL_SetSwapInterval(1) < 0) {
        std::cerr << "Warning: Unable to set VSync! SDL_Error: " << SDL_GetError() << std::endl;
    }

    // Initialize OpenGL
    glEnable(GL_DEPTH_TEST);
    glClearColor(HUMANGL_BACKGROUND_COLOR_R, HUMANGL_BACKGROUND_COLOR_G, HUMANGL_BACKGROUND_COLOR_B, HUMANGL_BACKGROUND_COLOR_A);  // Nice blue-gray background for menus
    glViewport(0, 0, windowWidth, windowHeight);

    keyboardState = SDL_GetKeyboardState(nullptr);

    // Initialize menu system
    if (!menuSystem.initialize(windowWidth, windowHeight)) {
        std::cerr << "Failed to initialize menu system" << std::endl;
        return false;
    }

    // Connect simulation renderer to settings for background colors
    simulationRenderer.setSettingsRenderer(&menuSystem.getSettingsMenuRenderer());

    // Apply initial body part colors
    simulationRenderer.applyBodyPartCustomizations();

    running = true;
    return true;
}

void Application::run() {
    if (!initialize()) {
        return;
    }

    // Main game loop
    while (running) {
        handleEvents();

        // Only update animations and handle keyboard input in simulation mode
        if (currentState == SIMULATION) {
            updateAnimations();        // Update all animations
            handleKeyboardInput();     // Handle continuous keyboard input
        }

        render();

        // Small delay to prevent excessive CPU usage
        SDL_Delay(HUMANGL_FRAME_DELAY); // ~60 FPS
    }

    cleanup();
}

void Application::cleanup() {
    menuSystem.cleanup();
    if (glContext) {
        SDL_GL_DeleteContext(glContext);
        glContext = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}

void Application::handleEvents() {
    // Use the unified EventHandler for all events (menu and simulation)
    running = eventHandler.handleEvents();
}

void Application::updateAnimations() {
    // Use the new AnimationManager to update animations
    animationManager.update();

    // Sync the old animation state for compatibility
    currentAnimation = animationManager.getCurrentAnimation();
    animationTime = animationManager.getAnimationTime();
    jumpHeight = animationManager.getJumpHeight();
}

void Application::handleKeyboardInput() {
    // Use the KeyboardHandler for all keyboard input
    keyboardHandler.handleInput();
}

void Application::render() {
    // Render based on current state
    if (currentState == SIMULATION) {
        renderSimulation();
    } else {
        // Let menu system handle menu rendering
        menuSystem.render();
    }

    // Swap buffers
    SDL_GL_SwapWindow(window);
}

void Application::renderSimulation() {
    // Use the new SimulationRenderer to handle all simulation rendering
    simulationRenderer.render();
}



void Application::updateWindowSize(int width, int height) {
    windowWidth = width;
    windowHeight = height;
    
    // Update all systems that need to know about window size changes
    menuSystem.updateWindowSize(windowWidth, windowHeight);
    simulationRenderer.updateWindowSize(windowWidth, windowHeight);
}
