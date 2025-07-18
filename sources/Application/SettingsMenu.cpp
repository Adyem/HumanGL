#include "../../includes/Application/SettingsMenu.hpp"



SettingsMenu::SettingsMenu(SettingsMenuRenderer& renderer, MouseHandler& mouseHandler, MenuInput& menuInput, int winWidth, int winHeight)
    : BaseMenu(mouseHandler, menuInput, winWidth, winHeight), renderer(renderer) {
    initializeButtons();
}

void SettingsMenu::initializeButtons() {
    // Reset to main page when initializing (ensures we start at main settings)
    renderer.resetToMainPage();

    // Get the buttons from the renderer and ensure they're properly synced
    buttons = renderer.getButtons();
}

void SettingsMenu::render() {
    // Let the renderer handle its own rendering
    renderer.render();
}

MenuAction SettingsMenu::handleButtonClick(int buttonIndex) {
    // Delegate button handling to the renderer
    MenuAction action = renderer.handleButtonClick(buttonIndex);

    // Force immediate button sync after any page changes
    buttons = renderer.getButtons();

    // Update hover states immediately after button sync
    updateButtonHover();

    return action;
}

MenuAction SettingsMenu::handleEvent(const SDL_Event& event) {
    MenuAction action = MENU_ACTION_NONE;

    switch (event.type) {
        case SDL_MOUSEMOTION: {
            // Update mouse position in handler
            mouseHandler.updateMousePosition(event.motion.x, event.motion.y);

            // Force button sync and update hover state immediately
            buttons = renderer.getButtons();
            mouseHandler.updateButtonHover(buttons);

            // Update custom UI element hover state
            float mouseX = static_cast<float>(event.motion.x);
            float mouseY = static_cast<float>(event.motion.y);
            renderer.updateHover(mouseX, mouseY);
            break;
        }

        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                mouseHandler.setMousePressed(true);

                // Check for clicks on custom UI elements first
                float mouseX = static_cast<float>(event.button.x);
                float mouseY = static_cast<float>(event.button.y);
                if (renderer.handleMouseClick(mouseX, mouseY)) {
                    // Click was handled by custom UI
                    return MENU_ACTION_NONE;
                }
            }
            break;

        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT) {
                mouseHandler.setMouseReleased(true);

                // Stop slider dragging
                renderer.updateHover(-1, -1); // Signal to stop dragging

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

MenuAction SettingsMenu::update() {
    // Call base class update first
    MenuAction action = BaseMenu::update();

    // Ensure button hover states are continuously updated
    updateButtonHover();

    return action;
}

void SettingsMenu::updateButtonHover() {
    // Always sync with renderer's buttons first - this is critical!
    const std::vector<MenuButton>& rendererButtons = renderer.getButtons();
    buttons = rendererButtons;

    // Then update hover states on the synced buttons
    mouseHandler.updateButtonHover(buttons);
}
