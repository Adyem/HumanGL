#pragma once

#include "../humangl.hpp"
#include "MenuRenderer.hpp"
#include "TextRenderer.hpp"
#include <map>

class BodyPartEditorMenu : public MenuRenderer {
private:
    std::vector<MenuButton> buttons;
    BodyPart selectedBodyPart;
    std::map<BodyPart, BodyPartSettings> bodyPartSettings;
    int currentColorIndex;
    std::vector<Color> availableColors;
    
    // UI element positions for mouse interaction
    float sliderX, sliderY, sliderWidth, sliderHeight;
    float colorSelectorX, colorSelectorY, colorSelectorSize;
    bool isDraggingSlider;
    
    // Input handling state
    const Uint8* keyboardState;
    bool plusKeyPressed;
    bool minusKeyPressed;
    bool cKeyPressed;

public:
    BodyPartEditorMenu(TextRenderer& textRenderer);
    virtual ~BodyPartEditorMenu() = default;

    // Set the body part to edit
    void setSelectedBodyPart(BodyPart part);
    void setBodyPartSettings(const std::map<BodyPart, BodyPartSettings>& settings);

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
    void updateHover(float mouseX, float mouseY);
    void handleMouseUp();

    // Input handling
    void handleInput();

    // Update button hover states
    void updateButtonHover(class MouseHandler& mouseHandler);

    // Body part customization
    void cycleBodyPartColor();
    void adjustBodyPartScale(float scaleMultiplier);
    void setBodyPartScale(float newScale);
    void resetBodyPartToDefault();

    // Get current settings
    const BodyPartSettings& getBodyPartSettings(BodyPart part) const;
    const std::map<BodyPart, BodyPartSettings>& getAllBodyPartSettings() const;

private:
    // Helper methods
    void initializeAvailableColors();
    void drawSlider(float x, float y, float value, const std::string& label);
    void drawColorSelector(float x, float y);
    std::string getBodyPartName(BodyPart part) const;
    BodyPartSettings getDefaultBodyPartSettings(BodyPart part) const;
    void renderTitle();
    void renderBodyPartCustomization();
    void handleCustomizationInput();
};
