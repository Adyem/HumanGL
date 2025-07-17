#include "../../includes/Menus/MainMenuRenderer.hpp"

MainMenuRenderer::MainMenuRenderer(TextRenderer& textRenderer)
    : MenuRenderer(textRenderer) {
    initializeButtons();
}

void MainMenuRenderer::initializeButtons() {
    // Main menu buttons (centered)
    float buttonWidth = HUMANGL_MENU_BUTTON_WIDTH;
    float buttonHeight = HUMANGL_MENU_BUTTON_HEIGHT;
    float centerX = (static_cast<float>(windowWidth) - buttonWidth) / 2.0f;
    float startY = static_cast<float>(windowHeight) / 2.0f - HUMANGL_MENU_TITLE_OFFSET_Y;
    float spacing = HUMANGL_MENU_BUTTON_SPACING;

    buttons.clear();
    buttons.push_back(MenuButton(centerX, startY, buttonWidth, buttonHeight, "Start Simulation"));
    buttons.push_back(MenuButton(centerX, startY + spacing, buttonWidth, buttonHeight, "Instructions"));
    buttons.push_back(MenuButton(centerX, startY + spacing * 2, buttonWidth, buttonHeight, "Settings"));
    buttons.push_back(MenuButton(centerX, startY + spacing * 3, buttonWidth, buttonHeight, "Credits"));
    buttons.push_back(MenuButton(centerX, startY + spacing * 4, buttonWidth, buttonHeight, "Exit"));
}

void MainMenuRenderer::render(const std::vector<MenuButton>& externalButtons) {
    setup2D();
    clearScreen();

    renderTitle();

    // Draw menu buttons
    for (const auto& button : externalButtons) {
        drawButton(button);
    }
}

void MainMenuRenderer::render() {
    setup2D();
    clearScreen();

    renderTitle();

    // Draw our own buttons
    for (const auto& button : buttons) {
        drawButton(button);
    }
}

const std::vector<MenuButton>& MainMenuRenderer::getButtons() const {
    return buttons;
}

MenuAction MainMenuRenderer::handleButtonClick(int buttonIndex) {
    switch (buttonIndex) {
        case 0: // Start Simulation
            return MENU_ACTION_START_SIMULATION;
        case 1: // Instructions
            return MENU_ACTION_INSTRUCTIONS;
        case 2: // Settings
            return MENU_ACTION_SETTINGS;
        case 3: // Credits
            return MENU_ACTION_CREDITS;
        case 4: // Exit
            return MENU_ACTION_EXIT;
        default:
            return MENU_ACTION_NONE;
    }
}

void MainMenuRenderer::renderTitle() {
    // Draw main title
    float titleX = static_cast<float>(windowWidth) / 2.0f - 150.0f; // Rough centering
    float titleY = 100.0f;
	float lineSpacing = 30.0f;
    textRenderer.drawText(titleX + lineSpacing * 4.0f, titleY, "HumanGL", 1.0f, 1.0f, 1.0f);
	titleY += lineSpacing;
	textRenderer.drawText(titleX, titleY, "Created by rperez-t and bvangene", 0.8f, 0.8f, 0.8f);
}

