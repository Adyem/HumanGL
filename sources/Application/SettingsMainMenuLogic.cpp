#include "../../includes/Application/SettingsMainMenuLogic.hpp"

SettingsMainMenuLogic::SettingsMainMenuLogic() {
    // No initialization needed for main menu logic
}

MenuAction SettingsMainMenuLogic::handleButtonClick(int buttonIndex) {
    switch (buttonIndex) {
        case 0: // Body Customization
            return MENU_ACTION_BODY_CUSTOMIZATION;
        case 1: // Background Colors
            return MENU_ACTION_BACKGROUND_CUSTOMIZATION;
        case 2: // Back to Menu
            return MENU_ACTION_BACK_TO_MENU;
        default:
            return MENU_ACTION_NONE;
    }
}
