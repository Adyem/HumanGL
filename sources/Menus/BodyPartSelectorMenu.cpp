#include "../../includes/Menus/BodyPartSelectorMenu.hpp"
#include "../../includes/Input/MouseHandler.hpp"

BodyPartSelectorMenu::BodyPartSelectorMenu(TextRenderer& textRenderer)
    : MenuRenderer(textRenderer) {
    initializeButtons();
}

void BodyPartSelectorMenu::initializeButtons() {
    // Always clear existing buttons first
    buttons.clear();

    // Body part selection buttons
    float buttonWidth = HUMANGL_BODYPART_BUTTON_WIDTH;
    float buttonHeight = HUMANGL_BODYPART_BUTTON_HEIGHT;
    float spacing = HUMANGL_BODYPART_BUTTON_SPACING;
    float topMargin = HUMANGL_BODYPART_TOP_MARGIN;

    // Create buttons for all customizable body parts (centered grid)
    std::vector<BodyPart> mainBodyParts = getCustomizableBodyParts();

    // Center the grid
    float horizontalSpacing = 30.0f; // More horizontal spacing between columns
    float totalGridWidth = HUMANGL_BODYPART_COLUMNS * buttonWidth + (HUMANGL_BODYPART_COLUMNS - 1) * horizontalSpacing;
    float centerX = (static_cast<float>(windowWidth) - totalGridWidth) / 2.0f;

    int row = 0, col = 0;
    for (size_t i = 0; i < mainBodyParts.size(); i++) {
        BodyPart part = mainBodyParts[i];
        float x = centerX + col * (buttonWidth + horizontalSpacing);
        float y = topMargin + row * spacing;

        // Create button using proper constructor
        buttons.emplace_back(x, y, buttonWidth, buttonHeight, getBodyPartName(part));

        col++;
        if (col >= HUMANGL_BODYPART_COLUMNS) {
            col = 0;
            row++;
        }
    }

    // Back buttons (horizontal layout, centered)
    float backButtonY = topMargin + (row + 1) * spacing + 40.0f;
    float backButtonSpacing = 30.0f; // More spacing to match grid
    float totalBackButtonWidth = 2 * buttonWidth + backButtonSpacing;
    float backButtonStartX = (static_cast<float>(windowWidth) - totalBackButtonWidth) / 2.0f;

    buttons.emplace_back(backButtonStartX, backButtonY, buttonWidth, buttonHeight, "Back to Settings");
    buttons.emplace_back(backButtonStartX + buttonWidth + backButtonSpacing, backButtonY, buttonWidth, buttonHeight, "Back to Main Menu");
}

void BodyPartSelectorMenu::render(const std::vector<MenuButton>& externalButtons) {
    setup2D();
    clearScreen();

    renderTitle();

    // Draw menu buttons
    for (const auto& button : externalButtons) {
        drawButton(button);
    }
}

void BodyPartSelectorMenu::render() {
    render(buttons);
}

const std::vector<MenuButton>& BodyPartSelectorMenu::getButtons() const {
    return buttons;
}

MenuAction BodyPartSelectorMenu::handleButtonClick(int buttonIndex, BodyPart& selectedPart) {
    // Get the main body parts list (guaranteed to match button creation)
    std::vector<BodyPart> mainBodyParts = getCustomizableBodyParts();

    if (buttonIndex < static_cast<int>(mainBodyParts.size())) {
        // Select body part
        selectedPart = mainBodyParts[buttonIndex];
        return MENU_ACTION_BODY_PART_DETAIL;
    } else {
        // Handle back buttons
        int backButtonIndex = buttonIndex - static_cast<int>(mainBodyParts.size());
        switch (backButtonIndex) {
            case 0: // Back to Settings
                return MENU_ACTION_SETTINGS;
            case 1: // Back to Main Menu
                return MENU_ACTION_BACK_TO_MENU;
            default:
                return MENU_ACTION_NONE;
        }
    }
}

std::string BodyPartSelectorMenu::getBodyPartName(BodyPart part) const {
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

std::vector<BodyPart> BodyPartSelectorMenu::getCustomizableBodyParts() const {
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

void BodyPartSelectorMenu::renderTitle() {
    float titleX = static_cast<float>(windowWidth) / 2.0f - HUMANGL_TITLE_X_OFFSET;
    float titleY = HUMANGL_TITLE_Y_POSITION;
    textRenderer.drawText(titleX, titleY, "Body Part Selector", 1.0f, 1.0f, 1.0f);
}

void BodyPartSelectorMenu::updateButtonHover(MouseHandler& mouseHandler) {
    mouseHandler.updateButtonHover(buttons);
}
