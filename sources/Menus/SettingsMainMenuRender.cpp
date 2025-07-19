#include "../../includes/Menus/SettingsMainMenuRender.hpp"
#include "../../includes/Input/MouseHandler.hpp"

SettingsMainMenu::SettingsMainMenu(TextRenderer& textRenderer)
    : MenuRenderer(textRenderer) {
    initializeButtons();
}

void SettingsMainMenu::initializeButtons() {
    // Always clear existing buttons first
    buttons.clear();

    // Main settings page buttons
    float buttonWidth = HUMANGL_MENU_BUTTON_WIDTH;
    float buttonHeight = HUMANGL_MENU_BUTTON_HEIGHT;
    float centerX = (static_cast<float>(windowWidth) - buttonWidth) / 2.0f;
    float startY = static_cast<float>(windowHeight) / 2.0f - HUMANGL_MENU_SETTINGS_OFFSET_Y;
    float spacing = HUMANGL_MENU_BUTTON_SPACING;

    // Create buttons using proper MenuButton constructor
    buttons.emplace_back(centerX, startY, buttonWidth, buttonHeight, "Body parts");
    buttons.emplace_back(centerX, startY + spacing, buttonWidth, buttonHeight, "Graphics");
    buttons.emplace_back(centerX, startY + spacing * 2, buttonWidth, buttonHeight, "Back to Menu");
}

void SettingsMainMenu::render(const std::vector<MenuButton>& externalButtons) {
    setup2D();
    clearScreen();

    renderTitle();
    renderSettingsContent();

    // Draw menu buttons
    for (const auto& button : externalButtons) {
        drawButton(button);
    }
}

void SettingsMainMenu::render() {
    render(buttons);
}

const std::vector<MenuButton>& SettingsMainMenu::getButtons() const {
    return buttons;
}

MenuAction SettingsMainMenu::handleButtonClick(int buttonIndex) {
    return logic.handleButtonClick(buttonIndex);
}

void SettingsMainMenu::renderTitle() {
    float titleX = static_cast<float>(windowWidth) / 2.0f - HUMANGL_TITLE_X_OFFSET;
    float titleY = HUMANGL_TITLE_Y_POSITION;
    textRenderer.drawText(titleX, titleY, "Settings", 1.0f, 1.0f, 1.0f);
}

void SettingsMainMenu::renderSettingsContent() {
    // No content to render on the main settings page
}

void SettingsMainMenu::updateButtonHover(MouseHandler& mouseHandler) {
    mouseHandler.updateButtonHover(buttons);
}
