#include "../../includes/Input/SettingsInputHandler.hpp"

SettingsInputHandler::SettingsInputHandler() 
    : keyboardState(SDL_GetKeyboardState(nullptr)), settingsRenderer(nullptr),
      plusKeyPressed(false), minusKeyPressed(false), cKeyPressed(false) {
}

void SettingsInputHandler::setSettingsRenderer(SettingsMenuRenderer* renderer) {
    settingsRenderer = renderer;
}

void SettingsInputHandler::handleInput() {
    if (!settingsRenderer) return;

    // Handle input based on current page
    if (settingsRenderer->getCurrentPage() == BODY_PART_DETAIL) {
        handleCustomizationInput();
    } else if (settingsRenderer->getCurrentPage() == BACKGROUND_CUSTOMIZATION) {
        handleBackgroundCustomizationInput();
    }
}

void SettingsInputHandler::handleCustomizationInput() {
    // Handle scale adjustment with + and - keys (including = key for +)
    bool currentPlusState = keyboardState[SDL_SCANCODE_KP_PLUS] || keyboardState[SDL_SCANCODE_EQUALS];
    bool currentMinusState = keyboardState[SDL_SCANCODE_KP_MINUS] || keyboardState[SDL_SCANCODE_MINUS];
    bool currentCState = keyboardState[SDL_SCANCODE_C];

    // Scale up with + or = key (only on key press, not hold)
    if (currentPlusState && !plusKeyPressed) {
        settingsRenderer->adjustBodyPartScale(1.1f);
        plusKeyPressed = true;
    } else if (!currentPlusState) {
        plusKeyPressed = false;
    }

    // Scale down with - key (only on key press, not hold)
    if (currentMinusState && !minusKeyPressed) {
        settingsRenderer->adjustBodyPartScale(0.9f);
        minusKeyPressed = true;
    } else if (!currentMinusState) {
        minusKeyPressed = false;
    }

    // Cycle color with C key (only on key press, not hold)
    if (currentCState && !cKeyPressed) {
        settingsRenderer->cycleBodyPartColor();
        cKeyPressed = true;
    } else if (!currentCState) {
        cKeyPressed = false;
    }
}

void SettingsInputHandler::handleBackgroundCustomizationInput() {
    // Handle background color changes with M and S keys
    bool currentMState = keyboardState[SDL_SCANCODE_M];
    bool currentSState = keyboardState[SDL_SCANCODE_S];

    // Change menu background color with M key
    if (currentMState && !plusKeyPressed) { // Reuse plusKeyPressed for M key
        settingsRenderer->cycleMenuBackgroundColor();
        plusKeyPressed = true;
    } else if (!currentMState) {
        plusKeyPressed = false;
    }

    // Change simulation background color with S key
    if (currentSState && !minusKeyPressed) { // Reuse minusKeyPressed for S key
        settingsRenderer->cycleSimulationBackgroundColor();
        minusKeyPressed = true;
    } else if (!currentSState) {
        minusKeyPressed = false;
    }
}
