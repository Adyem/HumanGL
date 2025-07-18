#include "../../includes/Application/MenuSystem.hpp"

MenuSystem::MenuSystem()
    : mainMenuRenderer(textRenderer), settingsMenuRenderer(textRenderer), creditsMenuRenderer(textRenderer), instructionsMenuRenderer(textRenderer),
      mainMenu(mainMenuRenderer, mouseHandler, menuInputStub, HUMANGL_DEFAULT_WINDOW_WIDTH, HUMANGL_DEFAULT_WINDOW_HEIGHT),
      creditsMenu(creditsMenuRenderer, mouseHandler, menuInputStub, HUMANGL_DEFAULT_WINDOW_WIDTH, HUMANGL_DEFAULT_WINDOW_HEIGHT),
      instructionsMenu(instructionsMenuRenderer, mouseHandler, menuInputStub, HUMANGL_DEFAULT_WINDOW_WIDTH, HUMANGL_DEFAULT_WINDOW_HEIGHT),
      currentState(MAIN_MENU), windowWidth(HUMANGL_DEFAULT_WINDOW_WIDTH), windowHeight(HUMANGL_DEFAULT_WINDOW_HEIGHT) {
    // Settings use SettingsMenuRenderer directly (no wrapper needed)
}

MenuSystem::~MenuSystem() {
    cleanup();
}

bool MenuSystem::initialize(int winWidth, int winHeight) {
    windowWidth = winWidth;
    windowHeight = winHeight;
    
    // Initialize all subsystems
    if (!textRenderer.initialize()) {
        return false;
    }
    
    // MenuInput functionality moved to EventHandler - no initialization needed
    
    // Update renderers with window size
    mainMenuRenderer.updateWindowSize(windowWidth, windowHeight);
    settingsMenuRenderer.updateWindowSize(windowWidth, windowHeight);
    creditsMenuRenderer.updateWindowSize(windowWidth, windowHeight);
    instructionsMenuRenderer.updateWindowSize(windowWidth, windowHeight);
    
    // Menu initialization is handled by individual menu classes
    
    return true;
}

void MenuSystem::cleanup() {
    textRenderer.cleanup();
}

void MenuSystem::updateWindowSize(int width, int height) {
    windowWidth = width;
    windowHeight = height;
    mainMenuRenderer.updateWindowSize(width, height);
    settingsMenuRenderer.updateWindowSize(width, height);
    creditsMenuRenderer.updateWindowSize(width, height);
    instructionsMenuRenderer.updateWindowSize(width, height);

    // Update menu instances for new window size
    mainMenu.updateWindowSize(width, height);
    creditsMenu.updateWindowSize(width, height);
    instructionsMenu.updateWindowSize(width, height);
}

void MenuSystem::setState(AppState state) {
    // If we're entering settings from another state, reset to main settings page
    if (state == SETTINGS && currentState != SETTINGS) {
        settingsMenuRenderer.resetToMainPage();
    }

    currentState = state;
}

AppState MenuSystem::getState() const {
    return currentState;
}



MenuAction MenuSystem::handleEvent(const SDL_Event& event) {
    MenuAction action = MENU_ACTION_NONE;

    // Delegate event handling to the appropriate menu
    switch (currentState) {
        case MAIN_MENU:
            action = mainMenu.handleEvent(event);
            break;
        case SETTINGS:
            action = handleSettingsEvent(event);
            break;
        case CREDITS:
            action = creditsMenu.handleEvent(event);
            break;
        case INSTRUCTIONS:
            action = instructionsMenu.handleEvent(event);
            break;
        case SIMULATION:
            // Simulation events are handled by Application class
            break;
    }

    // Process menu actions using setState to ensure proper state transitions
    switch (action) {
        case MENU_ACTION_START_SIMULATION:
            setState(SIMULATION);
            break;
        case MENU_ACTION_SETTINGS:
            setState(SETTINGS);
            break;
        case MENU_ACTION_CREDITS:
            setState(CREDITS);
            break;
        case MENU_ACTION_INSTRUCTIONS:
            setState(INSTRUCTIONS);
            break;
        case MENU_ACTION_BACK_TO_MENU:
            setState(MAIN_MENU);
            break;
        default:
            break;
    }

    return action;
}

