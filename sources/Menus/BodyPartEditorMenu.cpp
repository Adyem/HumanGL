#include "../../includes/Menus/BodyPartEditorMenu.hpp"
#include "../../includes/Input/MouseHandler.hpp"
#include <algorithm>
#include <string>

BodyPartEditorMenu::BodyPartEditorMenu(TextRenderer& textRenderer)
    : MenuRenderer(textRenderer), selectedBodyPart(BODY_PART_HEAD), currentColorIndex(0),
      sliderX(0), sliderY(0), sliderWidth(0), sliderHeight(0),
      colorSelectorX(0), colorSelectorY(0), colorSelectorSize(0), isDraggingSlider(false),
      keyboardState(SDL_GetKeyboardState(nullptr)), plusKeyPressed(false), minusKeyPressed(false), cKeyPressed(false) {
    initializeAvailableColors();
    initializeButtons();

    // Initialize default body part settings
    for (int i = 0; i < BODY_PART_COUNT; i++) {
        BodyPart part = static_cast<BodyPart>(i);
        bodyPartSettings[part] = getDefaultBodyPartSettings(part);
    }
}

void BodyPartEditorMenu::setSelectedBodyPart(BodyPart part) {
    selectedBodyPart = part;
    initializeButtons(); // Refresh buttons for new body part
}

void BodyPartEditorMenu::setBodyPartSettings(const std::map<BodyPart, BodyPartSettings>& settings) {
    bodyPartSettings = settings;
}

void BodyPartEditorMenu::initializeButtons() {
    // Always clear existing buttons first
    buttons.clear();

    // Body part detail page buttons (horizontal layout)
    float buttonWidth = 190.0f; // Even bigger to fit longer text
    float buttonHeight = HUMANGL_MENU_BUTTON_HEIGHT;
    float startY = static_cast<float>(windowHeight) - 100.0f;
    float buttonSpacing = 25.0f; // More spacing between buttons

    // Calculate total width and center position for 4 buttons
    float totalWidth = 4 * buttonWidth + 3 * buttonSpacing;
    float startX = (static_cast<float>(windowWidth) - totalWidth) / 2.0f;

    buttons.emplace_back(startX, startY, buttonWidth, buttonHeight, "Reset to Default");
    buttons.emplace_back(startX + buttonWidth + buttonSpacing, startY, buttonWidth, buttonHeight, "Back to Body Parts");
    buttons.emplace_back(startX + 2 * (buttonWidth + buttonSpacing), startY, buttonWidth, buttonHeight, "Back to Settings");
    buttons.emplace_back(startX + 3 * (buttonWidth + buttonSpacing), startY, buttonWidth, buttonHeight, "Back to Main Menu");
}

void BodyPartEditorMenu::render(const std::vector<MenuButton>& externalButtons) {
    setup2D();
    clearScreen();

    renderTitle();
    renderBodyPartCustomization();

    // Draw menu buttons
    for (const auto& button : externalButtons) {
        drawButton(button);
    }
}

void BodyPartEditorMenu::render() {
    render(buttons);
}

const std::vector<MenuButton>& BodyPartEditorMenu::getButtons() const {
    return buttons;
}

