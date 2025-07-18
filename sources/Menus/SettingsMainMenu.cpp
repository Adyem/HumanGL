#include "../../includes/Menus/SettingsMainMenu.hpp"
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
    float startY = static_cast<float>(windowHeight) / 2.0f + 50.0f;
    float spacing = HUMANGL_MENU_BUTTON_SPACING;

    // Create buttons using proper MenuButton constructor
    buttons.emplace_back(centerX, startY, buttonWidth, buttonHeight, "Body Customization");
    buttons.emplace_back(centerX, startY + spacing, buttonWidth, buttonHeight, "Background Colors");
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
    switch (buttonIndex) {
        case 0: // Body Customization
            return MENU_ACTION_BODY_CUSTOMIZATION;
        case 1: // Background Colors
            return MENU_ACTION_BACKGROUND_CUSTOMIZATION;
        case 2: // Back to Menu
            return MENU_ACTION_BACK_TO_MENU;
        default:
            return MENU_ACTION_NONE;
    }
}

void SettingsMainMenu::renderTitle() {
    float titleX = static_cast<float>(windowWidth) / 2.0f - HUMANGL_TITLE_X_OFFSET;
    float titleY = HUMANGL_TITLE_Y_POSITION;
    textRenderer.drawText(titleX, titleY, "Settings", 1.0f, 1.0f, 1.0f);
}

void SettingsMainMenu::renderSettingsContent() {
    float contentY = HUMANGL_SETTINGS_CONTENT_START_Y;
    float lineSpacing = HUMANGL_SETTINGS_LINE_SPACING;
    
    textRenderer.drawText(HUMANGL_SETTINGS_LEFT_MARGIN, contentY, "Welcome to Settings!", 0.9f, 0.9f, 0.9f);
    contentY += lineSpacing * 2.0f;
    
    textRenderer.drawText(HUMANGL_SETTINGS_LEFT_MARGIN, contentY, "Customization:", 0.9f, 0.9f, 0.9f);
    contentY += lineSpacing;
    textRenderer.drawText(HUMANGL_SETTINGS_LEFT_MARGIN + HUMANGL_SETTINGS_INDENT, contentY, "- Use 'Body Customization' to modify body parts", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing;
    textRenderer.drawText(HUMANGL_SETTINGS_LEFT_MARGIN + HUMANGL_SETTINGS_INDENT, contentY, "- Use 'Background Colors' to change menu/simulation colors", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing * 2.0f;
    
    textRenderer.drawText(HUMANGL_SETTINGS_LEFT_MARGIN, contentY, "Navigation:", 0.9f, 0.9f, 0.9f);
    contentY += lineSpacing;
    textRenderer.drawText(HUMANGL_SETTINGS_LEFT_MARGIN + HUMANGL_SETTINGS_INDENT, contentY, "- Use buttons to navigate between sections", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing;
    textRenderer.drawText(HUMANGL_SETTINGS_LEFT_MARGIN + HUMANGL_SETTINGS_INDENT, contentY, "- Press ESC to return to main menu", 0.8f, 0.8f, 0.8f);
}

void SettingsMainMenu::updateButtonHover(MouseHandler& mouseHandler) {
    mouseHandler.updateButtonHover(buttons);
}
