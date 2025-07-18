#include "../../includes/Application/BodyPartEditorMenu.hpp"

BodyPartEditorLogic::BodyPartEditorLogic()
    : selectedBodyPart(BODY_PART_HEAD), currentColorIndex(0), isDraggingSlider(false), isMousePressed(false),
      keyboardState(SDL_GetKeyboardState(nullptr)), plusKeyPressed(false), minusKeyPressed(false), cKeyPressed(false) {
    initializeAvailableColors();

    // Initialize default body part settings
    for (int i = 0; i < BODY_PART_COUNT; i++) {
        BodyPart part = static_cast<BodyPart>(i);
        bodyPartSettings[part] = getDefaultBodyPartSettings(part);
    }
}

void BodyPartEditorLogic::setSelectedBodyPart(BodyPart part) {
    selectedBodyPart = part;
    
    // Update color index to match the selected body part's current color
    Color currentColor = bodyPartSettings[selectedBodyPart].color;
    currentColorIndex = 0; // Default to first color
    for (size_t i = 0; i < availableColors.size(); i++) {
        if (availableColors[i].r == currentColor.r &&
            availableColors[i].g == currentColor.g &&
            availableColors[i].b == currentColor.b) {
            currentColorIndex = static_cast<int>(i);
            break;
        }
    }
}

void BodyPartEditorLogic::setBodyPartSettings(const std::map<BodyPart, BodyPartSettings>& settings) {
    bodyPartSettings = settings;
}

MenuAction BodyPartEditorLogic::handleButtonClick(int buttonIndex) {
    switch (buttonIndex) {
        case 0: // Reset to Default
            resetBodyPartToDefault();
            return MENU_ACTION_NONE;
        case 1: // Back to Body Parts
            return MENU_ACTION_BODY_CUSTOMIZATION;
        case 2: // Back to Settings
            return MENU_ACTION_SETTINGS;
        case 3: // Back to Main Menu
            return MENU_ACTION_BACK_TO_MENU;
        default:
            return MENU_ACTION_NONE;
    }
}

bool BodyPartEditorLogic::handleMouseClick(float mouseX, float mouseY, float sliderX, float sliderY,
                                          float sliderWidth, float sliderHeight, float colorSelectorX,
                                          float colorSelectorY, float colorSelectorSize) {
    // Set mouse pressed state
    isMousePressed = true;

    // Check if clicked on slider
    if (mouseX >= sliderX && mouseX <= sliderX + sliderWidth &&
        mouseY >= sliderY && mouseY <= sliderY + sliderHeight) {

        // Calculate new scale value based on click position
        float normalizedPos = (mouseX - sliderX) / sliderWidth;
        float newScale = HUMANGL_SLIDER_MIN_VALUE + normalizedPos * (HUMANGL_SLIDER_MAX_VALUE - HUMANGL_SLIDER_MIN_VALUE);
        setBodyPartScale(newScale);
        isDraggingSlider = true;
        return true;
    }

    // Check if clicked on color selector
    if (mouseX >= colorSelectorX && mouseX <= colorSelectorX + colorSelectorSize &&
        mouseY >= colorSelectorY && mouseY <= colorSelectorY + colorSelectorSize) {

        // Cycle to next color
        cycleBodyPartColor();
        return true;
    }

    isDraggingSlider = false;
    return false;
}

void BodyPartEditorLogic::updateHover(float mouseX, float mouseY, float sliderX, float /* sliderY */,
                                     float sliderWidth, float /* sliderHeight */) {
    // Handle mouse up signal (negative coordinates)
    if (mouseX < 0 || mouseY < 0) {
        isDraggingSlider = false;
        isMousePressed = false;
        return;
    }

    // Update slider dragging if mouse button is held down AND we're dragging the slider
    if (isDraggingSlider && isMousePressed && sliderWidth > 0) {
        float normalizedPos = std::max(0.0f, std::min(1.0f, (mouseX - sliderX) / sliderWidth));
        float newScale = HUMANGL_SLIDER_MIN_VALUE + normalizedPos * (HUMANGL_SLIDER_MAX_VALUE - HUMANGL_SLIDER_MIN_VALUE);
        setBodyPartScale(newScale);
    }
}

void BodyPartEditorLogic::handleMouseUp() {
    isDraggingSlider = false;
    isMousePressed = false;
}

void BodyPartEditorLogic::handleInput() {
    if (!keyboardState) return;
    
    handleCustomizationInput();
}

void BodyPartEditorLogic::cycleBodyPartColor() {
    currentColorIndex = (currentColorIndex + 1) % availableColors.size();
    bodyPartSettings[selectedBodyPart].color = availableColors[currentColorIndex];
}

void BodyPartEditorLogic::adjustBodyPartScale(float scaleMultiplier) {
    BodyPartSettings& settings = bodyPartSettings[selectedBodyPart];
    settings.scale.x = std::max(HUMANGL_SLIDER_MIN_VALUE, std::min(HUMANGL_SLIDER_MAX_VALUE, settings.scale.x * scaleMultiplier));
    settings.scale.y = std::max(HUMANGL_SLIDER_MIN_VALUE, std::min(HUMANGL_SLIDER_MAX_VALUE, settings.scale.y * scaleMultiplier));
    settings.scale.z = std::max(HUMANGL_SLIDER_MIN_VALUE, std::min(HUMANGL_SLIDER_MAX_VALUE, settings.scale.z * scaleMultiplier));
}

