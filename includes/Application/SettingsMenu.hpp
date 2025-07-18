#pragma once

#include "../humangl.hpp"
#include "BaseMenu.hpp"
#include "../Menus/SettingsMenuRenderer.hpp"

class SettingsMenu : public BaseMenu {
private:
    SettingsMenuRenderer& renderer;

public:
    SettingsMenu(SettingsMenuRenderer& renderer, MouseHandler& mouseHandler, MenuInputInterface& menuInput, int winWidth, int winHeight);
    virtual ~SettingsMenu() = default;

    // Implement pure virtual methods from BaseMenu
    void initializeButtons() override;
    void render() override;
    MenuAction handleButtonClick(int buttonIndex) override;

    // Override event handling for custom mouse interactions
    MenuAction handleEvent(const SDL_Event& event) override;

    // Override update to ensure continuous hover updates
    MenuAction update() override;

protected:
    // Override to ensure hover works with renderer's buttons
    void updateButtonHover() override;
};
