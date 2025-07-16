#include "../../includes/Input/MenuInput.hpp"

MenuInput::MenuInput() 
    : keyboardState(nullptr), escapePressed(false), mKeyPressed(false),
      prevEscapeState(false), prevMKeyState(false) {
}

MenuInput::~MenuInput() {
}

bool MenuInput::initialize() {
    keyboardState = SDL_GetKeyboardState(nullptr);
    return keyboardState != nullptr;
}

void MenuInput::update() {
    if (!keyboardState) {
        return;
    }
    
    // Update keyboard state
    keyboardState = SDL_GetKeyboardState(nullptr);
    
    // Check for single-press events (key was not pressed before, but is pressed now)
    bool currentEscapeState = keyboardState[SDL_SCANCODE_ESCAPE] != 0;
    bool currentMKeyState = keyboardState[SDL_SCANCODE_M] != 0;
    
    escapePressed = currentEscapeState && !prevEscapeState;
    mKeyPressed = currentMKeyState && !prevMKeyState;
    
    // Update previous states
    prevEscapeState = currentEscapeState;
    prevMKeyState = currentMKeyState;
}

void MenuInput::handleKeyEvent(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                escapePressed = true;
                break;
            case SDLK_m:
                mKeyPressed = true;
                break;
            default:
                break;
        }
    }
}

void MenuInput::resetKeyStates() {
    escapePressed = false;
    mKeyPressed = false;
}

bool MenuInput::isKeyDown(SDL_Scancode key) const {
    if (!keyboardState) {
        return false;
    }
    return keyboardState[key] != 0;
}
