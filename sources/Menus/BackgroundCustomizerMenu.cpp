#include "../../includes/Menus/BackgroundCustomizerMenu.hpp"
#include "../../includes/Input/MouseHandler.hpp"

BackgroundCustomizerMenu::BackgroundCustomizerMenu(TextRenderer& textRenderer)
    : MenuRenderer(textRenderer),
      menuBackgroundColor(Color(HUMANGL_BACKGROUND_COLOR_R, HUMANGL_BACKGROUND_COLOR_G, HUMANGL_BACKGROUND_COLOR_B, HUMANGL_BACKGROUND_COLOR_A)),
      simulationBackgroundColor(Color(HUMANGL_SIMULATION_BACKGROUND_R, HUMANGL_SIMULATION_BACKGROUND_G, HUMANGL_SIMULATION_BACKGROUND_B, HUMANGL_SIMULATION_BACKGROUND_A)),
      menuBgColorIndex(0), simulationBgColorIndex(0),
      menuColorSelectorX(0), menuColorSelectorY(0), menuColorSelectorSize(0),
      simColorSelectorX(0), simColorSelectorY(0), simColorSelectorSize(0),
      keyboardState(SDL_GetKeyboardState(nullptr)), plusKeyPressed(false), minusKeyPressed(false) {
    initializeAvailableColors();
    initializeButtons();
}

void BackgroundCustomizerMenu::initializeButtons() {
    // Always clear existing buttons first
    buttons.clear();

    // Background customization page buttons (horizontal layout)
    float buttonWidth = 180.0f; // Bigger to fit text better
    float buttonHeight = HUMANGL_MENU_BUTTON_HEIGHT;
    float startY = static_cast<float>(windowHeight) - 100.0f;
    float buttonSpacing = 25.0f; // More spacing between buttons

    // Calculate total width and center position for 3 buttons
    float totalWidth = 3 * buttonWidth + 2 * buttonSpacing;
    float startX = (static_cast<float>(windowWidth) - totalWidth) / 2.0f;

    buttons.emplace_back(startX, startY, buttonWidth, buttonHeight, "Reset to Default");
    buttons.emplace_back(startX + buttonWidth + buttonSpacing, startY, buttonWidth, buttonHeight, "Back to Settings");
    buttons.emplace_back(startX + 2 * (buttonWidth + buttonSpacing), startY, buttonWidth, buttonHeight, "Back to Main Menu");
}

void BackgroundCustomizerMenu::render(const std::vector<MenuButton>& externalButtons) {
    setup2D();
    clearScreen();

    renderTitle();
    renderBackgroundCustomization();

    // Draw menu buttons
    for (const auto& button : externalButtons) {
        drawButton(button);
    }
}

void BackgroundCustomizerMenu::render() {
    render(buttons);
}

const std::vector<MenuButton>& BackgroundCustomizerMenu::getButtons() const {
    return buttons;
}

MenuAction BackgroundCustomizerMenu::handleButtonClick(int buttonIndex) {
    switch (buttonIndex) {
        case 0: // Reset to Default
            resetColorsToDefault();
            return MENU_ACTION_NONE;
        case 1: // Back to Settings
            return MENU_ACTION_SETTINGS;
        case 2: // Back to Main Menu
            return MENU_ACTION_BACK_TO_MENU;
        default:
            return MENU_ACTION_NONE;
    }
}

bool BackgroundCustomizerMenu::handleMouseClick(float mouseX, float mouseY) {
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

    return false;
}

void BackgroundCustomizerMenu::handleInput() {
    if (!keyboardState) return;
    
    handleBackgroundCustomizationInput();
}

void BackgroundCustomizerMenu::cycleMenuBackgroundColor() {
    menuBgColorIndex = (menuBgColorIndex + 1) % availableColors.size();
    menuBackgroundColor = availableColors[menuBgColorIndex];
}

void BackgroundCustomizerMenu::cycleSimulationBackgroundColor() {
    simulationBgColorIndex = (simulationBgColorIndex + 1) % availableColors.size();
    simulationBackgroundColor = availableColors[simulationBgColorIndex];
}

void BackgroundCustomizerMenu::resetColorsToDefault() {
    // Reset to default colors
    menuBackgroundColor = Color(HUMANGL_BACKGROUND_COLOR_R, HUMANGL_BACKGROUND_COLOR_G, HUMANGL_BACKGROUND_COLOR_B, HUMANGL_BACKGROUND_COLOR_A);
    simulationBackgroundColor = Color(HUMANGL_SIMULATION_BACKGROUND_R, HUMANGL_SIMULATION_BACKGROUND_G, HUMANGL_SIMULATION_BACKGROUND_B, HUMANGL_SIMULATION_BACKGROUND_A);

    // Reset color indices
    menuBgColorIndex = 0;
    simulationBgColorIndex = 0;
}

void BackgroundCustomizerMenu::initializeAvailableColors() {
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

void BackgroundCustomizerMenu::renderTitle() {
    float titleX = static_cast<float>(windowWidth) / 2.0f - HUMANGL_TITLE_X_OFFSET;
    float titleY = HUMANGL_TITLE_Y_POSITION;
    textRenderer.drawText(titleX, titleY, "Background Colors", 1.0f, 1.0f, 1.0f);
}

void BackgroundCustomizerMenu::renderBackgroundCustomization() {
    float contentY = HUMANGL_SETTINGS_CONTENT_START_Y;
    float lineSpacing = HUMANGL_SETTINGS_LINE_SPACING;

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

void BackgroundCustomizerMenu::drawBackgroundColorSelector(float x, float y, const Color& currentColor, bool isMenuColor) {
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
    std::string label = isMenuColor ? "Menu" : "Simulation";
    float textR = isHovering ? 1.0f : 0.8f;
    float textG = isHovering ? 1.0f : 0.8f;
    float textB = isHovering ? 1.0f : 0.8f;
    textRenderer.drawText(x + previewSize + 10.0f, y + 8.0f, label, textR, textG, textB);
}

void BackgroundCustomizerMenu::handleBackgroundCustomizationInput() {
    // Handle background color changes with M and S keys
    bool currentMState = keyboardState[SDL_SCANCODE_M];
    bool currentSState = keyboardState[SDL_SCANCODE_S];

    // Change menu background color with M key
    if (currentMState && !plusKeyPressed) { // Reuse plusKeyPressed for M key
        cycleMenuBackgroundColor();
        plusKeyPressed = true;
    } else if (!currentMState) {
        plusKeyPressed = false;
    }

    // Change simulation background color with S key
    if (currentSState && !minusKeyPressed) { // Reuse minusKeyPressed for S key
        cycleSimulationBackgroundColor();
        minusKeyPressed = true;
    } else if (!currentSState) {
        minusKeyPressed = false;
    }
}

void BackgroundCustomizerMenu::updateButtonHover(MouseHandler& mouseHandler) {
    mouseHandler.updateButtonHover(buttons);
}
