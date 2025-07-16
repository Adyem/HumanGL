#include "../../includes/Menus/SettingsMenuRenderer.hpp"

SettingsMenuRenderer::SettingsMenuRenderer(TextRenderer& textRenderer)
    : MenuRenderer(textRenderer) {
    initializeButtons();
}

void SettingsMenuRenderer::initializeButtons() {
    float buttonWidth = 200.0f;
    float buttonHeight = 50.0f;
    float centerX = (static_cast<float>(windowWidth) - buttonWidth) / 2.0f;
    float startY = static_cast<float>(windowHeight) / 2.0f + 150.0f;

    buttons.clear();
    buttons.push_back(MenuButton(centerX, startY, buttonWidth, buttonHeight, "Back to Menu"));
}

void SettingsMenuRenderer::render(const std::vector<MenuButton>& externalButtons) {
    setup2D();
    clearScreen();

    renderTitle();
    renderSettingsContent();

    // Draw menu buttons
    for (const auto& button : externalButtons) {
        drawButton(button);
    }
}

void SettingsMenuRenderer::render() {
    setup2D();
    clearScreen();

    renderTitle();
    renderSettingsContent();

    // Draw our own buttons
    for (const auto& button : buttons) {
        drawButton(button);
    }
}

const std::vector<MenuButton>& SettingsMenuRenderer::getButtons() const {
    return buttons;
}

MenuAction SettingsMenuRenderer::handleButtonClick(int buttonIndex) {
    switch (buttonIndex) {
        case 0: // Back to Menu
            return MENU_ACTION_BACK_TO_MENU;
        default:
            return MENU_ACTION_NONE;
    }
}

void SettingsMenuRenderer::renderTitle() {
    // Draw settings title
    float titleX = static_cast<float>(windowWidth) / 2.0f - 50.0f;
    float titleY = 100.0f;
    textRenderer.drawText(titleX, titleY, "Settings", 1.0f, 1.0f, 1.0f);
}

void SettingsMenuRenderer::renderSettingsContent() {
    // Draw settings content
    float contentY = 200.0f;
    float lineSpacing = 30.0f;

    textRenderer.drawText(50.0f, contentY, "Graphics Settings:", 0.9f, 0.9f, 0.9f);
    contentY += lineSpacing;
    textRenderer.drawText(70.0f, contentY, "- Resolution: 800x600", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing;
    textRenderer.drawText(70.0f, contentY, "- VSync: Enabled", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing;
    textRenderer.drawText(70.0f, contentY, "- Anti-aliasing: Off", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing * 1.5f;

    textRenderer.drawText(50.0f, contentY, "Controls:", 0.9f, 0.9f, 0.9f);
    contentY += lineSpacing;
    textRenderer.drawText(70.0f, contentY, "- Mouse sensitivity: Normal", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing;
    textRenderer.drawText(70.0f, contentY, "- Keyboard layout: QWERTY", 0.8f, 0.8f, 0.8f);
}
