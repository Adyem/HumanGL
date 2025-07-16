#pragma once

#include "../humangl.hpp"
#include "MenuSystem.hpp"
#include "../Human/DrawPerson.hpp"
#include "../Input/KeyboardHandler.hpp"
#include "../Simulation/SimulationRenderer.hpp"
#include "../Simulation/AnimationManager.hpp"
#include "../Simulation/EventHandler.hpp"
#include "../Matrix/MatrixStack.hpp"

class Application {
private:
    // SDL and OpenGL context
    SDL_Window* window;
    SDL_GLContext glContext;
    bool running;
    
    // Window properties
    int windowWidth;
    int windowHeight;
    
    // Application state
    AppState currentState;
    
    // Core systems
    MatrixStack matrixStack;
    DrawPerson drawPerson;
    KeyboardHandler keyboardHandler;
    MenuSystem menuSystem;
    
    // Simulation systems
    AnimationManager animationManager;
    SimulationRenderer simulationRenderer;
    EventHandler eventHandler;
    
    // Legacy animation state (for compatibility)
    AnimationMode currentAnimation;
    float animationTime;
    float jumpHeight;
    
    // Keyboard state
    const Uint8* keyboardState;

public:
    // Constructor and destructor
    Application();
    ~Application();
    
    // Main application methods
    bool initialize();
    void run();
    void cleanup();
    
    // Core loop methods
    void handleEvents();
    void updateAnimations();
    void handleKeyboardInput();
    void render();
    
    // Rendering methods
    void renderSimulation();
    void renderMenu();
    
    // State management
    AppState getCurrentState() const { return currentState; }
    void setState(AppState newState) { currentState = newState; }
    
    // Window management
    void updateWindowSize(int width, int height);
    
    // Utility methods
    bool isRunning() const { return running; }
    void setRunning(bool state) { running = state; }
};
