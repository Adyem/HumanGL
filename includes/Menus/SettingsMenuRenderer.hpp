#pragma once

#include "../humangl.hpp"
#include "MenuRenderer.hpp"
#include "TextRenderer.hpp"

class SettingsMenuRenderer : public MenuRenderer {
private:
    std::vector<MenuButton> buttons;

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

private:
    // Settings menu specific rendering methods
    void renderTitle();
    void renderSettingsContent();
};
