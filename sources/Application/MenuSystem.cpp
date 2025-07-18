#include "../../includes/Application/MenuSystem.hpp"

MenuSystem::MenuSystem()
    : mainMenuRenderer(textRenderer), settingsMenuRenderer(textRenderer), creditsMenuRenderer(textRenderer), instructionsMenuRenderer(textRenderer),
      mainMenu(mainMenuRenderer, mouseHandler, menuInputStub, HUMANGL_DEFAULT_WINDOW_WIDTH, HUMANGL_DEFAULT_WINDOW_HEIGHT),
      settingsMenu(settingsMenuRenderer, mouseHandler, menuInputStub, HUMANGL_DEFAULT_WINDOW_WIDTH, HUMANGL_DEFAULT_WINDOW_HEIGHT),
      creditsMenu(creditsMenuRenderer, mouseHandler, menuInputStub, HUMANGL_DEFAULT_WINDOW_WIDTH, HUMANGL_DEFAULT_WINDOW_HEIGHT),
      instructionsMenu(instructionsMenuRenderer, mouseHandler, menuInputStub, HUMANGL_DEFAULT_WINDOW_WIDTH, HUMANGL_DEFAULT_WINDOW_HEIGHT),
      currentState(MAIN_MENU), windowWidth(HUMANGL_DEFAULT_WINDOW_WIDTH), windowHeight(HUMANGL_DEFAULT_WINDOW_HEIGHT) {
    // Input handling is now integrated into SettingsMenuRenderer and EventHandler
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
    settingsMenu.updateWindowSize(width, height);
    creditsMenu.updateWindowSize(width, height);
    instructionsMenu.updateWindowSize(width, height);
}

void MenuSystem::setState(AppState state) {
    // If we're entering settings from another state, reset to main settings page
    if (state == SETTINGS && currentState != SETTINGS) {
        settingsMenuRenderer.resetToMainPage();
        settingsMenu.initializeButtons();
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
            action = settingsMenu.handleEvent(event);
            // Handle settings customization input (now integrated into SettingsMenuRenderer)
            settingsMenuRenderer.handleInput();
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

MenuAction MenuSystem::update() {
    MenuAction action = MENU_ACTION_NONE;

    // Delegate update to the appropriate menu
    switch (currentState) {
        case MAIN_MENU:
            action = mainMenu.update();
            break;
        case SETTINGS:
            action = settingsMenu.update();
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
            settingsMenu.render();
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




