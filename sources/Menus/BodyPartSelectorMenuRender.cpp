#include "../../includes/Menus/BodyPartSelectorMenuRender.hpp"
#include "../../includes/Input/MouseHandler.hpp"

BodyPartSelectorMenu::BodyPartSelectorMenu(TextRenderer& textRenderer)
    : MenuRenderer(textRenderer) {
    initializeButtons();
}

void BodyPartSelectorMenu::initializeButtons() {
    // Always clear existing buttons first
    buttons.clear();

    // Body part selection buttons
    float buttonWidth = HUMANGL_BODYPART_BUTTON_WIDTH;
    float buttonHeight = HUMANGL_BODYPART_BUTTON_HEIGHT;
    float spacing = HUMANGL_BODYPART_BUTTON_SPACING;
    float topMargin = HUMANGL_BODYPART_TOP_MARGIN;

    // Create buttons for all customizable body parts (centered grid)
    std::vector<BodyPart> mainBodyParts = logic.getCustomizableBodyParts();

    // Center the grid
    float horizontalSpacing = 30.0f; // More horizontal spacing between columns
    float totalGridWidth = HUMANGL_BODYPART_COLUMNS * buttonWidth + (HUMANGL_BODYPART_COLUMNS - 1) * horizontalSpacing;
    float centerX = (static_cast<float>(windowWidth) - totalGridWidth) / 2.0f;

    int row = 0, col = 0;
    for (size_t i = 0; i < mainBodyParts.size(); i++) {
        BodyPart part = mainBodyParts[i];
        float x = centerX + col * (buttonWidth + horizontalSpacing);
        float y = topMargin + row * spacing;

        // Create button using proper constructor
        buttons.emplace_back(x, y, buttonWidth, buttonHeight, logic.getBodyPartName(part));

        col++;
        if (col >= HUMANGL_BODYPART_COLUMNS) {
            col = 0;
            row++;
        }
    }

    // Back buttons (horizontal layout, centered)
    float backButtonY = topMargin + (row + 1) * spacing + 40.0f;
    float backButtonSpacing = 30.0f; // More spacing to match grid
    float totalBackButtonWidth = 2 * buttonWidth + backButtonSpacing;
    float backButtonStartX = (static_cast<float>(windowWidth) - totalBackButtonWidth) / 2.0f;

    buttons.emplace_back(backButtonStartX, backButtonY, buttonWidth, buttonHeight, "Back to Settings");
    buttons.emplace_back(backButtonStartX + buttonWidth + backButtonSpacing, backButtonY, buttonWidth, buttonHeight, "Back to Main Menu");
}

void BodyPartSelectorMenu::render(const std::vector<MenuButton>& externalButtons) {
    setup2D();
    clearScreen();

    renderTitle();

    // Draw menu buttons
    for (const auto& button : externalButtons) {
        drawButton(button);
    }
}

void BodyPartSelectorMenu::render() {
    render(buttons);
}

const std::vector<MenuButton>& BodyPartSelectorMenu::getButtons() const {
    return buttons;
}

MenuAction BodyPartSelectorMenu::handleButtonClick(int buttonIndex, BodyPart& selectedPart) {
    return logic.handleButtonClick(buttonIndex, selectedPart);
}

void BodyPartSelectorMenu::renderTitle() {
    float titleX = static_cast<float>(windowWidth) / 2.0f - HUMANGL_TITLE_X_OFFSET;
    float titleY = HUMANGL_TITLE_Y_POSITION;
    textRenderer.drawText(titleX, titleY, "Body Part Selector", 1.0f, 1.0f, 1.0f);
}

void BodyPartSelectorMenu::updateButtonHover(MouseHandler& mouseHandler) {
    mouseHandler.updateButtonHover(buttons);
}
