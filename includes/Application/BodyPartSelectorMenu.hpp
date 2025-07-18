#pragma once

#include "../humangl.hpp"

class BodyPartSelectorLogic {
public:
    BodyPartSelectorLogic();
    virtual ~BodyPartSelectorLogic() = default;

    // Handle button clicks - returns selected body part or navigation action
    MenuAction handleButtonClick(int buttonIndex, BodyPart& selectedPart);

    // Get list of customizable body parts
    std::vector<BodyPart> getCustomizableBodyParts() const;

    // Get body part name as string
    std::string getBodyPartName(BodyPart part) const;
};
