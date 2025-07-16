#pragma once

#include "../humangl.hpp"
#include "BaseMenu.hpp"
#include "../Menus/MainMenuRenderer.hpp"

class MainMenu : public BaseMenu {
private:
    MainMenuRenderer& renderer;

public:
    MainMenu(MainMenuRenderer& renderer, MouseHandler& mouseHandler, MenuInput& menuInput, int winWidth, int winHeight);
    virtual ~MainMenu() = default;

    // Implement pure virtual methods from BaseMenu
    void initializeButtons() override;
    void render() override;
    MenuAction handleButtonClick(int buttonIndex) override;
};