// Settings-specific event handling (follows BaseMenu pattern)
MenuAction MenuSystem::handleSettingsEvent(const SDL_Event& event) {
    MenuAction action = MENU_ACTION_NONE;

    switch (event.type) {
        case SDL_MOUSEMOTION:
            mouseHandler.updateMousePosition(event.motion.x, event.motion.y);
            updateSettingsButtonHover();
            // Also update hover for custom UI elements (sliders, color selectors)
            settingsMenuRenderer.updateHover(static_cast<float>(event.motion.x), static_cast<float>(event.motion.y));
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                mouseHandler.setMousePressed(true);
            }
            break;

        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT) {
                mouseHandler.setMouseReleased(true);

                // First check if it's a button click
                int clickedButton = checkSettingsButtonClick();
                if (clickedButton >= 0) {
                    action = settingsMenuRenderer.handleButtonClick(clickedButton);
                } else {
                    // If no button was clicked, check for custom UI interactions (sliders, color selectors)
                    float mouseX = static_cast<float>(event.button.x);
                    float mouseY = static_cast<float>(event.button.y);
                    settingsMenuRenderer.handleMouseClick(mouseX, mouseY);
                }

                // Handle mouse up for custom UI elements
                settingsMenuRenderer.handleMouseUp();
            }
            break;

        case SDL_KEYDOWN:
            menuInputStub.handleKeyEvent(event);
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                action = MENU_ACTION_BACK_TO_MENU;
            }
            break;

        default:
            break;
    }

    return action;
}

void MenuSystem::updateSettingsButtonHover() {
    // Update hover for the current page's buttons
    const std::vector<MenuButton>& buttons = settingsMenuRenderer.getButtons();
    mouseHandler.updateButtonHover(const_cast<std::vector<MenuButton>&>(buttons));
    // Also update hover for the renderer's button system
    settingsMenuRenderer.updateButtonHover(mouseHandler);
}

int MenuSystem::checkSettingsButtonClick() {
    const std::vector<MenuButton>& buttons = settingsMenuRenderer.getButtons();
    return mouseHandler.checkButtonClick(const_cast<std::vector<MenuButton>&>(buttons));
}

MenuAction MenuSystem::updateSettings() {
    MenuAction action = MENU_ACTION_NONE;

    // Update input system
    menuInputStub.update();

    // Handle settings-specific input (keyboard shortcuts for customization)
    settingsMenuRenderer.handleInput();

    // Reset input states
    menuInputStub.resetKeyStates();
    mouseHandler.resetMouseState();

    return action;
}

MenuAction MenuSystem::update() {
    MenuAction action = MENU_ACTION_NONE;

    // Delegate update to the appropriate menu
    switch (currentState) {
        case MAIN_MENU:
            action = mainMenu.update();
            break;
        case SETTINGS:
            action = updateSettings();
            break;
        case CREDITS:
            action = creditsMenu.update();
            break;
        case INSTRUCTIONS:
            action = instructionsMenu.update();
            break;
        case SIMULATION:
            // Simulation input is now handled by EventHandler
            // No menu input handling needed here
            break;
    }

    // Process menu actions
    switch (action) {
        case MENU_ACTION_RETURN_TO_MENU:
            currentState = MAIN_MENU;
            break;
        case MENU_ACTION_EXIT:
            // Return to main menu when ESC is pressed
            currentState = MAIN_MENU;
            break;
        default:
            break;
    }

    return action;
}

void MenuSystem::render() {
    // Set menu background color from settings
    const Color& menuBgColor = settingsMenuRenderer.getMenuBackgroundColor();
    glClearColor(menuBgColor.r, menuBgColor.g, menuBgColor.b, menuBgColor.a);

    // Clear the screen with the background color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    switch (currentState) {
        case MAIN_MENU:
            mainMenu.render();
            break;
        case SETTINGS:
            settingsMenuRenderer.render();
            break;
        case CREDITS:
            creditsMenu.render();
            break;
        case INSTRUCTIONS:
            instructionsMenu.render();
            break;
        case SIMULATION:
            // Simulation rendering is handled by Application class
            break;
    }
}




