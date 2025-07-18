#pragma once

#include "../humangl.hpp"
#include <vector>

class BackgroundCustomizerLogic {
private:
    std::vector<Color> availableColors;
    
    // Background color settings
    Color menuBackgroundColor;
    Color simulationBackgroundColor;
    int menuBgColorIndex;
    int simulationBgColorIndex;
    
    // Input handling state
    const Uint8* keyboardState;
    bool plusKeyPressed;  // Reused for M key
    bool minusKeyPressed; // Reused for S key

public:
    BackgroundCustomizerLogic();
    virtual ~BackgroundCustomizerLogic() = default;

    // Handle button clicks
    MenuAction handleButtonClick(int buttonIndex);

    // Mouse interaction logic
    bool handleMouseClick(float mouseX, float mouseY, float menuColorSelectorX, float menuColorSelectorY, 
                         float menuColorSelectorSize, float simColorSelectorX, float simColorSelectorY, 
                         float simColorSelectorSize);

    // Input handling
    void handleInput();

    // Background color customization
    void cycleMenuBackgroundColor();
    void cycleSimulationBackgroundColor();
    void resetColorsToDefault();

    // Get current colors
    const Color& getMenuBackgroundColor() const { return menuBackgroundColor; }
    const Color& getSimulationBackgroundColor() const { return simulationBackgroundColor; }
    const std::vector<Color>& getAvailableColors() const { return availableColors; }

private:
    // Helper methods
    void initializeAvailableColors();
    void handleBackgroundCustomizationInput();
};