void BodyPartEditorLogic::setBodyPartScale(float newScale) {
    BodyPartSettings& settings = bodyPartSettings[selectedBodyPart];
    float clampedScale = std::max(HUMANGL_SLIDER_MIN_VALUE, std::min(HUMANGL_SLIDER_MAX_VALUE, newScale));
    settings.scale.x = clampedScale;
    settings.scale.y = clampedScale;
    settings.scale.z = clampedScale;
}

void BodyPartEditorLogic::resetBodyPartToDefault() {
    // Reset current body part to proper default settings
    bodyPartSettings[selectedBodyPart] = getDefaultBodyPartSettings(selectedBodyPart);

    // Reset color index to match the default color
    Color defaultColor = bodyPartSettings[selectedBodyPart].color;
    currentColorIndex = 0; // Find matching color index
    for (size_t i = 0; i < availableColors.size(); i++) {
        if (availableColors[i].r == defaultColor.r &&
            availableColors[i].g == defaultColor.g &&
            availableColors[i].b == defaultColor.b) {
            currentColorIndex = static_cast<int>(i);
            break;
        }
    }
}

const BodyPartSettings& BodyPartEditorLogic::getBodyPartSettings(BodyPart part) const {
    return bodyPartSettings.at(part);
}

const std::map<BodyPart, BodyPartSettings>& BodyPartEditorLogic::getAllBodyPartSettings() const {
    return bodyPartSettings;
}

std::string BodyPartEditorLogic::getBodyPartName(BodyPart part) const {
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

void BodyPartEditorLogic::initializeAvailableColors() {
    availableColors.clear();
    availableColors.push_back(Color::SkinTone());
    availableColors.push_back(Color::ClothingBlue());
    availableColors.push_back(Color::Red());
    availableColors.push_back(Color::Green());
    availableColors.push_back(Color::Blue());
    availableColors.push_back(Color::Yellow());
    availableColors.push_back(Color::Magenta());
    availableColors.push_back(Color::Cyan());
    availableColors.push_back(Color::White());
    availableColors.push_back(Color::Black());
}

BodyPartSettings BodyPartEditorLogic::getDefaultBodyPartSettings(BodyPart part) const {
    BodyPartSettings settings;

    // Set default colors based on body part type
    switch (part) {
        // Skin color parts (head, neck, forearms, lower legs)
        case BODY_PART_HEAD:
        case BODY_PART_NECK:
        case BODY_PART_LEFT_FOREARM:
        case BODY_PART_RIGHT_FOREARM:
        case BODY_PART_LEFT_LOWER_LEG:
        case BODY_PART_RIGHT_LOWER_LEG:
            settings.color = Color::SkinTone();
            break;

        // Blue clothing parts (torso, shoulders, upper arms)
        case BODY_PART_TORSO:
        case BODY_PART_LEFT_SHOULDER:
        case BODY_PART_RIGHT_SHOULDER:
        case BODY_PART_LEFT_UPPER_ARM:
        case BODY_PART_RIGHT_UPPER_ARM:
            settings.color = Color::ClothingBlue();
            break;

        // Dark blue pants (thighs)
        case BODY_PART_LEFT_THIGH:
        case BODY_PART_RIGHT_THIGH:
            settings.color = Color(HUMANGL_PANTS_COLOR_R, HUMANGL_PANTS_COLOR_G, HUMANGL_PANTS_COLOR_B, 1.0f);
            break;

        // Black eyes
        case BODY_PART_EYES:
            settings.color = Color::Black();
            break;

        // Arms and legs (use skin for now, will be overridden by specific parts)
        case BODY_PART_LEFT_ARM:
        case BODY_PART_RIGHT_ARM:
        case BODY_PART_LEFT_LEG:
        case BODY_PART_RIGHT_LEG:
            settings.color = Color::SkinTone();
            break;

        default:
            settings.color = Color::SkinTone();
            break;
    }

    // Default scale and other settings
    settings.scale = Vector3(1.0f, 1.0f, 1.0f);
    settings.rotation = Vector3(0.0f, 0.0f, 0.0f);
    settings.position = Vector3(0.0f, 0.0f, 0.0f);
    settings.visible = true;

    return settings;
}

void BodyPartEditorLogic::handleCustomizationInput() {
    // Handle scale adjustment with + and - keys (including = key for +)
    bool currentPlusState = keyboardState[SDL_SCANCODE_KP_PLUS] || keyboardState[SDL_SCANCODE_EQUALS];
    bool currentMinusState = keyboardState[SDL_SCANCODE_KP_MINUS] || keyboardState[SDL_SCANCODE_MINUS];
    bool currentCState = keyboardState[SDL_SCANCODE_C];

    // Scale up with + or = key (only on key press, not hold)
    if (currentPlusState && !plusKeyPressed) {
        adjustBodyPartScale(1.1f);
        plusKeyPressed = true;
    } else if (!currentPlusState) {
        plusKeyPressed = false;
    }

    // Scale down with - key (only on key press, not hold)
    if (currentMinusState && !minusKeyPressed) {
        adjustBodyPartScale(0.9f);
        minusKeyPressed = true;
    } else if (!currentMinusState) {
        minusKeyPressed = false;
    }

    // Cycle color with C key (only on key press, not hold)
    if (currentCState && !cKeyPressed) {
        cycleBodyPartColor();
        cKeyPressed = true;
    } else if (!currentCState) {
        cKeyPressed = false;
    }
}
