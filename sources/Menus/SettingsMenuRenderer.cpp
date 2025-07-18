#include "../../includes/Menus/SettingsMenuRenderer.hpp"
#include <algorithm>
#include <string>
#include <map>

SettingsMenuRenderer::SettingsMenuRenderer(TextRenderer& textRenderer)
    : MenuRenderer(textRenderer), currentPage(SETTINGS_MAIN), selectedBodyPart(BODY_PART_HEAD), currentColorIndex(0),
      availableColors(),
      menuBackgroundColor(Color(HUMANGL_BACKGROUND_COLOR_R, HUMANGL_BACKGROUND_COLOR_G, HUMANGL_BACKGROUND_COLOR_B, HUMANGL_BACKGROUND_COLOR_A)),
      simulationBackgroundColor(Color(HUMANGL_SIMULATION_BACKGROUND_R, HUMANGL_SIMULATION_BACKGROUND_G, HUMANGL_SIMULATION_BACKGROUND_B, HUMANGL_SIMULATION_BACKGROUND_A)),
      menuBgColorIndex(0), simulationBgColorIndex(0), sliderX(0), sliderY(0), sliderWidth(0), sliderHeight(0),
      colorSelectorX(0), colorSelectorY(0), colorSelectorSize(0), menuColorSelectorX(0), menuColorSelectorY(0), menuColorSelectorSize(0),
      simColorSelectorX(0), simColorSelectorY(0), simColorSelectorSize(0), isDraggingSlider(false) {
    initializeAvailableColors();
    initializeButtons();

    // Initialize default body part settings with proper colors
    for (int i = 0; i < BODY_PART_COUNT; i++) {
        BodyPart part = static_cast<BodyPart>(i);
        bodyPartSettings[part] = getDefaultBodyPartSettings(part);
    }
}

// Reset to main settings page (called when entering settings from main menu)
void SettingsMenuRenderer::resetToMainPage() {
    currentPage = SETTINGS_MAIN;
    isDraggingSlider = false;
    selectedBodyPart = BODY_PART_HEAD;
    currentColorIndex = 0;
    initializeButtons();
}

