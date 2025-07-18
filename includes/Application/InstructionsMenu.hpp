#pragma once

#include "../humangl.hpp"
#include "BaseMenu.hpp"
#include "../Menus/InstructionsMenuRenderer.hpp"

class InstructionsMenu : public BaseMenu {
private:
    InstructionsMenuRenderer& renderer;

public:
    InstructionsMenu(InstructionsMenuRenderer& renderer, MouseHandler& mouseHandler, MenuInputInterface& menuInput, int winWidth, int winHeight);
    virtual ~InstructionsMenu() = default;

    // Implement pure virtual methods from BaseMenu
    void initializeButtons() override;
    void render() override;
    MenuAction handleButtonClick(int buttonIndex) override;
};
