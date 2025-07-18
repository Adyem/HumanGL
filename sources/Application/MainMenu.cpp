#include "../../includes/Application/MainMenu.hpp"

MainMenu::MainMenu(MainMenuRenderer& renderer, MouseHandler& mouseHandler, MenuInputInterface& menuInput, int winWidth, int winHeight)
    : BaseMenu(mouseHandler, menuInput, winWidth, winHeight), renderer(renderer) {
    initializeButtons();
}

void MainMenu::initializeButtons() {
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

void MainMenu::render() {
    renderer.render(buttons);
}

MenuAction MainMenu::handleButtonClick(int buttonIndex) {
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