void SettingsMenuRenderer::initializeButtons() {
    // Always clear existing buttons first
    buttons.clear();

    if (currentPage == SETTINGS_MAIN) {
        // Main settings page buttons
        float buttonWidth = HUMANGL_MENU_BUTTON_WIDTH;
        float buttonHeight = HUMANGL_MENU_BUTTON_HEIGHT;
        float centerX = (static_cast<float>(windowWidth) - buttonWidth) / 2.0f;
        float startY = static_cast<float>(windowHeight) / 2.0f + 50.0f;
        float spacing = HUMANGL_MENU_BUTTON_SPACING;

        // Create buttons using proper MenuButton constructor
        buttons.emplace_back(centerX, startY, buttonWidth, buttonHeight, "Body Customization");
        buttons.emplace_back(centerX, startY + spacing, buttonWidth, buttonHeight, "Background Colors");
        buttons.emplace_back(centerX, startY + spacing * 2, buttonWidth, buttonHeight, "Back to Menu");

    } else if (currentPage == BODY_CUSTOMIZATION) {
        // Body part selection buttons
        float buttonWidth = HUMANGL_BODYPART_BUTTON_WIDTH;
        float buttonHeight = HUMANGL_BODYPART_BUTTON_HEIGHT;
        float spacing = HUMANGL_BODYPART_BUTTON_SPACING;
        float topMargin = HUMANGL_BODYPART_TOP_MARGIN;

        // Create buttons for all customizable body parts (centered grid)
        std::vector<BodyPart> mainBodyParts = getCustomizableBodyParts();

        // Center the grid
        float totalGridWidth = HUMANGL_BODYPART_COLUMNS * buttonWidth + (HUMANGL_BODYPART_COLUMNS - 1) * 20.0f;
        float centerX = (static_cast<float>(windowWidth) - totalGridWidth) / 2.0f;

        int row = 0, col = 0;
        for (size_t i = 0; i < mainBodyParts.size(); i++) {
            BodyPart part = mainBodyParts[i];
            float x = centerX + col * (buttonWidth + 20.0f);
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
        float buttonSpacing = 20.0f;
        float totalBackButtonWidth = 2 * buttonWidth + buttonSpacing;
        float backButtonStartX = (static_cast<float>(windowWidth) - totalBackButtonWidth) / 2.0f;

        buttons.emplace_back(backButtonStartX, backButtonY, buttonWidth, buttonHeight, "Back to Settings");
        buttons.emplace_back(backButtonStartX + buttonWidth + buttonSpacing, backButtonY, buttonWidth, buttonHeight, "Back to Main Menu");

    } else if (currentPage == BODY_PART_DETAIL) {
        // Body part detail page buttons (horizontal layout)
        float buttonWidth = 140.0f; // Smaller to fit 4 buttons
        float buttonHeight = HUMANGL_MENU_BUTTON_HEIGHT;
        float startY = static_cast<float>(windowHeight) - 100.0f;
        float buttonSpacing = 15.0f;

        // Calculate total width and center position for 4 buttons
        float totalWidth = 4 * buttonWidth + 3 * buttonSpacing;
        float startX = (static_cast<float>(windowWidth) - totalWidth) / 2.0f;

        buttons.emplace_back(startX, startY, buttonWidth, buttonHeight, "Reset to Default");
        buttons.emplace_back(startX + buttonWidth + buttonSpacing, startY, buttonWidth, buttonHeight, "Back to Body Parts");
        buttons.emplace_back(startX + 2 * (buttonWidth + buttonSpacing), startY, buttonWidth, buttonHeight, "Back to Settings");
        buttons.emplace_back(startX + 3 * (buttonWidth + buttonSpacing), startY, buttonWidth, buttonHeight, "Back to Main Menu");

    } else if (currentPage == BACKGROUND_CUSTOMIZATION) {
        // Background customization page buttons (horizontal layout)
        float buttonWidth = 150.0f; // Smaller to fit 3 buttons
        float buttonHeight = HUMANGL_MENU_BUTTON_HEIGHT;
        float startY = static_cast<float>(windowHeight) - 100.0f;
        float buttonSpacing = 15.0f;

        // Calculate total width and center position for 3 buttons
        float totalWidth = 3 * buttonWidth + 2 * buttonSpacing;
        float startX = (static_cast<float>(windowWidth) - totalWidth) / 2.0f;

        buttons.emplace_back(startX, startY, buttonWidth, buttonHeight, "Reset to Default");
        buttons.emplace_back(startX + buttonWidth + buttonSpacing, startY, buttonWidth, buttonHeight, "Back to Settings");
        buttons.emplace_back(startX + 2 * (buttonWidth + buttonSpacing), startY, buttonWidth, buttonHeight, "Back to Main Menu");
    }
}

void SettingsMenuRenderer::render(const std::vector<MenuButton>& externalButtons) {
    setup2D();
    clearScreen();

    renderTitle();
    renderSettingsContent();

    // Draw menu buttons
    for (const auto& button : externalButtons) {
        drawButton(button);
    }
}

void SettingsMenuRenderer::render() {
    setup2D();
    clearScreen();

    renderTitle();

    // Render content based on current page
    switch (currentPage) {
        case SETTINGS_MAIN:
            renderSettingsContent();
            break;
        case BODY_CUSTOMIZATION:
            renderBodyPartSelection();
            break;
        case BODY_PART_DETAIL:
            renderBodyPartCustomization();
            break;
        case BACKGROUND_CUSTOMIZATION:
            renderBackgroundCustomization();
            break;
        default:
            renderSettingsContent();
            break;
    }

    // Draw our own buttons with forced hover check
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    // Create a copy to modify hover states
    std::vector<MenuButton> renderButtons = buttons;
    for (auto& button : renderButtons) {
        // Update hover state directly before drawing
        button.hovered = button.isPointInside(static_cast<float>(mouseX), static_cast<float>(mouseY));
        drawButton(button);
    }
}

const std::vector<MenuButton>& SettingsMenuRenderer::getButtons() const {
    return buttons;
}

MenuAction SettingsMenuRenderer::handleButtonClick(int buttonIndex) {
    if (currentPage == SETTINGS_MAIN) {
        switch (buttonIndex) {
            case 0: // Body Customization
                setPage(BODY_CUSTOMIZATION);
                return MENU_ACTION_NONE;
            case 1: // Background Colors
                setPage(BACKGROUND_CUSTOMIZATION);
                return MENU_ACTION_NONE;
            case 2: // Back to Menu
                return MENU_ACTION_BACK_TO_MENU;
            default:
                return MENU_ACTION_NONE;
        }
    } else if (currentPage == BODY_CUSTOMIZATION) {
        // Get the main body parts list (guaranteed to match button creation)
        std::vector<BodyPart> mainBodyParts = getCustomizableBodyParts();

        if (buttonIndex < static_cast<int>(mainBodyParts.size())) {
            // Select body part
            selectedBodyPart = mainBodyParts[buttonIndex];
            setPage(BODY_PART_DETAIL);
            return MENU_ACTION_NONE;
        } else if (buttonIndex == static_cast<int>(mainBodyParts.size())) {
            // Back to settings
            setPage(SETTINGS_MAIN);
            return MENU_ACTION_NONE;
        } else {
            // Back to main menu - reset to main settings page first
            currentPage = SETTINGS_MAIN;
            return MENU_ACTION_BACK_TO_MENU;
        }
    } else if (currentPage == BODY_PART_DETAIL) {
        switch (buttonIndex) {
            case 0: // Reset to Default
                resetBodyPartToDefault();
                return MENU_ACTION_NONE;
            case 1: // Back to Body Parts
                setPage(BODY_CUSTOMIZATION);
                return MENU_ACTION_NONE;
            case 2: // Back to Settings
                setPage(SETTINGS_MAIN);
                return MENU_ACTION_NONE;
            case 3: // Back to Main Menu
                currentPage = SETTINGS_MAIN;
                return MENU_ACTION_BACK_TO_MENU;
            default:
                return MENU_ACTION_NONE;
        }
    } else if (currentPage == BACKGROUND_CUSTOMIZATION) {
        switch (buttonIndex) {
            case 0: // Reset to Default
                resetColorsToDefault();
                return MENU_ACTION_NONE;
            case 1: // Back to Settings
                setPage(SETTINGS_MAIN);
                return MENU_ACTION_NONE;
            case 2: // Back to Main Menu
                currentPage = SETTINGS_MAIN;
                return MENU_ACTION_BACK_TO_MENU;
            default:
                return MENU_ACTION_NONE;
        }
    }

    return MENU_ACTION_NONE;
}

void SettingsMenuRenderer::renderTitle() {
    // Draw title based on current page
    float titleX = static_cast<float>(windowWidth) / 2.0f - HUMANGL_TITLE_X_OFFSET;
    float titleY = HUMANGL_TITLE_Y_POSITION;

    std::string title;
    switch (currentPage) {
        case SETTINGS_MAIN:
            title = "Settings";
            break;
        case BODY_CUSTOMIZATION:
            title = "Body Customization";
            break;
        case BODY_PART_DETAIL:
            title = "Customize " + getBodyPartName(selectedBodyPart);
            break;
        case BACKGROUND_CUSTOMIZATION:
            title = "Background Colors";
            break;
        default:
            title = "Settings";
            break;
    }

    textRenderer.drawText(titleX, titleY, title, 1.0f, 1.0f, 1.0f);
}

void SettingsMenuRenderer::renderSettingsContent() {
    // Draw settings content
    float contentY = HUMANGL_SETTINGS_CONTENT_START_Y;
    float lineSpacing = HUMANGL_SETTINGS_LINE_SPACING;

    textRenderer.drawText(HUMANGL_SETTINGS_LEFT_MARGIN, contentY, "Graphics Settings:", 0.9f, 0.9f, 0.9f);
    contentY += lineSpacing;
    textRenderer.drawText(HUMANGL_SETTINGS_LEFT_MARGIN + HUMANGL_SETTINGS_INDENT, contentY, "- Resolution: 1280x720 (720p)", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing;
    textRenderer.drawText(HUMANGL_SETTINGS_LEFT_MARGIN + HUMANGL_SETTINGS_INDENT, contentY, "- VSync: Enabled", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing;
    textRenderer.drawText(HUMANGL_SETTINGS_LEFT_MARGIN + HUMANGL_SETTINGS_INDENT, contentY, "- Anti-aliasing: Off", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing * 1.5f;

    textRenderer.drawText(HUMANGL_SETTINGS_LEFT_MARGIN, contentY, "Controls:", 0.9f, 0.9f, 0.9f);
    contentY += lineSpacing;
    textRenderer.drawText(HUMANGL_SETTINGS_LEFT_MARGIN + HUMANGL_SETTINGS_INDENT, contentY, "- Mouse sensitivity: Normal", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing;
    textRenderer.drawText(HUMANGL_SETTINGS_LEFT_MARGIN + HUMANGL_SETTINGS_INDENT, contentY, "- Keyboard layout: QWERTY", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing * 1.5f;

    textRenderer.drawText(HUMANGL_SETTINGS_LEFT_MARGIN, contentY, "Customization:", 0.9f, 0.9f, 0.9f);
    contentY += lineSpacing;
    textRenderer.drawText(HUMANGL_SETTINGS_LEFT_MARGIN + HUMANGL_SETTINGS_INDENT, contentY, "- Use 'Body Customization' to modify body parts", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing;
    textRenderer.drawText(HUMANGL_SETTINGS_LEFT_MARGIN + HUMANGL_SETTINGS_INDENT, contentY, "- Use 'Background Colors' to change menu/simulation colors", 0.8f, 0.8f, 0.8f);
}

// Page navigation methods
void SettingsMenuRenderer::setPage(SettingsPage page) {
    currentPage = page;
    initializeButtons();

    // Reset any interaction states when changing pages
    isDraggingSlider = false;
}

void SettingsMenuRenderer::setSelectedBodyPart(BodyPart part) {
    selectedBodyPart = part;
}

SettingsPage SettingsMenuRenderer::getCurrentPage() const {
    return currentPage;
}

// Body part customization methods
void SettingsMenuRenderer::cycleBodyPartColor() {
    currentColorIndex = (currentColorIndex + 1) % availableColors.size();
    bodyPartSettings[selectedBodyPart].color = availableColors[currentColorIndex];
}

void SettingsMenuRenderer::adjustBodyPartScale(float scaleMultiplier) {
    BodyPartSettings& settings = bodyPartSettings[selectedBodyPart];
    settings.scale.x = std::max(HUMANGL_SLIDER_MIN_VALUE, std::min(HUMANGL_SLIDER_MAX_VALUE, settings.scale.x * scaleMultiplier));
    settings.scale.y = std::max(HUMANGL_SLIDER_MIN_VALUE, std::min(HUMANGL_SLIDER_MAX_VALUE, settings.scale.y * scaleMultiplier));
    settings.scale.z = std::max(HUMANGL_SLIDER_MIN_VALUE, std::min(HUMANGL_SLIDER_MAX_VALUE, settings.scale.z * scaleMultiplier));
}

void SettingsMenuRenderer::setBodyPartScale(float newScale) {
    BodyPartSettings& settings = bodyPartSettings[selectedBodyPart];
    float clampedScale = std::max(HUMANGL_SLIDER_MIN_VALUE, std::min(HUMANGL_SLIDER_MAX_VALUE, newScale));
    settings.scale.x = clampedScale;
    settings.scale.y = clampedScale;
    settings.scale.z = clampedScale;
}

const BodyPartSettings& SettingsMenuRenderer::getBodyPartSettings(BodyPart part) const {
    return bodyPartSettings.at(part);
}

const std::map<BodyPart, BodyPartSettings>& SettingsMenuRenderer::getAllBodyPartSettings() const {
    return bodyPartSettings;
}

// Initialize available colors
void SettingsMenuRenderer::initializeAvailableColors() {
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

// Handle mouse click in the settings menu
bool SettingsMenuRenderer::handleMouseClick(float mouseX, float mouseY) {
    if (currentPage == BODY_PART_DETAIL) {
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
    } else if (currentPage == BACKGROUND_CUSTOMIZATION) {
        // Check if clicked on menu background color selector
        if (mouseX >= menuColorSelectorX && mouseX <= menuColorSelectorX + menuColorSelectorSize &&
            mouseY >= menuColorSelectorY && mouseY <= menuColorSelectorY + menuColorSelectorSize) {
            cycleMenuBackgroundColor();
            return true;
        }

        // Check if clicked on simulation background color selector
        if (mouseX >= simColorSelectorX && mouseX <= simColorSelectorX + simColorSelectorSize &&
            mouseY >= simColorSelectorY && mouseY <= simColorSelectorY + simColorSelectorSize) {
            cycleSimulationBackgroundColor();
            return true;
        }
    }

    return false;
}

// Update hover state based on mouse position
void SettingsMenuRenderer::updateHover(float mouseX, float mouseY) {
    // Check for stop dragging signal
    if (mouseX < 0 || mouseY < 0) {
        isDraggingSlider = false;
        return;
    }

    if (currentPage == BODY_PART_DETAIL) {
        // Update slider dragging if mouse button is held down
        if (isDraggingSlider && sliderWidth > 0) {
            float normalizedPos = std::max(0.0f, std::min(1.0f, (mouseX - sliderX) / sliderWidth));
            float newScale = HUMANGL_SLIDER_MIN_VALUE + normalizedPos * (HUMANGL_SLIDER_MAX_VALUE - HUMANGL_SLIDER_MIN_VALUE);
            setBodyPartScale(newScale);
        }
    }
}

// Render body part selection page
void SettingsMenuRenderer::renderBodyPartSelection() {
}

// Render body part customization page
void SettingsMenuRenderer::renderBodyPartCustomization() {
    float contentY = HUMANGL_SETTINGS_CONTENT_START_Y;
    float lineSpacing = HUMANGL_SETTINGS_LINE_SPACING;

    std::string title = "Customizing: " + getBodyPartName(selectedBodyPart);
    textRenderer.drawText(HUMANGL_SETTINGS_LEFT_MARGIN, contentY, title, 0.9f, 0.9f, 0.9f);
    contentY += lineSpacing * 2.0f;

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

// Draw a slider UI element
void SettingsMenuRenderer::drawSlider(float x, float y, float value, const std::string& label) {
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

// Draw color selector
void SettingsMenuRenderer::drawColorSelector(float x, float y) {
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

    // Draw color name with hover effect
    std::string colorText = isHovering ? "Click to change color!" : "Click to change color";
    float textR = isHovering ? 1.0f : 0.8f;
    float textG = isHovering ? 1.0f : 0.8f;
    float textB = isHovering ? 1.0f : 0.8f;
    textRenderer.drawText(x + HUMANGL_COLOR_PREVIEW_SIZE + 10.0f, y + 8.0f, colorText, textR, textG, textB);
}

// Get body part name as string
std::string SettingsMenuRenderer::getBodyPartName(BodyPart part) const {
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

BodyPartSettings SettingsMenuRenderer::getDefaultBodyPartSettings(BodyPart part) const {
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

std::vector<BodyPart> SettingsMenuRenderer::getCustomizableBodyParts() const {
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

// Background color customization methods
void SettingsMenuRenderer::cycleMenuBackgroundColor() {
    menuBgColorIndex = (menuBgColorIndex + 1) % availableColors.size();
    menuBackgroundColor = availableColors[menuBgColorIndex];
}

void SettingsMenuRenderer::cycleSimulationBackgroundColor() {
    simulationBgColorIndex = (simulationBgColorIndex + 1) % availableColors.size();
    simulationBackgroundColor = availableColors[simulationBgColorIndex];
}

void SettingsMenuRenderer::resetColorsToDefault() {
    // Reset to default colors
    menuBackgroundColor = Color(HUMANGL_BACKGROUND_COLOR_R, HUMANGL_BACKGROUND_COLOR_G, HUMANGL_BACKGROUND_COLOR_B, HUMANGL_BACKGROUND_COLOR_A);
    simulationBackgroundColor = Color(HUMANGL_SIMULATION_BACKGROUND_R, HUMANGL_SIMULATION_BACKGROUND_G, HUMANGL_SIMULATION_BACKGROUND_B, HUMANGL_SIMULATION_BACKGROUND_A);

    // Reset color indices
    menuBgColorIndex = 0;
    simulationBgColorIndex = 0;
}

void SettingsMenuRenderer::resetBodyPartToDefault() {
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

const Color& SettingsMenuRenderer::getMenuBackgroundColor() const {
    return menuBackgroundColor;
}

const Color& SettingsMenuRenderer::getSimulationBackgroundColor() const {
    return simulationBackgroundColor;
}

// Render background customization page
void SettingsMenuRenderer::renderBackgroundCustomization() {
    float contentY = HUMANGL_SETTINGS_CONTENT_START_Y;
    float lineSpacing = HUMANGL_SETTINGS_LINE_SPACING;

    textRenderer.drawText(HUMANGL_SETTINGS_LEFT_MARGIN, contentY, "Customize Background Colors:", 0.9f, 0.9f, 0.9f);
    contentY += lineSpacing * 2.0f;

    // Menu background color section
    textRenderer.drawText(HUMANGL_SETTINGS_LEFT_MARGIN, contentY, "Menu Background Color:", 0.9f, 0.9f, 0.9f);
    contentY += lineSpacing;

    float colorX = HUMANGL_SETTINGS_LEFT_MARGIN + 50.0f;
    drawBackgroundColorSelector(colorX, contentY, menuBackgroundColor, true);
    contentY += lineSpacing * 2.5f;

    // Simulation background color section
    textRenderer.drawText(HUMANGL_SETTINGS_LEFT_MARGIN, contentY, "Simulation Background Color:", 0.9f, 0.9f, 0.9f);
    contentY += lineSpacing;

    drawBackgroundColorSelector(colorX, contentY, simulationBackgroundColor, false);
    contentY += lineSpacing * 2.0f;

    // Instructions
    textRenderer.drawText(HUMANGL_SETTINGS_LEFT_MARGIN, contentY, "Instructions:", 0.9f, 0.9f, 0.9f);
    contentY += lineSpacing;
    textRenderer.drawText(HUMANGL_SETTINGS_LEFT_MARGIN + HUMANGL_SETTINGS_INDENT, contentY, "- Click color boxes to change colors", 0.8f, 0.8f, 0.8f);
    contentY += lineSpacing;
    textRenderer.drawText(HUMANGL_SETTINGS_LEFT_MARGIN + HUMANGL_SETTINGS_INDENT, contentY, "- Use M key for menu colors, S key for simulation colors", 0.8f, 0.8f, 0.8f);
}

// Draw background color selector
void SettingsMenuRenderer::drawBackgroundColorSelector(float x, float y, const Color& currentColor, bool isMenuColor) {
    float previewSize = HUMANGL_COLOR_PREVIEW_SIZE;

    // Check if mouse is hovering
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    bool isHovering = (static_cast<float>(mouseX) >= x && static_cast<float>(mouseX) <= x + previewSize &&
                      static_cast<float>(mouseY) >= y && static_cast<float>(mouseY) <= y + previewSize);

    // Store position for mouse interaction
    if (isMenuColor) {
        menuColorSelectorX = x;
        menuColorSelectorY = y;
        menuColorSelectorSize = previewSize;
    } else {
        simColorSelectorX = x;
        simColorSelectorY = y;
        simColorSelectorSize = previewSize;
    }

    // Draw color preview
    drawRect(x, y, previewSize, previewSize, currentColor.r, currentColor.g, currentColor.b, 1.0f);

    // Draw border with hover effect
    float borderR = isHovering ? 1.0f : 0.8f;
    float borderG = isHovering ? 1.0f : 0.8f;
    float borderB = isHovering ? 1.0f : 0.8f;
    float borderWidth = isHovering ? 2.0f : 1.0f;

    glLineWidth(borderWidth);
    glColor3f(borderR, borderG, borderB);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + previewSize, y);
    glVertex2f(x + previewSize, y + previewSize);
    glVertex2f(x, y + previewSize);
    glEnd();
    glLineWidth(1.0f);

    // Draw label
    std::string label = isMenuColor ? "Menu Background" : "Simulation Background";
    std::string clickText = isHovering ? " (Click to change!)" : " (Click to change)";
    float textR = isHovering ? 1.0f : 0.8f;
    float textG = isHovering ? 1.0f : 0.8f;
    float textB = isHovering ? 1.0f : 0.8f;
    textRenderer.drawText(x + previewSize + 10.0f, y + 8.0f, label + clickText, textR, textG, textB);
}
