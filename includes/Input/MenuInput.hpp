#pragma once

#include "../humangl.hpp"

class MenuInput {
private:
    const Uint8* keyboardState;
    bool escapePressed;
    bool mKeyPressed;
    
    // Key state tracking for single-press detection
    bool prevEscapeState;
    bool prevMKeyState;

public:
    MenuInput();
    ~MenuInput();
    
    // Initialize input system
    bool initialize();
    
    // Update input state
    void update();
    
    // Handle SDL key events
    void handleKeyEvent(const SDL_Event& event);
    
    // Check key states
    bool isEscapePressed() const { return escapePressed; }
    bool isMKeyPressed() const { return mKeyPressed; }
    
    // Reset key states (call after processing)
    void resetKeyStates();
    
    // Check if a specific key is currently held down
    bool isKeyDown(SDL_Scancode key) const;
};
