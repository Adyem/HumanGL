#pragma once

#include "../humangl.hpp"
#include "MenuRenderer.hpp"
#include "TextRenderer.hpp"
#include "SettingsMainMenuRender.hpp"
#include "BodyPartSelectorMenuRender.hpp"
#include "BodyPartEditorMenuRender.hpp"
#include "GraphicsMenuRender.hpp"
#include "../Application/SettingsMenu.hpp"

class SettingsMenuRenderer : public MenuRenderer {
private:
    // Logic component (handles all state and business logic)
    SettingsMenuLogic logic;

    // Component menu renderers (pure rendering)
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

    // Handle button clicks (delegates to logic)
    MenuAction handleButtonClick(int buttonIndex);

    // Page navigation (delegates to logic)
    void setPage(SettingsPage page);
    void setSelectedBodyPart(BodyPart part);
    SettingsPage getCurrentPage() const;
    void resetToMainPage();

    // Body part customization (delegates to logic)
    void cycleBodyPartColor();
    void adjustBodyPartScale(float scaleMultiplier);
    void setBodyPartScale(float newScale);
    void resetBodyPartToDefault();
    const BodyPartSettings& getBodyPartSettings(BodyPart part) const;
    const std::map<BodyPart, BodyPartSettings>& getAllBodyPartSettings() const;

    // Background color customization (delegates to logic)
    void cycleMenuBackgroundColor();
    void cycleSimulationBackgroundColor();
    void resetColorsToDefault();
    const Color& getMenuBackgroundColor() const;
    const Color& getSimulationBackgroundColor() const;

    // Mouse interaction (delegates to logic)
    bool handleMouseClick(float mouseX, float mouseY);
    void updateHover(float mouseX, float mouseY);
    void handleMouseUp();

    // Button hover updates (rendering coordination)
    void updateButtonHover(class MouseHandler& mouseHandler);

    // Input handling (delegates to logic)
    void handleInput();

private:
    // Helper methods for coordination
    MenuRenderer* getCurrentMenuRenderer();
    const MenuRenderer* getCurrentMenuRenderer() const;
    void syncBodyPartSettings();
    void syncBackgroundColors();
    void syncLogicWithMenuComponents();
};
