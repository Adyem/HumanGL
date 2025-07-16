#include "../../includes/Application/InstructionsMenu.hpp"

InstructionsMenu::InstructionsMenu(InstructionsMenuRenderer& renderer, MouseHandler& mouseHandler, MenuInput& menuInput, int winWidth, int winHeight)
    : BaseMenu(mouseHandler, menuInput, winWidth, winHeight), renderer(renderer) {
    initializeButtons();
}

void InstructionsMenu::initializeButtons() {
    float buttonWidth = 200.0f;
    float buttonHeight = 50.0f;
    float centerX = (static_cast<float>(windowWidth) - buttonWidth) / 2.0f;
    float startY = static_cast<float>(windowHeight) - 100.0f;

    buttons.clear();
    buttons.push_back(MenuButton(centerX, startY, buttonWidth, buttonHeight, "Back to Menu"));
}

void InstructionsMenu::render() {
    renderer.render(buttons);
}

MenuAction InstructionsMenu::handleButtonClick(int buttonIndex) {
    switch (buttonIndex) {
        case 0: // Back to Menu
            return MENU_ACTION_BACK_TO_MENU;
        default:
            return MENU_ACTION_NONE;
    }
}
