#include "../../includes/Menus/CreditsMenuRenderer.hpp"

CreditsMenuRenderer::CreditsMenuRenderer(TextRenderer& textRenderer)
    : MenuRenderer(textRenderer) {
    initializeButtons();
}

void CreditsMenuRenderer::initializeButtons() {
    float buttonWidth = HUMANGL_MENU_BUTTON_WIDTH;
    float buttonHeight = HUMANGL_MENU_BUTTON_HEIGHT;
    float centerX = (static_cast<float>(windowWidth) - buttonWidth) / 2.0f;
    float startY = static_cast<float>(windowHeight) / 2.0f + HUMANGL_MENU_SETTINGS_OFFSET_Y;

    buttons.clear();
    buttons.push_back(MenuButton(centerX, startY, buttonWidth, buttonHeight, "Back to Menu"));
}

void CreditsMenuRenderer::render(const std::vector<MenuButton>& externalButtons) {
    setup2D();
    clearScreen();

    renderTitle();
    renderCreditsContent();

    // Draw menu buttons
    for (const auto& button : externalButtons) {
        drawButton(button);
    }
}

void CreditsMenuRenderer::render() {
    setup2D();
    clearScreen();

    renderTitle();
    renderCreditsContent();

    // Draw our own buttons
    for (const auto& button : buttons) {
        drawButton(button);
    }
}

const std::vector<MenuButton>& CreditsMenuRenderer::getButtons() const {
    return buttons;
}

MenuAction CreditsMenuRenderer::handleButtonClick(int buttonIndex) {
    switch (buttonIndex) {
        case 0: // Back to Menu
            return MENU_ACTION_BACK_TO_MENU;
        default:
            return MENU_ACTION_NONE;
    }
}

void CreditsMenuRenderer::renderTitle() {
    // Draw credits title
    float titleX = static_cast<float>(windowWidth) / 2.0f - 50.0f;
    float titleY = 100.0f;
    textRenderer.drawText(titleX, titleY, "Credits", 1.0f, 1.0f, 1.0f);
}

void CreditsMenuRenderer::renderCreditsContent() {
    // Calculate column positions
    float leftColumnX = HUMANGL_CREDITS_LEFT_MARGIN;
    float rightColumnX = static_cast<float>(windowWidth) / 2.0f + HUMANGL_CREDITS_LEFT_MARGIN;
    float contentY = HUMANGL_CREDITS_CONTENT_START_Y;
    float lineSpacing = HUMANGL_CREDITS_LINE_SPACING;

    // Left Column - Technologies Used
    float leftY = contentY;
    textRenderer.drawText(leftColumnX, leftY, "Developed with:", 0.9f, 0.9f, 0.9f);
    leftY += lineSpacing;
    textRenderer.drawText(leftColumnX + HUMANGL_CREDITS_INDENT, leftY, "- OpenGL for 3D graphics", 0.8f, 0.8f, 0.8f);
    leftY += lineSpacing;
    textRenderer.drawText(leftColumnX + HUMANGL_CREDITS_INDENT, leftY, "- SDL2 for window management", 0.8f, 0.8f, 0.8f);
    leftY += lineSpacing;
    textRenderer.drawText(leftColumnX + HUMANGL_CREDITS_INDENT, leftY, "- C++14 for core implementation", 0.8f, 0.8f, 0.8f);
    leftY += lineSpacing * 1.5f;

    textRenderer.drawText(leftColumnX, leftY, "Architecture:", 0.9f, 0.9f, 0.9f);
    leftY += lineSpacing;
    textRenderer.drawText(leftColumnX + HUMANGL_CREDITS_INDENT, leftY, "- Modular design pattern", 0.8f, 0.8f, 0.8f);
    leftY += lineSpacing;
    textRenderer.drawText(leftColumnX + HUMANGL_CREDITS_INDENT, leftY, "- Object-oriented structure", 0.8f, 0.8f, 0.8f);
    leftY += lineSpacing;
    textRenderer.drawText(leftColumnX + HUMANGL_CREDITS_INDENT, leftY, "- Event-driven system", 0.8f, 0.8f, 0.8f);

    // Right Column - Features
    float rightY = contentY;
    textRenderer.drawText(rightColumnX, rightY, "Core features:", 0.9f, 0.9f, 0.9f);
    rightY += lineSpacing;
    textRenderer.drawText(rightColumnX + HUMANGL_CREDITS_INDENT, rightY, "- Hierarchical skeletal animation", 0.8f, 0.8f, 0.8f);
    rightY += lineSpacing;
    textRenderer.drawText(rightColumnX + HUMANGL_CREDITS_INDENT, rightY, "- Walking, Jumping and Model", 0.8f, 0.8f, 0.8f);
    rightY += lineSpacing * 1.5f;

    textRenderer.drawText(rightColumnX, rightY, "Bonus features:", 0.9f, 0.9f, 0.9f);
    rightY += lineSpacing;
    textRenderer.drawText(rightColumnX + HUMANGL_CREDITS_INDENT, rightY, "- Multiple Animations(dance, kung fu)", 0.8f, 0.8f, 0.8f);
    rightY += lineSpacing;
    textRenderer.drawText(rightColumnX + HUMANGL_CREDITS_INDENT, rightY, "- Input handling(keyboard and mouse)", 0.8f, 0.8f, 0.8f);
    rightY += lineSpacing;
    textRenderer.drawText(rightColumnX + HUMANGL_CREDITS_INDENT, rightY, "- Menu system with multiple pages", 0.8f, 0.8f, 0.8f);
    rightY += lineSpacing;
    textRenderer.drawText(rightColumnX + HUMANGL_CREDITS_INDENT, rightY, "- Extra bodyparts(neck,eyes, shoulders)", 0.8f, 0.8f, 0.8f);
    rightY += lineSpacing;
    textRenderer.drawText(rightColumnX + HUMANGL_CREDITS_INDENT, rightY, "- Settings for all bodyparts and custumization", 0.8f, 0.8f, 0.8f);
}
