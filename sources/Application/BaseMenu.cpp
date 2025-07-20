#include "../../includes/Application/BaseMenu.hpp"

BaseMenu::BaseMenu(MouseHandler& mouseHandler, MenuInputInterface& menuInput, int winWidth, int winHeight)
    : mouseHandler(mouseHandler), menuInput(menuInput), windowWidth(winWidth), windowHeight(winHeight),
      keyboardState(SDL_GetKeyboardState(nullptr)), escapePressed(false), prevEscapeState(false) {
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
    updateInput();

    // Check for menu navigation keys
    if (isEscapePressed()) {
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

void BaseMenu::updateInput() {
    if (!keyboardState) return;

    // Update keyboard state
    keyboardState = SDL_GetKeyboardState(nullptr);

    // Check for ESC key press (single press detection)
    bool currentEscapeState = keyboardState[SDL_SCANCODE_ESCAPE] != 0;

    escapePressed = currentEscapeState && !prevEscapeState;
    prevEscapeState = currentEscapeState;
}

int BaseMenu::checkButtonClick() {
    return mouseHandler.checkButtonClick(buttons);
}
