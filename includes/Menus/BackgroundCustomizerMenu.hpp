#pragma once

#include "../humangl.hpp"
#include "MenuRenderer.hpp"
#include "TextRenderer.hpp"

class BackgroundCustomizerMenu : public MenuRenderer {
private:
    std::vector<MenuButton> buttons;
    std::vector<Color> availableColors;
    
    // Background color settings
    Color menuBackgroundColor;
    Color simulationBackgroundColor;
    int menuBgColorIndex;
    int simulationBgColorIndex;
    
    // UI element positions for mouse interaction
    float menuColorSelectorX, menuColorSelectorY, menuColorSelectorSize;
    float simColorSelectorX, simColorSelectorY, simColorSelectorSize;
    
    // Input handling state
    const Uint8* keyboardState;
    bool plusKeyPressed;  // Reused for M key
    bool minusKeyPressed; // Reused for S key

public:
    BackgroundCustomizerMenu(TextRenderer& textRenderer);
    virtual ~BackgroundCustomizerMenu() = default;

    // Initialize buttons
    void initializeButtons();

    // Override the base class render method
    void render(const std::vector<MenuButton>& buttons) override;

    // Render this menu without external buttons
    void render();

    // Get buttons for interaction
    const std::vector<MenuButton>& getButtons() const;

    // Handle button clicks
    MenuAction handleButtonClick(int buttonIndex);

    // Mouse interaction
    bool handleMouseClick(float mouseX, float mouseY);

    // Input handling
    void handleInput();

    // Update button hover states
    void updateButtonHover(class MouseHandler& mouseHandler);

    // Background color customization
    void cycleMenuBackgroundColor();
    void cycleSimulationBackgroundColor();
    void resetColorsToDefault();

    // Get current colors
    const Color& getMenuBackgroundColor() const { return menuBackgroundColor; }
    const Color& getSimulationBackgroundColor() const { return simulationBackgroundColor; }

private:
    // Helper methods
    void initializeAvailableColors();
    void drawBackgroundColorSelector(float x, float y, const Color& currentColor, bool isMenuColor);
    void renderTitle();
    void renderBackgroundCustomization();
    void handleBackgroundCustomizationInput();
};
