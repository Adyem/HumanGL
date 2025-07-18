#pragma once

#include "../humangl.hpp"
#include "MenuRenderer.hpp"
#include "TextRenderer.hpp"
#include <vector>
#include <map>
#include <string>

class SettingsMenuRenderer : public MenuRenderer {
private:
    std::vector<MenuButton> buttons;
    SettingsPage currentPage;
    BodyPart selectedBodyPart;
    std::map<BodyPart, BodyPartSettings> bodyPartSettings;
    int currentColorIndex;
    std::vector<Color> availableColors;

    // Background color settings
    Color menuBackgroundColor;
    Color simulationBackgroundColor;
    int menuBgColorIndex;
    int simulationBgColorIndex;

    // UI element positions for mouse interaction
    float sliderX, sliderY, sliderWidth, sliderHeight;
    float colorSelectorX, colorSelectorY, colorSelectorSize;
    float menuColorSelectorX, menuColorSelectorY, menuColorSelectorSize;
    float simColorSelectorX, simColorSelectorY, simColorSelectorSize;
    bool isDraggingSlider;

public:
    SettingsMenuRenderer(TextRenderer& textRenderer);
    virtual ~SettingsMenuRenderer() = default;

    // Initialize menu buttons
    void initializeButtons();

    // Override the base class render method
    void render(const std::vector<MenuButton>& buttons) override;

    // Render this menu without external buttons
    void render();

    // Get buttons for interaction
    const std::vector<MenuButton>& getButtons() const;

    // Handle button clicks
    MenuAction handleButtonClick(int buttonIndex);

    // Page navigation
    void setPage(SettingsPage page);
    void setSelectedBodyPart(BodyPart part);
    SettingsPage getCurrentPage() const;
    void resetToMainPage();

    // Body part customization
    void cycleBodyPartColor();
    void adjustBodyPartScale(float scaleMultiplier);
    void setBodyPartScale(float newScale);
    const BodyPartSettings& getBodyPartSettings(BodyPart part) const;

    // Background color customization
    void cycleMenuBackgroundColor();
    void cycleSimulationBackgroundColor();
    const Color& getMenuBackgroundColor() const;
    const Color& getSimulationBackgroundColor() const;

    // Mouse interaction
    bool handleMouseClick(float mouseX, float mouseY);
    void updateHover(float mouseX, float mouseY);

private:
    // Settings menu specific rendering methods
    void renderTitle();
    void renderSettingsContent();
    void renderBodyPartSelection();
    void renderBodyPartCustomization();
    void renderBackgroundCustomization();

    // UI helper methods
    void initializeAvailableColors();
    void drawSlider(float x, float y, float value, const std::string& label);
    void drawColorSelector(float x, float y);
    void drawBackgroundColorSelector(float x, float y, const Color& currentColor, bool isMenuColor);
    std::string getBodyPartName(BodyPart part) const;
};
