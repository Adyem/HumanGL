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
    // Draw instructions content
    float contentY = HUMANGL_INSTRUCTIONS_CONTENT_START_Y;
    float lineSpacing = HUMANGL_INSTRUCTIONS_LINE_SPACING;

    textRenderer.drawText(HUMANGL_INSTRUCTIONS_LEFT_MARGIN, contentY, "=== HumanGL - Skeletal Animation Demo ===", 1.0f, 1.0f, 0.8f);
    contentY += lineSpacing * 1.5f;

    textRenderer.drawText(HUMANGL_INSTRUCTIONS_LEFT_MARGIN, contentY, "Menu Navigation:", 0.9f, 0.9f, 0.9f);
    contentY += lineSpacing;
    textRenderer.drawText(HUMANGL_INSTRUCTIONS_LEFT_MARGIN + HUMANGL_SETTINGS_INDENT, contentY, "- Use mouse to navigate menus", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing;
    textRenderer.drawText(HUMANGL_INSTRUCTIONS_LEFT_MARGIN + HUMANGL_SETTINGS_INDENT, contentY, "- ESC: Exit application", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing * 1.5f;

    textRenderer.drawText(HUMANGL_INSTRUCTIONS_LEFT_MARGIN, contentY, "Simulation Controls:", 0.9f, 0.9f, 0.9f);
    contentY += lineSpacing;
    textRenderer.drawText(HUMANGL_INSTRUCTIONS_LEFT_MARGIN + HUMANGL_SETTINGS_INDENT, contentY, "- M: Return to main menu", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing;
    textRenderer.drawText(HUMANGL_INSTRUCTIONS_LEFT_MARGIN + HUMANGL_SETTINGS_INDENT, contentY, "- SPACE: Toggle walking animation", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing;
    textRenderer.drawText(HUMANGL_INSTRUCTIONS_LEFT_MARGIN + HUMANGL_SETTINGS_INDENT, contentY, "- P: Jump (single jump)", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing;
    textRenderer.drawText(HUMANGL_INSTRUCTIONS_LEFT_MARGIN + HUMANGL_SETTINGS_INDENT, contentY, "- J: Toggle disco dancing", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing;
    textRenderer.drawText(HUMANGL_INSTRUCTIONS_LEFT_MARGIN + HUMANGL_SETTINGS_INDENT, contentY, "- K: Toggle kung fu fighting", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing * 1.5f;
    
    textRenderer.drawText(50.0f, contentY, "Manual Controls:", 0.9f, 0.9f, 0.9f);
    contentY += lineSpacing;
    textRenderer.drawText(70.0f, contentY, "- A/D: Rotate torso left/right", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing;
    textRenderer.drawText(70.0f, contentY, "- W/S: Head up/down", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing;
    textRenderer.drawText(70.0f, contentY, "- Q/E: Head left/right", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing;
    textRenderer.drawText(70.0f, contentY, "- 1-3: Left arm controls", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing;
    textRenderer.drawText(70.0f, contentY, "- 4-6: Right arm controls", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing;
    textRenderer.drawText(70.0f, contentY, "- 7-8: Left leg controls", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing;
    textRenderer.drawText(70.0f, contentY, "- 9-0: Right leg controls", 0.8f, 0.8f, 0.8f);
}
