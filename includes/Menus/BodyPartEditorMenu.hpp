#pragma once

#include "../humangl.hpp"
#include "MenuRenderer.hpp"
#include "TextRenderer.hpp"
#include "../Application/BodyPartEditorLogic.hpp"
#include <map>

class BodyPartEditorMenu : public MenuRenderer {
private:
    std::vector<MenuButton> buttons;
    BodyPartEditorLogic* externalLogic; // Reference to external logic (can be null)
    BodyPartEditorLogic internalLogic;  // Fallback internal logic

    // UI element positions for mouse interaction (rendering only)
    float sliderX, sliderY, sliderWidth, sliderHeight;
    float colorSelectorX, colorSelectorY, colorSelectorSize;

public:
    BodyPartEditorMenu(TextRenderer& textRenderer);
    BodyPartEditorMenu(TextRenderer& textRenderer, BodyPartEditorLogic& logic);
    virtual ~BodyPartEditorMenu() = default;

    // Set the body part to edit (delegates to logic)
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

    // Body part customization (delegates to logic)
    void cycleBodyPartColor();
    void adjustBodyPartScale(float scaleMultiplier);
    void setBodyPartScale(float newScale);
    void resetBodyPartToDefault();

    // Get current settings (delegates to logic)
    const BodyPartSettings& getBodyPartSettings(BodyPart part) const;
    const std::map<BodyPart, BodyPartSettings>& getAllBodyPartSettings() const;

    // Access to logic component for external coordination
    BodyPartEditorLogic& getLogic();

    // Set external logic reference
    void setExternalLogic(BodyPartEditorLogic& logic);

private:
    // Helper methods (rendering only)
    void drawSlider(float x, float y, float value, const std::string& label);
    void drawColorSelector(float x, float y);
    void renderTitle();
    void renderBodyPartCustomization();

    // Get the active logic (external if set, otherwise internal)
    BodyPartEditorLogic& getActiveLogic();
};