MenuAction BodyPartEditorMenu::handleButtonClick(int buttonIndex) {
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

bool BodyPartEditorMenu::handleMouseClick(float mouseX, float mouseY) {
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

void BodyPartEditorMenu::updateHover(float mouseX, float mouseY) {
    // Handle mouse up signal (negative coordinates)
    if (mouseX < 0 || mouseY < 0) {
        isDraggingSlider = false;
        return;
    }

    // Update slider dragging if mouse button is held down
    if (isDraggingSlider && sliderWidth > 0) {
        float normalizedPos = std::max(0.0f, std::min(1.0f, (mouseX - sliderX) / sliderWidth));
        float newScale = HUMANGL_SLIDER_MIN_VALUE + normalizedPos * (HUMANGL_SLIDER_MAX_VALUE - HUMANGL_SLIDER_MIN_VALUE);
        setBodyPartScale(newScale);
    }
}

void BodyPartEditorMenu::handleMouseUp() {
    isDraggingSlider = false;
}

void BodyPartEditorMenu::handleInput() {
    if (!keyboardState) return;
    
    handleCustomizationInput();
}

void BodyPartEditorMenu::cycleBodyPartColor() {
    currentColorIndex = (currentColorIndex + 1) % availableColors.size();
    bodyPartSettings[selectedBodyPart].color = availableColors[currentColorIndex];
}

void BodyPartEditorMenu::adjustBodyPartScale(float scaleMultiplier) {
    BodyPartSettings& settings = bodyPartSettings[selectedBodyPart];
    settings.scale.x = std::max(HUMANGL_SLIDER_MIN_VALUE, std::min(HUMANGL_SLIDER_MAX_VALUE, settings.scale.x * scaleMultiplier));
    settings.scale.y = std::max(HUMANGL_SLIDER_MIN_VALUE, std::min(HUMANGL_SLIDER_MAX_VALUE, settings.scale.y * scaleMultiplier));
    settings.scale.z = std::max(HUMANGL_SLIDER_MIN_VALUE, std::min(HUMANGL_SLIDER_MAX_VALUE, settings.scale.z * scaleMultiplier));
}

void BodyPartEditorMenu::setBodyPartScale(float newScale) {
    BodyPartSettings& settings = bodyPartSettings[selectedBodyPart];
    float clampedScale = std::max(HUMANGL_SLIDER_MIN_VALUE, std::min(HUMANGL_SLIDER_MAX_VALUE, newScale));
    settings.scale.x = clampedScale;
    settings.scale.y = clampedScale;
    settings.scale.z = clampedScale;
}

void BodyPartEditorMenu::resetBodyPartToDefault() {
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

const BodyPartSettings& BodyPartEditorMenu::getBodyPartSettings(BodyPart part) const {
    auto it = bodyPartSettings.find(part);
    if (it != bodyPartSettings.end()) {
        return it->second;
    }
    // Return default if not found
    static BodyPartSettings defaultSettings = getDefaultBodyPartSettings(part);
    return defaultSettings;
}

const std::map<BodyPart, BodyPartSettings>& BodyPartEditorMenu::getAllBodyPartSettings() const {
    return bodyPartSettings;
}

void BodyPartEditorMenu::initializeAvailableColors() {
    availableColors.clear();

    // Add a variety of colors for customization
    availableColors.push_back(Color::SkinTone());
    availableColors.push_back(Color::Blue());
    availableColors.push_back(Color::Red());
    availableColors.push_back(Color::Green());
    availableColors.push_back(Color::Yellow());
    availableColors.push_back(Color::Magenta());
    availableColors.push_back(Color::Cyan());
    availableColors.push_back(Color::ClothingBlue());
    availableColors.push_back(Color::White());
    availableColors.push_back(Color::Black());
}

void BodyPartEditorMenu::renderTitle() {
    std::string title = "Customize " + getBodyPartName(selectedBodyPart);
    float titleX = static_cast<float>(windowWidth) / 2.0f - HUMANGL_TITLE_X_OFFSET;
    float titleY = HUMANGL_TITLE_Y_POSITION;
    textRenderer.drawText(titleX, titleY, title, 1.0f, 1.0f, 1.0f);
}

void BodyPartEditorMenu::renderBodyPartCustomization() {
    float contentY = HUMANGL_SETTINGS_CONTENT_START_Y;
    float lineSpacing = HUMANGL_SETTINGS_LINE_SPACING;

    // Scale controls
    textRenderer.drawText(HUMANGL_SETTINGS_LEFT_MARGIN, contentY, "Size:", 0.9f, 0.9f, 0.9f);
    contentY += lineSpacing;

    const BodyPartSettings& settings = bodyPartSettings[selectedBodyPart];
    drawSlider(HUMANGL_SETTINGS_LEFT_MARGIN + 50.0f, contentY, settings.scale.x, "Scale");
    contentY += lineSpacing * 2.0f;

    // Color controls
    textRenderer.drawText(HUMANGL_SETTINGS_LEFT_MARGIN, contentY, "Color:", 0.9f, 0.9f, 0.9f);
    contentY += lineSpacing;
    drawColorSelector(HUMANGL_SETTINGS_LEFT_MARGIN + 50.0f, contentY);
    contentY += lineSpacing * 2.0f;

    // Instructions
    textRenderer.drawText(HUMANGL_SETTINGS_LEFT_MARGIN, contentY, "Instructions:", 0.9f, 0.9f, 0.9f);
    contentY += lineSpacing;
    textRenderer.drawText(HUMANGL_SETTINGS_LEFT_MARGIN + HUMANGL_SETTINGS_INDENT, contentY, "- Use +/- keys to adjust size", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing;
    textRenderer.drawText(HUMANGL_SETTINGS_LEFT_MARGIN + HUMANGL_SETTINGS_INDENT, contentY, "- Use C key to cycle through colors", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing;
    textRenderer.drawText(HUMANGL_SETTINGS_LEFT_MARGIN + HUMANGL_SETTINGS_INDENT, contentY, "- Use the mouse to change size and color", 0.8f, 0.8f, 0.8f);
}

void BodyPartEditorMenu::drawSlider(float x, float y, float value, const std::string& label) {
    // Store slider position for mouse interaction
    sliderX = x;
    sliderY = y;
    sliderWidth = HUMANGL_SLIDER_WIDTH;
    sliderHeight = HUMANGL_SLIDER_HEIGHT;

    // Check if mouse is hovering over slider
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    bool isHovering = (static_cast<float>(mouseX) >= x && static_cast<float>(mouseX) <= x + HUMANGL_SLIDER_WIDTH &&
                      static_cast<float>(mouseY) >= y && static_cast<float>(mouseY) <= y + HUMANGL_SLIDER_HEIGHT);

    // Draw slider track with hover effect
    float trackR = isHovering ? 0.4f : 0.3f;
    float trackG = isHovering ? 0.4f : 0.3f;
    float trackB = isHovering ? 0.4f : 0.3f;
    drawRect(x, y, HUMANGL_SLIDER_WIDTH, HUMANGL_SLIDER_HEIGHT, trackR, trackG, trackB, 0.8f);

    // Calculate handle position
    float normalizedValue = (value - HUMANGL_SLIDER_MIN_VALUE) / (HUMANGL_SLIDER_MAX_VALUE - HUMANGL_SLIDER_MIN_VALUE);
    float handleX = x + normalizedValue * (HUMANGL_SLIDER_WIDTH - HUMANGL_SLIDER_HANDLE_WIDTH);

    // Draw slider handle with hover and drag effects
    float handleR = isDraggingSlider ? 1.0f : (isHovering ? 0.9f : 0.7f);
    float handleG = isDraggingSlider ? 1.0f : (isHovering ? 0.9f : 0.7f);
    float handleB = isDraggingSlider ? 1.0f : (isHovering ? 0.9f : 0.7f);
    drawRect(handleX, y - 2.0f, HUMANGL_SLIDER_HANDLE_WIDTH, HUMANGL_SLIDER_HEIGHT + 4.0f, handleR, handleG, handleB, 1.0f);

    // Draw value text
    std::string valueText = label + ": " + std::to_string(value).substr(0, 4);
    textRenderer.drawText(x + HUMANGL_SLIDER_WIDTH + 10.0f, y + 5.0f, valueText, 0.8f, 0.8f, 0.8f);
}

void BodyPartEditorMenu::drawColorSelector(float x, float y) {
    // Store color selector position for mouse interaction
    colorSelectorX = x;
    colorSelectorY = y;
    colorSelectorSize = HUMANGL_COLOR_PREVIEW_SIZE;

    // Check if mouse is hovering over color selector
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    bool isHovering = (static_cast<float>(mouseX) >= x && static_cast<float>(mouseX) <= x + HUMANGL_COLOR_PREVIEW_SIZE &&
                      static_cast<float>(mouseY) >= y && static_cast<float>(mouseY) <= y + HUMANGL_COLOR_PREVIEW_SIZE);

    const Color& currentColor = bodyPartSettings[selectedBodyPart].color;

    // Draw current color preview
    drawRect(x, y, HUMANGL_COLOR_PREVIEW_SIZE, HUMANGL_COLOR_PREVIEW_SIZE, currentColor.r, currentColor.g, currentColor.b, 1.0f);

    // Draw border around preview with hover effect
    float borderR = isHovering ? 1.0f : 0.8f;
    float borderG = isHovering ? 1.0f : 0.8f;
    float borderB = isHovering ? 1.0f : 0.8f;

    // Draw thicker border when hovering
    float borderWidth = isHovering ? 2.0f : 1.0f;
    glLineWidth(borderWidth);
    glColor3f(borderR, borderG, borderB);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + HUMANGL_COLOR_PREVIEW_SIZE, y);
    glVertex2f(x + HUMANGL_COLOR_PREVIEW_SIZE, y + HUMANGL_COLOR_PREVIEW_SIZE);
    glVertex2f(x, y + HUMANGL_COLOR_PREVIEW_SIZE);
    glEnd();
    glLineWidth(1.0f); // Reset line width
}

std::string BodyPartEditorMenu::getBodyPartName(BodyPart part) const {
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

BodyPartSettings BodyPartEditorMenu::getDefaultBodyPartSettings(BodyPart part) const {
    BodyPartSettings settings;

    // Set default scale
    settings.scale = Vector3(1.0f, 1.0f, 1.0f);

    // Set default colors based on body part type
    switch (part) {
        case BODY_PART_EYES:
            settings.color = Color::Black(); // Eyes are black by default
            break;
        case BODY_PART_HEAD:
        case BODY_PART_NECK:
        case BODY_PART_LEFT_FOREARM:
        case BODY_PART_RIGHT_FOREARM:
        case BODY_PART_LEFT_LOWER_LEG:
        case BODY_PART_RIGHT_LOWER_LEG:
            settings.color = Color::SkinTone(); // Exposed skin parts
            break;
        default:
            settings.color = Color::Blue(); // Clothing parts (torso, arms, legs)
            break;
    }

    // Set visibility
    settings.visible = true;

    return settings;
}

void BodyPartEditorMenu::handleCustomizationInput() {
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

void BodyPartEditorMenu::updateButtonHover(MouseHandler& mouseHandler) {
    mouseHandler.updateButtonHover(buttons);
}
