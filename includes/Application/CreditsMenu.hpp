#pragma once

#include "../humangl.hpp"
#include "BaseMenu.hpp"
#include "../Menus/CreditsMenuRenderer.hpp"

class CreditsMenu : public BaseMenu {
private:
    CreditsMenuRenderer& renderer;

public:
    CreditsMenu(CreditsMenuRenderer& renderer, MouseHandler& mouseHandler, MenuInput& menuInput, int winWidth, int winHeight);
    virtual ~CreditsMenu() = default;

    // Implement pure virtual methods from BaseMenu
    void initializeButtons() override;
    void render() override;
    MenuAction handleButtonClick(int buttonIndex) override;
};
