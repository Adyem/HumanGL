#pragma once

#include "../humangl.hpp"

class SettingsMainMenuLogic {
public:
    SettingsMainMenuLogic();
    virtual ~SettingsMainMenuLogic() = default;

    // Handle button clicks - returns navigation action
    MenuAction handleButtonClick(int buttonIndex);

};
