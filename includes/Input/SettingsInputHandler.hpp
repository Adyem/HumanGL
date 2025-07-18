#pragma once

#include "../humangl.hpp"
#include "../Menus/SettingsMenuRenderer.hpp"

class SettingsInputHandler {
private:
    const Uint8* keyboardState;
    SettingsMenuRenderer* settingsRenderer;
    
    // Key press tracking to prevent rapid firing
    bool plusKeyPressed;
    bool minusKeyPressed;
    bool cKeyPressed;

public:
    SettingsInputHandler();
    ~SettingsInputHandler() = default;

    // Set settings renderer reference
    void setSettingsRenderer(SettingsMenuRenderer* renderer);

    // Handle input for settings customization
    void handleInput();

private:
    // Handle body part customization input
    void handleCustomizationInput();

    // Handle background customization input
    void handleBackgroundCustomizationInput();
};
