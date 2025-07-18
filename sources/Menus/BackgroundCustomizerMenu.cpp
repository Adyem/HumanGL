#include "../../includes/Menus/BackgroundCustomizerMenu.hpp"
#include "../../includes/Input/MouseHandler.hpp"

BackgroundCustomizerMenu::BackgroundCustomizerMenu(TextRenderer& textRenderer)
    : MenuRenderer(textRenderer), externalLogic(nullptr),
      menuColorSelectorX(0), menuColorSelectorY(0), menuColorSelectorSize(0),
      simColorSelectorX(0), simColorSelectorY(0), simColorSelectorSize(0) {
    initializeButtons();
}

BackgroundCustomizerMenu::BackgroundCustomizerMenu(TextRenderer& textRenderer, BackgroundCustomizerLogic& logic)
    : MenuRenderer(textRenderer), externalLogic(&logic),
      menuColorSelectorX(0), menuColorSelectorY(0), menuColorSelectorSize(0),
      simColorSelectorX(0), simColorSelectorY(0), simColorSelectorSize(0) {
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
    return getActiveLogic().handleButtonClick(buttonIndex);
}

bool BackgroundCustomizerMenu::handleMouseClick(float mouseX, float mouseY) {
    return getActiveLogic().handleMouseClick(mouseX, mouseY, menuColorSelectorX, menuColorSelectorY, menuColorSelectorSize,
                                            simColorSelectorX, simColorSelectorY, simColorSelectorSize);
}

void BackgroundCustomizerMenu::handleInput() {
    getActiveLogic().handleInput();
}

void BackgroundCustomizerMenu::cycleMenuBackgroundColor() {
    getActiveLogic().cycleMenuBackgroundColor();
}

void BackgroundCustomizerMenu::cycleSimulationBackgroundColor() {
    getActiveLogic().cycleSimulationBackgroundColor();
}

void BackgroundCustomizerMenu::resetColorsToDefault() {
    getActiveLogic().resetColorsToDefault();
}

const Color& BackgroundCustomizerMenu::getMenuBackgroundColor() const {
    return const_cast<BackgroundCustomizerMenu*>(this)->getActiveLogic().getMenuBackgroundColor();
}

const Color& BackgroundCustomizerMenu::getSimulationBackgroundColor() const {
    return const_cast<BackgroundCustomizerMenu*>(this)->getActiveLogic().getSimulationBackgroundColor();
}

// Method to get the logic component for external access
BackgroundCustomizerLogic& BackgroundCustomizerMenu::getLogic() {
    return getActiveLogic();
}

void BackgroundCustomizerMenu::setExternalLogic(BackgroundCustomizerLogic& logic) {
    externalLogic = &logic;
}

BackgroundCustomizerLogic& BackgroundCustomizerMenu::getActiveLogic() {
    return externalLogic ? *externalLogic : internalLogic;
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
    drawBackgroundColorSelector(colorX, contentY, getActiveLogic().getMenuBackgroundColor(), true);
    contentY += lineSpacing * 2.5f;

    // Simulation background color section
    textRenderer.drawText(HUMANGL_SETTINGS_LEFT_MARGIN, contentY, "Simulation Background Color:", 0.9f, 0.9f, 0.9f);
    contentY += lineSpacing;

    drawBackgroundColorSelector(colorX, contentY, getActiveLogic().getSimulationBackgroundColor(), false);
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

void BackgroundCustomizerMenu::updateButtonHover(MouseHandler& mouseHandler) {
    mouseHandler.updateButtonHover(buttons);
}
