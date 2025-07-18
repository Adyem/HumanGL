#pragma once

#include "../humangl.hpp"
#include "../Menus/TextRenderer.hpp"
#include "../Menus/MenuRenderer.hpp"
#include "../Menus/MainMenuRenderer.hpp"
#include "../Menus/SettingsMenuRenderer.hpp"
#include "../Menus/CreditsMenuRenderer.hpp"
#include "../Menus/InstructionsMenuRenderer.hpp"
#include "../Input/MouseHandler.hpp"
#include "BaseMenu.hpp"
#include "MainMenu.hpp"
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

    // Temporary stub for MenuInput (functionality moved to EventHandler)
    class MenuInputStub : public MenuInputInterface {
    public:
        bool isEscapePressed() const override { return false; }
        bool isMKeyPressed() const override { return false; }
        void resetKeyStates() override {}
        void handleKeyEvent(const SDL_Event&) override {}
        void update() override {}
    } menuInputStub;

    // Menu instances
    MainMenu mainMenu;
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

private:
    // Settings-specific event handling (follows BaseMenu pattern)
    MenuAction handleSettingsEvent(const SDL_Event& event);
    void updateSettingsButtonHover();
    int checkSettingsButtonClick();
    MenuAction updateSettings();


};
