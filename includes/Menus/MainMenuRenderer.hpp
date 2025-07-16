#pragma once

#include "../humangl.hpp"
#include "MenuRenderer.hpp"
#include "TextRenderer.hpp"

class MainMenuRenderer : public MenuRenderer {
private:
    std::vector<MenuButton> buttons;

public:
    MainMenuRenderer(TextRenderer& textRenderer);
    virtual ~MainMenuRenderer() = default;

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
    // Main menu specific rendering methods
    void renderTitle();
};
