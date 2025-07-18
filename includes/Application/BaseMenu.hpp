#pragma once

#include "../humangl.hpp"
#include "../Input/MouseHandler.hpp"
#include "../Input/MenuInput.hpp"

class BaseMenu {
protected:
    std::vector<MenuButton> buttons;
    MouseHandler& mouseHandler;
    MenuInput& menuInput;
    int windowWidth;
    int windowHeight;

public:
    BaseMenu(MouseHandler& mouseHandler, MenuInput& menuInput, int winWidth, int winHeight);
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

protected:
    // Helper methods for derived classes
    virtual void updateButtonHover();
    int checkButtonClick();
};
