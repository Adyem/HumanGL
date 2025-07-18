#include "../../includes/Application/CreditsMenu.hpp"

CreditsMenu::CreditsMenu(CreditsMenuRenderer& renderer, MouseHandler& mouseHandler, MenuInputInterface& menuInput, int winWidth, int winHeight)
    : BaseMenu(mouseHandler, menuInput, winWidth, winHeight), renderer(renderer) {
    initializeButtons();
}

void CreditsMenu::initializeButtons() {
    float buttonWidth = HUMANGL_MENU_BUTTON_WIDTH;
    float buttonHeight = HUMANGL_MENU_BUTTON_HEIGHT;
    float centerX = (static_cast<float>(windowWidth) - buttonWidth) / 2.0f;
    float startY = static_cast<float>(windowHeight) / 2.0f + HUMANGL_MENU_SETTINGS_OFFSET_Y;

    buttons.clear();
    buttons.push_back(MenuButton(centerX, startY, buttonWidth, buttonHeight, "Back to Menu"));
}

void CreditsMenu::render() {
    renderer.render(buttons);
}

MenuAction CreditsMenu::handleButtonClick(int buttonIndex) {
    switch (buttonIndex) {
        case 0: // Back to Menu
            return MENU_ACTION_BACK_TO_MENU;
        default:
            return MENU_ACTION_NONE;
    }
}
