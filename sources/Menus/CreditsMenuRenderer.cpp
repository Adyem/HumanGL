#include "../../includes/Menus/CreditsMenuRenderer.hpp"

CreditsMenuRenderer::CreditsMenuRenderer(TextRenderer& textRenderer)
    : MenuRenderer(textRenderer) {
    initializeButtons();
}

void CreditsMenuRenderer::initializeButtons() {
    float buttonWidth = 200.0f;
    float buttonHeight = 50.0f;
    float centerX = (static_cast<float>(windowWidth) - buttonWidth) / 2.0f;
    float startY = static_cast<float>(windowHeight) / 2.0f + 150.0f;

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
    // Draw credits content
    float contentY = 200.0f;
    float lineSpacing = 30.0f;

    textRenderer.drawText(50.0f, contentY, "HumanGL - Skeletal Animation Demo", 1.0f, 1.0f, 0.8f);
    contentY += lineSpacing * 1.5f;

    textRenderer.drawText(50.0f, contentY, "Developed with:", 0.9f, 0.9f, 0.9f);
    contentY += lineSpacing;
    textRenderer.drawText(70.0f, contentY, "- OpenGL for 3D graphics", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing;
    textRenderer.drawText(70.0f, contentY, "- SDL2 for window management", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing;
    textRenderer.drawText(70.0f, contentY, "- C++ for core implementation", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing * 1.5f;

    textRenderer.drawText(50.0f, contentY, "Features:", 0.9f, 0.9f, 0.9f);
    contentY += lineSpacing;
    textRenderer.drawText(70.0f, contentY, "- Hierarchical skeletal animation", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing;
    textRenderer.drawText(70.0f, contentY, "- Interactive joint control", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing;
    textRenderer.drawText(70.0f, contentY, "- Multiple animation modes", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing;
    textRenderer.drawText(70.0f, contentY, "- Modular menu system", 0.8f, 0.8f, 0.8f);
}
