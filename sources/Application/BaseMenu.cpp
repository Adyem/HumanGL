#include "../../includes/Application/BaseMenu.hpp"

BaseMenu::BaseMenu(MouseHandler& mouseHandler, MenuInput& menuInput, int winWidth, int winHeight)
    : mouseHandler(mouseHandler), menuInput(menuInput), windowWidth(winWidth), windowHeight(winHeight) {
}

void BaseMenu::updateWindowSize(int width, int height) {
    windowWidth = width;
    windowHeight = height;
    initializeButtons(); // Reinitialize buttons for new window size
}

const std::vector<MenuButton>& BaseMenu::getButtons() const {
    return buttons;
}

MenuAction BaseMenu::handleEvent(const SDL_Event& event) {
    MenuAction action = MENU_ACTION_NONE;
    
    switch (event.type) {
        case SDL_MOUSEMOTION:
            mouseHandler.updateMousePosition(event.motion.x, event.motion.y);
            updateButtonHover();
            break;
            
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                mouseHandler.setMousePressed(true);
            }
            break;
            
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT) {
                mouseHandler.setMouseReleased(true);
                int clickedButton = checkButtonClick();
                if (clickedButton >= 0) {
                    action = handleButtonClick(clickedButton);
                }
            }
            break;
            
        case SDL_KEYDOWN:
            menuInput.handleKeyEvent(event);
            break;
            
        default:
            break;
    }
    
    return action;
}

MenuAction BaseMenu::update() {
    MenuAction action = MENU_ACTION_NONE;
    
    // Update input system
    menuInput.update();
    
    // Check for menu navigation keys
    if (menuInput.isEscapePressed()) {
        action = MENU_ACTION_EXIT;
    }
    
    // Reset input states
    menuInput.resetKeyStates();
    mouseHandler.resetMouseState();
    
    return action;
}

void BaseMenu::updateButtonHover() {
    mouseHandler.updateButtonHover(buttons);
}

int BaseMenu::checkButtonClick() {
    return mouseHandler.checkButtonClick(buttons);
}
