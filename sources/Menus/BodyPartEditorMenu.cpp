#include "../../includes/Menus/BodyPartEditorMenu.hpp"
#include "../../includes/Input/MouseHandler.hpp"
#include <algorithm>
#include <string>

BodyPartEditorMenu::BodyPartEditorMenu(TextRenderer& textRenderer)
    : MenuRenderer(textRenderer), externalLogic(nullptr),
      sliderX(0), sliderY(0), sliderWidth(0), sliderHeight(0),
      colorSelectorX(0), colorSelectorY(0), colorSelectorSize(0) {
    initializeButtons();
}

BodyPartEditorMenu::BodyPartEditorMenu(TextRenderer& textRenderer, BodyPartEditorLogic& logic)
    : MenuRenderer(textRenderer), externalLogic(&logic),
      sliderX(0), sliderY(0), sliderWidth(0), sliderHeight(0),
      colorSelectorX(0), colorSelectorY(0), colorSelectorSize(0) {
    initializeButtons();
}

void BodyPartEditorMenu::setSelectedBodyPart(BodyPart part) {
    getActiveLogic().setSelectedBodyPart(part);
    initializeButtons(); // Refresh buttons for new body part
}

void BodyPartEditorMenu::setBodyPartSettings(const std::map<BodyPart, BodyPartSettings>& settings) {
    getActiveLogic().setBodyPartSettings(settings);
}

// Method to get the logic component for external access
BodyPartEditorLogic& BodyPartEditorMenu::getLogic() {
    return getActiveLogic();
}

void BodyPartEditorMenu::setExternalLogic(BodyPartEditorLogic& logic) {
    externalLogic = &logic;
}

BodyPartEditorLogic& BodyPartEditorMenu::getActiveLogic() {
    return externalLogic ? *externalLogic : internalLogic;
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
    return getActiveLogic().handleMouseClick(mouseX, mouseY, sliderX, sliderY, sliderWidth, sliderHeight,
                                            colorSelectorX, colorSelectorY, colorSelectorSize);
}

void BodyPartEditorMenu::updateHover(float mouseX, float mouseY) {
    getActiveLogic().updateHover(mouseX, mouseY, sliderX, sliderY, sliderWidth, sliderHeight);
}

void BodyPartEditorMenu::handleMouseUp() {
    getActiveLogic().handleMouseUp();
}

void BodyPartEditorMenu::handleInput() {
    getActiveLogic().handleInput();
}

void BodyPartEditorMenu::cycleBodyPartColor() {
    getActiveLogic().cycleBodyPartColor();
}

void BodyPartEditorMenu::adjustBodyPartScale(float scaleMultiplier) {
    getActiveLogic().adjustBodyPartScale(scaleMultiplier);
}

void BodyPartEditorMenu::setBodyPartScale(float newScale) {
    getActiveLogic().setBodyPartScale(newScale);
}

void BodyPartEditorMenu::resetBodyPartToDefault() {
    getActiveLogic().resetBodyPartToDefault();
}

const BodyPartSettings& BodyPartEditorMenu::getBodyPartSettings(BodyPart part) const {
    return const_cast<BodyPartEditorMenu*>(this)->getActiveLogic().getBodyPartSettings(part);
}

const std::map<BodyPart, BodyPartSettings>& BodyPartEditorMenu::getAllBodyPartSettings() const {
    return const_cast<BodyPartEditorMenu*>(this)->getActiveLogic().getAllBodyPartSettings();
}

void BodyPartEditorMenu::renderTitle() {
    std::string title = "Customize " + getActiveLogic().getBodyPartName(getActiveLogic().getSelectedBodyPart());
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

    const BodyPartSettings& settings = getActiveLogic().getBodyPartSettings(getActiveLogic().getSelectedBodyPart());
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
    bool isDragging = getActiveLogic().getIsDraggingSlider();
    float handleR = isDragging ? 1.0f : (isHovering ? 0.9f : 0.7f);
    float handleG = isDragging ? 1.0f : (isHovering ? 0.9f : 0.7f);
    float handleB = isDragging ? 1.0f : (isHovering ? 0.9f : 0.7f);
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

    const Color& currentColor = getActiveLogic().getBodyPartSettings(getActiveLogic().getSelectedBodyPart()).color;

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

void BodyPartEditorMenu::updateButtonHover(MouseHandler& mouseHandler) {
    mouseHandler.updateButtonHover(buttons);
}
