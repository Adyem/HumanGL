#pragma once

#include "../humangl.hpp"
#include "MenuRenderer.hpp"
#include "TextRenderer.hpp"
#include "../Application/SettingsMainMenuLogic.hpp"

class SettingsMainMenu : public MenuRenderer {
private:
    std::vector<MenuButton> buttons;
    SettingsMainMenuLogic logic;

public:
    SettingsMainMenu(TextRenderer& textRenderer);
    virtual ~SettingsMainMenu() = default;

    // Initialize main settings buttons
    void initializeButtons();

    // Override the base class render method
    void render(const std::vector<MenuButton>& buttons) override;

    // Render this menu without external buttons
    void render();

    // Get buttons for interaction
    const std::vector<MenuButton>& getButtons() const;

    // Handle button clicks
    MenuAction handleButtonClick(int buttonIndex);

    // Update button hover states
    void updateButtonHover(class MouseHandler& mouseHandler);

private:
    // Settings menu specific rendering methods
    void renderTitle();
    void renderSettingsContent();
};
