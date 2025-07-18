#pragma once

#include "../humangl.hpp"
#include "../Menus/TextRenderer.hpp"
#include "../Menus/MenuRenderer.hpp"
#include "../Menus/MainMenuRenderer.hpp"
#include "../Menus/SettingsMenuRenderer.hpp"
#include "../Menus/CreditsMenuRenderer.hpp"
#include "../Menus/InstructionsMenuRenderer.hpp"
#include "../Input/MouseHandler.hpp"
#include "../Input/MenuInput.hpp"
#include "../Input/SettingsInputHandler.hpp"
#include "BaseMenu.hpp"
#include "MainMenu.hpp"
#include "SettingsMenu.hpp"
#include "CreditsMenu.hpp"
#include "InstructionsMenu.hpp"

class MenuSystem {
private:
    // Static instances of utility classes
    TextRenderer textRenderer;
    MainMenuRenderer mainMenuRenderer;
    SettingsMenuRenderer settingsMenuRenderer;
    CreditsMenuRenderer creditsMenuRenderer;
    InstructionsMenuRenderer instructionsMenuRenderer;
    MouseHandler mouseHandler;
    MenuInput menuInput;
    SettingsInputHandler settingsInputHandler;

    // Menu instances
    MainMenu mainMenu;
    SettingsMenu settingsMenu;
    CreditsMenu creditsMenu;
    InstructionsMenu instructionsMenu;
    
    // Current state
    AppState currentState;
    int windowWidth;
    int windowHeight;

public:
    MenuSystem();
    ~MenuSystem();
    
    // Initialize the menu system
    bool initialize(int winWidth, int winHeight);
    
    // Clean up resources
    void cleanup();
    
    // Update window dimensions
    void updateWindowSize(int width, int height);
    
    // Set current menu state
    void setState(AppState state);
    AppState getState() const;
    
    // Handle SDL events
    MenuAction handleEvent(const SDL_Event& event);
    
    // Update menu system (call each frame)
    MenuAction update();

    // Get settings renderer for color access
    SettingsMenuRenderer& getSettingsMenuRenderer() { return settingsMenuRenderer; }

    // Render current menu
    void render();
};
