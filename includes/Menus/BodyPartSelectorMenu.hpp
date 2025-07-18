#pragma once

#include "../humangl.hpp"
#include "MenuRenderer.hpp"
#include "TextRenderer.hpp"
#include "../Application/BodyPartSelectorLogic.hpp"

class BodyPartSelectorMenu : public MenuRenderer {
private:
    std::vector<MenuButton> buttons;
    BodyPartSelectorLogic logic;

public:
    BodyPartSelectorMenu(TextRenderer& textRenderer);
    virtual ~BodyPartSelectorMenu() = default;

    // Initialize body part selection buttons
    void initializeButtons();

    // Override the base class render method
    void render(const std::vector<MenuButton>& buttons) override;

    // Render this menu without external buttons
    void render();

    // Get buttons for interaction
    const std::vector<MenuButton>& getButtons() const;

    // Handle button clicks - returns selected body part or navigation action
    MenuAction handleButtonClick(int buttonIndex, BodyPart& selectedPart);

    // Update button hover states
    void updateButtonHover(class MouseHandler& mouseHandler);

private:
    // Helper methods
    void renderTitle();
};
