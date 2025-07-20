#pragma once

#include "../humangl.hpp"
#include "MenuRenderer.hpp"
#include "TextRenderer.hpp"
#include "../Application/GraphicsMenu.hpp"

class BackgroundCustomizerMenu : public MenuRenderer {
private:
    std::vector<MenuButton> buttons;
    BackgroundCustomizerLogic* externalLogic; // Reference to external logic (can be null)
    BackgroundCustomizerLogic internalLogic;  // Fallback internal logic

    // UI element positions for mouse interaction (rendering only)
    float menuColorSelectorX, menuColorSelectorY, menuColorSelectorSize;
    float simColorSelectorX, simColorSelectorY, simColorSelectorSize;

public:
    BackgroundCustomizerMenu(TextRenderer& textRenderer);
    BackgroundCustomizerMenu(TextRenderer& textRenderer, BackgroundCustomizerLogic& logic);
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

    // Get current colors (delegates to logic)
    const Color& getMenuBackgroundColor() const;
    const Color& getSimulationBackgroundColor() const;

    // Access to logic component for external coordination
    BackgroundCustomizerLogic& getLogic();

    // Set external logic reference
    void setExternalLogic(BackgroundCustomizerLogic& logic);

private:
    // Helper methods (rendering only)
    void drawBackgroundColorSelector(float x, float y, const Color& currentColor, bool isMenuColor);
    void renderTitle();
    void renderBackgroundCustomization();

    // Get the active logic (external if set, otherwise internal)
    BackgroundCustomizerLogic& getActiveLogic();
};
