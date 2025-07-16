#include "../../includes/Simulation/EventHandler.hpp"

EventHandler::EventHandler(AnimationManager& animMgr, KeyboardHandler& kbHandler, MenuSystem& menuSys,
                          SimulationRenderer& simRenderer, AppState* appState, int& winWidth, int& winHeight)
    : animationManager(animMgr), keyboardHandler(kbHandler), menuSystem(menuSys),
      simulationRenderer(simRenderer), running(true), currentState(appState),
      windowWidth(winWidth), windowHeight(winHeight) {
}

bool EventHandler::handleEvents() {
    if (currentState && *currentState == SIMULATION) {
        // Handle simulation events
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    handleQuitEvent();
                    break;

                case SDL_KEYDOWN:
                    handleKeyDown(event.key);
                    break;

                case SDL_KEYUP:
                    handleKeyUp(event.key);
                    break;

                case SDL_WINDOWEVENT:
                    handleWindowEvent(event.window);
                    break;

                default:
                    break;
            }
        }

        // Handle continuous keyboard input
        keyboardHandler.handleInput();
    } else {
        // Handle menu events
        handleMenuEvents();
    }

    return running;
}

void EventHandler::handleKeyDown(const SDL_KeyboardEvent& keyEvent) {
    switch (keyEvent.keysym.sym) {
        case SDLK_ESCAPE:
            handleQuitEvent();
            break;
            
        case SDLK_m:
            returnToMenu();
            break;
            
        case SDLK_SPACE:
            toggleWalkingAnimation();
            break;
            
        case SDLK_p:
            triggerJumpAnimation();
            break;
            
        case SDLK_j:
            toggleDancingAnimation();
            break;
            
        case SDLK_k:
            toggleKungFuAnimation();
            break;
            
        default:
            break;
    }
}

void EventHandler::handleKeyUp(const SDL_KeyboardEvent& keyEvent) {
    // Handle key release events if needed
    (void)keyEvent; // Suppress unused parameter warning
}

void EventHandler::handleWindowEvent(const SDL_WindowEvent& windowEvent) {
    switch (windowEvent.event) {
        case SDL_WINDOWEVENT_CLOSE:
            handleQuitEvent();
            break;
            
        case SDL_WINDOWEVENT_RESIZED:
            // Window resize handling could be added here
            break;
            
        default:
            break;
    }
}

void EventHandler::handleQuitEvent() {
    running = false;
}

void EventHandler::toggleWalkingAnimation() {
    if (animationManager.isWalking()) {
        animationManager.stopAnimation();
    } else if (!animationManager.isAnimating()) {
        animationManager.startWalking();
    }
}

void EventHandler::triggerJumpAnimation() {
    if (!animationManager.isAnimating()) {
        animationManager.startJumping();
    }
}

void EventHandler::toggleDancingAnimation() {
    if (animationManager.isDancing()) {
        animationManager.stopAnimation();
    } else if (!animationManager.isAnimating()) {
        animationManager.startDancing();
    }
}

void EventHandler::toggleKungFuAnimation() {
    if (animationManager.isKungFu()) {
        animationManager.stopAnimation();
    } else if (!animationManager.isAnimating()) {
        animationManager.startKungFu();
    }
}

void EventHandler::returnToMenu() {
    if (currentState) {
        *currentState = MAIN_MENU;
        menuSystem.setState(MAIN_MENU);
    }
}

void EventHandler::handleMenuEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        // Handle quit event
        if (event.type == SDL_QUIT) {
            handleQuitEvent();
            continue;
        }

        // Handle window resize
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
            windowWidth = event.window.data1;
            windowHeight = event.window.data2;
            menuSystem.updateWindowSize(windowWidth, windowHeight);
            simulationRenderer.updateWindowSize(windowWidth, windowHeight);
            continue;
        }

        // Let menu system handle the event
        MenuAction action = menuSystem.handleEvent(event);
        processMenuAction(action);
    }

    // Update menu system
    MenuAction action = menuSystem.update();
    processMenuAction(action);
}

void EventHandler::processMenuAction(MenuAction action) {
    if (!currentState) return;

    switch (action) {
        case MENU_ACTION_START_SIMULATION:
            *currentState = SIMULATION;
            menuSystem.setState(SIMULATION);
            // Reset all positions when entering simulation
            animationManager.resetToDefaultPosition();
            keyboardHandler.resetCameraPosition();
            break;
        case MENU_ACTION_SETTINGS:
            *currentState = SETTINGS;
            break;
        case MENU_ACTION_CREDITS:
            *currentState = CREDITS;
            break;
        case MENU_ACTION_EXIT:
            running = false;
            break;
        case MENU_ACTION_BACK_TO_MENU:
        case MENU_ACTION_RETURN_TO_MENU:
            *currentState = MAIN_MENU;
            menuSystem.setState(MAIN_MENU);
            break;
        default:
            break;
    }
}
