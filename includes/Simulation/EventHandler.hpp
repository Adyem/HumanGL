#pragma once

#include "../humangl.hpp"
#include "AnimationManager.hpp"
#include "../Input/KeyboardHandler.hpp"
#include "../Application/MenuSystem.hpp"
#include "SimulationRenderer.hpp"

class EventHandler {
private:
    AnimationManager& animationManager;
    KeyboardHandler& keyboardHandler;
    MenuSystem& menuSystem;
    SimulationRenderer& simulationRenderer;

    // Event state tracking
    bool running;
    AppState* currentState;
    int& windowWidth;
    int& windowHeight;

public:
    EventHandler(AnimationManager& animMgr, KeyboardHandler& kbHandler, MenuSystem& menuSys,
                SimulationRenderer& simRenderer, AppState* appState, int& winWidth, int& winHeight);
    ~EventHandler() = default;

    // Main event handling method
    bool handleEvents();

    // Specific event handlers
    void handleKeyDown(const SDL_KeyboardEvent& keyEvent);
    void handleKeyUp(const SDL_KeyboardEvent& keyEvent);
    void handleWindowEvent(const SDL_WindowEvent& windowEvent);
    void handleQuitEvent();

    // Menu event handling
    void handleMenuEvents();
    void processMenuAction(MenuAction action);

    // Animation control methods
    void toggleWalkingAnimation();
    void triggerJumpAnimation();
    void toggleDancingAnimation();
    void toggleKungFuAnimation();

    // State queries
    bool isRunning() const { return running; }
    void setRunning(bool state) { running = state; }

    // Menu navigation
    void returnToMenu();
};

