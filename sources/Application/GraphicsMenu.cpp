#include "../../includes/Application/GraphicsMenu.hpp"

BackgroundCustomizerLogic::BackgroundCustomizerLogic()
    : menuBackgroundColor(Color(HUMANGL_BACKGROUND_COLOR_R, HUMANGL_BACKGROUND_COLOR_G, HUMANGL_BACKGROUND_COLOR_B, HUMANGL_BACKGROUND_COLOR_A)),
      simulationBackgroundColor(Color(HUMANGL_SIMULATION_BACKGROUND_R, HUMANGL_SIMULATION_BACKGROUND_G, HUMANGL_SIMULATION_BACKGROUND_B, HUMANGL_SIMULATION_BACKGROUND_A)),
      menuBgColorIndex(0), simulationBgColorIndex(0),
      keyboardState(SDL_GetKeyboardState(nullptr)), plusKeyPressed(false), minusKeyPressed(false) {
    initializeAvailableColors();
}

MenuAction BackgroundCustomizerLogic::handleButtonClick(int buttonIndex) {
    switch (buttonIndex) {
        case 0: // Reset to Default
            resetColorsToDefault();
            return MENU_ACTION_NONE;
        case 1: // Back to Settings
            return MENU_ACTION_SETTINGS;
        case 2: // Back to Main Menu
            return MENU_ACTION_BACK_TO_MENU;
        default:
            return MENU_ACTION_NONE;
    }
}

bool BackgroundCustomizerLogic::handleMouseClick(float mouseX, float mouseY, float menuColorSelectorX, 
                                                float menuColorSelectorY, float menuColorSelectorSize, 
                                                float simColorSelectorX, float simColorSelectorY, 
                                                float simColorSelectorSize) {
    // Check if clicked on menu background color selector
    if (mouseX >= menuColorSelectorX && mouseX <= menuColorSelectorX + menuColorSelectorSize &&
        mouseY >= menuColorSelectorY && mouseY <= menuColorSelectorY + menuColorSelectorSize) {
        cycleMenuBackgroundColor();
        return true;
    }

    // Check if clicked on simulation background color selector
    if (mouseX >= simColorSelectorX && mouseX <= simColorSelectorX + simColorSelectorSize &&
        mouseY >= simColorSelectorY && mouseY <= simColorSelectorY + simColorSelectorSize) {
        cycleSimulationBackgroundColor();
        return true;
    }

    return false;
}

void BackgroundCustomizerLogic::handleInput() {
    if (!keyboardState) return;
    
    handleBackgroundCustomizationInput();
}

void BackgroundCustomizerLogic::cycleMenuBackgroundColor() {
    menuBgColorIndex = (menuBgColorIndex + 1) % availableColors.size();
    menuBackgroundColor = availableColors[menuBgColorIndex];
}

void BackgroundCustomizerLogic::cycleSimulationBackgroundColor() {
    simulationBgColorIndex = (simulationBgColorIndex + 1) % availableColors.size();
    simulationBackgroundColor = availableColors[simulationBgColorIndex];
}

void BackgroundCustomizerLogic::resetColorsToDefault() {
    // Reset to default colors
    menuBackgroundColor = Color(HUMANGL_BACKGROUND_COLOR_R, HUMANGL_BACKGROUND_COLOR_G, HUMANGL_BACKGROUND_COLOR_B, HUMANGL_BACKGROUND_COLOR_A);
    simulationBackgroundColor = Color(HUMANGL_SIMULATION_BACKGROUND_R, HUMANGL_SIMULATION_BACKGROUND_G, HUMANGL_SIMULATION_BACKGROUND_B, HUMANGL_SIMULATION_BACKGROUND_A);

    // Reset color indices
    menuBgColorIndex = 0;
    simulationBgColorIndex = 0;
}

void BackgroundCustomizerLogic::initializeAvailableColors() {
    availableColors.clear();
    availableColors.push_back(Color::SkinTone());
    availableColors.push_back(Color::ClothingBlue());
    availableColors.push_back(Color::Red());
    availableColors.push_back(Color::Green());
    availableColors.push_back(Color::Blue());
    availableColors.push_back(Color::Yellow());
    availableColors.push_back(Color::Magenta());
    availableColors.push_back(Color::Cyan());
    availableColors.push_back(Color::White());
    availableColors.push_back(Color::Black());
}

void BackgroundCustomizerLogic::handleBackgroundCustomizationInput() {
    // Handle background color changes with M and S keys
    bool currentMState = keyboardState[SDL_SCANCODE_M];
    bool currentSState = keyboardState[SDL_SCANCODE_S];

    // Change menu background color with M key
    if (currentMState && !plusKeyPressed) { // Reuse plusKeyPressed for M key
        cycleMenuBackgroundColor();
        plusKeyPressed = true;
    } else if (!currentMState) {
        plusKeyPressed = false;
    }

    // Change simulation background color with S key
    if (currentSState && !minusKeyPressed) { // Reuse minusKeyPressed for S key
        cycleSimulationBackgroundColor();
        minusKeyPressed = true;
    } else if (!currentSState) {
        minusKeyPressed = false;
    }
}
