#include "../../includes/Menus/InstructionsMenuRenderer.hpp"

InstructionsMenuRenderer::InstructionsMenuRenderer(TextRenderer& textRenderer) 
    : MenuRenderer(textRenderer) {
    initializeButtons();
}

void InstructionsMenuRenderer::initializeButtons() {
    float buttonWidth = HUMANGL_MENU_BUTTON_WIDTH;
    float buttonHeight = HUMANGL_MENU_BUTTON_HEIGHT;
    float centerX = (static_cast<float>(windowWidth) - buttonWidth) / 2.0f;
    float startY = static_cast<float>(windowHeight) - HUMANGL_MENU_INSTRUCTIONS_OFFSET_Y;

    buttons.clear();
    buttons.push_back(MenuButton(centerX, startY, buttonWidth, buttonHeight, "Back to Menu"));
}

void InstructionsMenuRenderer::render(const std::vector<MenuButton>& externalButtons) {
    setup2D();
    clearScreen();
    
    renderTitle();
    renderInstructionsContent();
    
    // Draw menu buttons
    for (const auto& button : externalButtons) {
        drawButton(button);
    }
}

void InstructionsMenuRenderer::render() {
    setup2D();
    clearScreen();
    
    renderTitle();
    renderInstructionsContent();
    
    // Draw our own buttons
    for (const auto& button : buttons) {
        drawButton(button);
    }
}

const std::vector<MenuButton>& InstructionsMenuRenderer::getButtons() const {
    return buttons;
}

MenuAction InstructionsMenuRenderer::handleButtonClick(int buttonIndex) {
    switch (buttonIndex) {
        case 0: // Back to Menu
            return MENU_ACTION_BACK_TO_MENU;
        default:
            return MENU_ACTION_NONE;
    }
}

void InstructionsMenuRenderer::renderTitle() {
    // Draw instructions title
    float titleX = static_cast<float>(windowWidth) / 2.0f - 80.0f;
    float titleY = HUMANGL_TITLE_Y_POSITION - 20.0f;
    textRenderer.drawText(titleX, titleY, "Instructions", 1.0f, 1.0f, 1.0f);
}

void InstructionsMenuRenderer::renderInstructionsContent() {
    // Calculate column positions
    float leftColumnX = HUMANGL_INSTRUCTIONS_LEFT_MARGIN;
    float rightColumnX = static_cast<float>(windowWidth) / 2.0f + HUMANGL_INSTRUCTIONS_LEFT_MARGIN;
    float contentY = HUMANGL_INSTRUCTIONS_CONTENT_START_Y;
    float lineSpacing = HUMANGL_INSTRUCTIONS_LINE_SPACING;

    // Left Column - Menu Navigation and Basic Controls
    float leftY = contentY;
    textRenderer.drawText(leftColumnX, leftY, "Menu Navigation:", 0.9f, 0.9f, 0.9f);
    leftY += lineSpacing;
    textRenderer.drawText(leftColumnX + HUMANGL_SETTINGS_INDENT, leftY, "- Use mouse to navigate menus", 0.8f, 0.8f, 0.8f);
    leftY += lineSpacing;
    textRenderer.drawText(leftColumnX + HUMANGL_SETTINGS_INDENT, leftY, "- ESC: Exit application (this can be used anywhere on the app)", 0.8f, 0.8f, 0.8f);
	leftY += lineSpacing;
	textRenderer.drawText(leftColumnX + HUMANGL_SETTINGS_INDENT, leftY, "- M: Return to menu from simulation", 0.8f, 0.8f, 0.8f);
    leftY += lineSpacing * 1.5f;

    textRenderer.drawText(leftColumnX, leftY, "Animation Controls:", 0.9f, 0.9f, 0.9f);
    leftY += lineSpacing;
    textRenderer.drawText(leftColumnX + HUMANGL_SETTINGS_INDENT, leftY, "- SPACE: Toggle walking", 0.8f, 0.8f, 0.8f);
    leftY += lineSpacing;
    textRenderer.drawText(leftColumnX + HUMANGL_SETTINGS_INDENT, leftY, "- P: Jump (single jump)", 0.8f, 0.8f, 0.8f);
    leftY += lineSpacing;
    textRenderer.drawText(leftColumnX + HUMANGL_SETTINGS_INDENT, leftY, "- J: Toggle disco dancing", 0.8f, 0.8f, 0.8f);
    leftY += lineSpacing;
    textRenderer.drawText(leftColumnX + HUMANGL_SETTINGS_INDENT, leftY, "- K: Toggle kung fu fighting", 0.8f, 0.8f, 0.8f);

    // Right Column - Manual Controls and Camera
    float rightY = contentY;
    textRenderer.drawText(rightColumnX, rightY, "Manual Controls:", 0.9f, 0.9f, 0.9f);
    rightY += lineSpacing;
    textRenderer.drawText(rightColumnX + HUMANGL_SETTINGS_INDENT, rightY, "- A/D: Rotate torso left/right", 0.8f, 0.8f, 0.8f);
    rightY += lineSpacing;
    textRenderer.drawText(rightColumnX + HUMANGL_SETTINGS_INDENT, rightY, "- W/S: Head up/down", 0.8f, 0.8f, 0.8f);
    rightY += lineSpacing;
    textRenderer.drawText(rightColumnX + HUMANGL_SETTINGS_INDENT, rightY, "- Q/E: Head left/right", 0.8f, 0.8f, 0.8f);
    rightY += lineSpacing * 1.5f;
}
