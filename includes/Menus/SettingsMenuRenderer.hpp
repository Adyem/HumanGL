#pragma once

#include "../humangl.hpp"
#include "MenuRenderer.hpp"
#include "TextRenderer.hpp"
#include "SettingsMainMenu.hpp"
#include "BodyPartSelectorMenu.hpp"
#include "BodyPartEditorMenu.hpp"
#include "BackgroundCustomizerMenu.hpp"
#include <vector>
#include <map>
#include <string>

class SettingsMenuRenderer : public MenuRenderer {
private:
    // Current state
    SettingsPage currentPage;
    BodyPart selectedBodyPart;

    // Component menu renderers
    SettingsMainMenu mainMenu;
    BodyPartSelectorMenu bodyPartSelector;
    BodyPartEditorMenu bodyPartEditor;
    BackgroundCustomizerMenu backgroundCustomizer;

public:
    SettingsMenuRenderer(TextRenderer& textRenderer);
    virtual ~SettingsMenuRenderer() = default;

    // Initialize menu buttons
    void initializeButtons();

    // Override the base class render method
    void render(const std::vector<MenuButton>& buttons) override;

    // Update window size for all components
    void updateWindowSize(int width, int height);

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

    // Body part customization (delegated to components)
    void cycleBodyPartColor();
    void adjustBodyPartScale(float scaleMultiplier);
    void setBodyPartScale(float newScale);
    void resetBodyPartToDefault();
    const BodyPartSettings& getBodyPartSettings(BodyPart part) const;
    const std::map<BodyPart, BodyPartSettings>& getAllBodyPartSettings() const;

    // Background color customization (delegated to components)
    void cycleMenuBackgroundColor();
    void cycleSimulationBackgroundColor();
    void resetColorsToDefault();
    const Color& getMenuBackgroundColor() const;
    const Color& getSimulationBackgroundColor() const;

    // Mouse interaction (delegated to components)
    bool handleMouseClick(float mouseX, float mouseY);
    void updateHover(float mouseX, float mouseY);
    void handleMouseUp();

    // Button hover updates
    void updateButtonHover(class MouseHandler& mouseHandler);

    // Input handling (delegated to components)
    void handleInput();

private:
    // Helper methods for coordination
    MenuRenderer* getCurrentMenuRenderer();
    const MenuRenderer* getCurrentMenuRenderer() const;
    void syncBodyPartSettings();
    void syncBackgroundColors();
};
