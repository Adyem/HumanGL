#pragma once

#include "../humangl.hpp"
#include "MenuRenderer.hpp"
#include "TextRenderer.hpp"

class InstructionsMenuRenderer : public MenuRenderer {
private:
    std::vector<MenuButton> buttons;

public:
    InstructionsMenuRenderer(TextRenderer& textRenderer);
    virtual ~InstructionsMenuRenderer() = default;

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
    // Instructions menu specific rendering methods
    void renderTitle();
    void renderInstructionsContent();
};
