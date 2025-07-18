#include "../../includes/Application/BodyPartSelectorLogic.hpp"

BodyPartSelectorLogic::BodyPartSelectorLogic() {
    // No initialization needed
}

MenuAction BodyPartSelectorLogic::handleButtonClick(int buttonIndex, BodyPart& selectedPart) {
    // Get the main body parts list (guaranteed to match button creation)
    std::vector<BodyPart> mainBodyParts = getCustomizableBodyParts();

    if (buttonIndex < static_cast<int>(mainBodyParts.size())) {
        // Select body part
        selectedPart = mainBodyParts[buttonIndex];
        return MENU_ACTION_BODY_PART_DETAIL;
    } else if (buttonIndex == static_cast<int>(mainBodyParts.size())) {
        // Back to settings
        return MENU_ACTION_SETTINGS;
    } else {
        // Back to main menu
        return MENU_ACTION_BACK_TO_MENU;
    }
}

std::vector<BodyPart> BodyPartSelectorLogic::getCustomizableBodyParts() const {
    return {
        BODY_PART_HEAD,
        BODY_PART_NECK,
        BODY_PART_TORSO,
        BODY_PART_EYES,
        BODY_PART_LEFT_SHOULDER,
        BODY_PART_RIGHT_SHOULDER,
        BODY_PART_LEFT_UPPER_ARM,
        BODY_PART_RIGHT_UPPER_ARM,
        BODY_PART_LEFT_FOREARM,
        BODY_PART_RIGHT_FOREARM,
        BODY_PART_LEFT_THIGH,
        BODY_PART_RIGHT_THIGH,
        BODY_PART_LEFT_LOWER_LEG,
        BODY_PART_RIGHT_LOWER_LEG
    };
}

std::string BodyPartSelectorLogic::getBodyPartName(BodyPart part) const {
    switch (part) {
        case BODY_PART_HEAD: return "Head";
        case BODY_PART_NECK: return "Neck";
        case BODY_PART_TORSO: return "Torso";
        case BODY_PART_LEFT_ARM: return "Left Arm";
        case BODY_PART_RIGHT_ARM: return "Right Arm";
        case BODY_PART_LEFT_LEG: return "Left Leg";
        case BODY_PART_RIGHT_LEG: return "Right Leg";
        case BODY_PART_LEFT_SHOULDER: return "Left Shoulder";
        case BODY_PART_RIGHT_SHOULDER: return "Right Shoulder";
        case BODY_PART_LEFT_UPPER_ARM: return "Left Upper Arm";
        case BODY_PART_LEFT_FOREARM: return "Left Forearm";
        case BODY_PART_RIGHT_UPPER_ARM: return "Right Upper Arm";
        case BODY_PART_RIGHT_FOREARM: return "Right Forearm";
        case BODY_PART_LEFT_THIGH: return "Left Thigh";
        case BODY_PART_LEFT_LOWER_LEG: return "Left Lower Leg";
        case BODY_PART_RIGHT_THIGH: return "Right Thigh";
        case BODY_PART_RIGHT_LOWER_LEG: return "Right Lower Leg";
        case BODY_PART_EYES: return "Eyes";
        default: return "Unknown";
    }
}
