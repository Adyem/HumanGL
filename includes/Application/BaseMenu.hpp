#pragma once

#include "../humangl.hpp"
#include "../Input/MouseHandler.hpp"
// Simple interface for menu input (functionality moved to EventHandler)
class MenuInputInterface {
public:
    virtual ~MenuInputInterface() = default;
    virtual bool isEscapePressed() const = 0;
    virtual bool isMKeyPressed() const = 0;
    virtual void resetKeyStates() = 0;
    virtual void handleKeyEvent(const SDL_Event& event) = 0;
    virtual void update() = 0;
};

class BaseMenu {
protected:
    std::vector<MenuButton> buttons;
    MouseHandler& mouseHandler;
    MenuInputInterface& menuInput;
    int windowWidth;
    int windowHeight;

    // ESC key handling
    const Uint8* keyboardState;
    bool escapePressed;
    bool prevEscapeState;

public:
    BaseMenu(MouseHandler& mouseHandler, MenuInputInterface& menuInput, int winWidth, int winHeight);
    virtual ~BaseMenu() = default;

    // Pure virtual methods that must be implemented by derived classes
    virtual void initializeButtons() = 0;
    virtual void render() = 0;
    virtual MenuAction handleButtonClick(int buttonIndex) = 0;

    // Common functionality
    void updateWindowSize(int width, int height);
    const std::vector<MenuButton>& getButtons() const;
    virtual MenuAction handleEvent(const SDL_Event& event);
    virtual MenuAction update();

    // Input handling
    void updateInput();
    bool isEscapePressed() const { return escapePressed; }

protected:
    // Helper methods for derived classes
    virtual void updateButtonHover();
    int checkButtonClick();
};
