#include "../../includes/Menus/SettingsMenuRenderer.hpp"
#include "../../includes/Input/MouseHandler.hpp"

SettingsMenuRenderer::SettingsMenuRenderer(TextRenderer& textRenderer)
    : MenuRenderer(textRenderer),
      mainMenu(textRenderer), bodyPartSelector(textRenderer),
      bodyPartEditor(textRenderer), backgroundCustomizer(textRenderer) {
    // Sync the shared logic components with the menu components
    syncLogicWithMenuComponents();
    initializeButtons();
}

void SettingsMenuRenderer::initializeButtons() {
    // Delegate button initialization to the appropriate component
    switch (logic.getCurrentPage()) {
        case SETTINGS_MAIN:
            mainMenu.initializeButtons();
            break;
        case BODY_CUSTOMIZATION:
            bodyPartSelector.initializeButtons();
            break;
        case BODY_PART_DETAIL:
            bodyPartEditor.initializeButtons();
            break;
        case BACKGROUND_CUSTOMIZATION:
            backgroundCustomizer.initializeButtons();
            break;
        case RESOLUTION_SETTINGS:
            mainMenu.initializeButtons(); // For now, use main menu for resolution settings
            break;
        default:
            mainMenu.initializeButtons();
            break;
    }
}

void SettingsMenuRenderer::render(const std::vector<MenuButton>& externalButtons) {
    // Delegate rendering to the appropriate component
    getCurrentMenuRenderer()->render(externalButtons);
}

void SettingsMenuRenderer::render() {
    // Delegate rendering to the appropriate component
    switch (logic.getCurrentPage()) {
        case SETTINGS_MAIN:
            mainMenu.render();
            break;
        case BODY_CUSTOMIZATION:
            bodyPartSelector.render();
            break;
        case BODY_PART_DETAIL:
            bodyPartEditor.render();
            break;
        case BACKGROUND_CUSTOMIZATION:
            backgroundCustomizer.render();
            break;
        case RESOLUTION_SETTINGS:
            mainMenu.render(); // For now, use main menu for resolution settings
            break;
        default:
            mainMenu.render();
            break;
    }
}

const std::vector<MenuButton>& SettingsMenuRenderer::getButtons() const {
    // Delegate to the appropriate component
    switch (logic.getCurrentPage()) {
        case SETTINGS_MAIN:
            return mainMenu.getButtons();
        case BODY_CUSTOMIZATION:
            return bodyPartSelector.getButtons();
        case BODY_PART_DETAIL:
            return bodyPartEditor.getButtons();
        case BACKGROUND_CUSTOMIZATION:
            return backgroundCustomizer.getButtons();
        case RESOLUTION_SETTINGS:
            return mainMenu.getButtons(); // For now, use main menu for resolution settings
        default:
            return mainMenu.getButtons();
    }
}

MenuAction SettingsMenuRenderer::handleButtonClick(int buttonIndex) {
    MenuAction action = logic.handleButtonClick(buttonIndex);

    // If page changed, reinitialize buttons for the new page
    if (action == MENU_ACTION_NONE) {
        initializeButtons();
    }

    return action;
}

// Page navigation (delegates to logic)
void SettingsMenuRenderer::setPage(SettingsPage page) {
    logic.setPage(page);
    initializeButtons();
}

void SettingsMenuRenderer::setSelectedBodyPart(BodyPart part) {
    logic.setSelectedBodyPart(part);
    bodyPartEditor.setSelectedBodyPart(part);
}

SettingsPage SettingsMenuRenderer::getCurrentPage() const {
    return logic.getCurrentPage();
}

void SettingsMenuRenderer::resetToMainPage() {
    logic.resetToMainPage();
    initializeButtons();
}

void SettingsMenuRenderer::updateWindowSize(int width, int height) {
    // Update base class window size
    MenuRenderer::updateWindowSize(width, height);

    // Update all component menu renderers
    mainMenu.updateWindowSize(width, height);
    bodyPartSelector.updateWindowSize(width, height);
    bodyPartEditor.updateWindowSize(width, height);
    backgroundCustomizer.updateWindowSize(width, height);

    // Reinitialize buttons for new window size
    initializeButtons();
}

// Body part customization (delegates to logic - now using shared state)
void SettingsMenuRenderer::cycleBodyPartColor() {
    logic.cycleBodyPartColor();
}

void SettingsMenuRenderer::adjustBodyPartScale(float scaleMultiplier) {
    logic.adjustBodyPartScale(scaleMultiplier);
}

void SettingsMenuRenderer::setBodyPartScale(float newScale) {
    logic.setBodyPartScale(newScale);
}

void SettingsMenuRenderer::resetBodyPartToDefault() {
    logic.resetBodyPartToDefault();
}

const BodyPartSettings& SettingsMenuRenderer::getBodyPartSettings(BodyPart part) const {
    // Always return from the main logic (single source of truth)
    return logic.getBodyPartSettings(part);
}

const std::map<BodyPart, BodyPartSettings>& SettingsMenuRenderer::getAllBodyPartSettings() const {
    // Always return from the main logic (single source of truth)
    return logic.getAllBodyPartSettings();
}

// Background color customization (delegates to logic - now using shared state)
void SettingsMenuRenderer::cycleMenuBackgroundColor() {
    logic.cycleMenuBackgroundColor();
}

void SettingsMenuRenderer::cycleSimulationBackgroundColor() {
    logic.cycleSimulationBackgroundColor();
}

void SettingsMenuRenderer::resetColorsToDefault() {
    logic.resetColorsToDefault();
}

const Color& SettingsMenuRenderer::getMenuBackgroundColor() const {
    // Always return from the main logic (single source of truth)
    return logic.getMenuBackgroundColor();
}

const Color& SettingsMenuRenderer::getSimulationBackgroundColor() const {
    // Always return from the main logic (single source of truth)
    return logic.getSimulationBackgroundColor();
}

// Mouse interaction (delegates to rendering components - now using shared state)
bool SettingsMenuRenderer::handleMouseClick(float mouseX, float mouseY) {
    // Delegate to the rendering components which handle UI positioning
    switch (logic.getCurrentPage()) {
        case BODY_PART_DETAIL:
            return bodyPartEditor.handleMouseClick(mouseX, mouseY);
        case BACKGROUND_CUSTOMIZATION:
            return backgroundCustomizer.handleMouseClick(mouseX, mouseY);
        default:
            return false;
    }
}

void SettingsMenuRenderer::updateHover(float mouseX, float mouseY) {
    switch (logic.getCurrentPage()) {
        case BODY_PART_DETAIL:
            bodyPartEditor.updateHover(mouseX, mouseY);
            break;
        default:
            break;
    }
}

void SettingsMenuRenderer::handleMouseUp() {
    switch (logic.getCurrentPage()) {
        case BODY_PART_DETAIL:
            bodyPartEditor.handleMouseUp();
            break;
        default:
            break;
    }
}

// Input handling (delegates to logic - now using shared state)
void SettingsMenuRenderer::handleInput() {
    logic.handleInput();
}

// Helper method to get the current menu renderer
MenuRenderer* SettingsMenuRenderer::getCurrentMenuRenderer() {
    switch (logic.getCurrentPage()) {
        case SETTINGS_MAIN:
            return &mainMenu;
        case BODY_CUSTOMIZATION:
            return &bodyPartSelector;
        case BODY_PART_DETAIL:
            return &bodyPartEditor;
        case BACKGROUND_CUSTOMIZATION:
            return &backgroundCustomizer;
        case RESOLUTION_SETTINGS:
            return &mainMenu; // For now, use main menu for resolution settings
        default:
            return &mainMenu;
    }
}

const MenuRenderer* SettingsMenuRenderer::getCurrentMenuRenderer() const {
    switch (logic.getCurrentPage()) {
        case SETTINGS_MAIN:
            return &mainMenu;
        case BODY_CUSTOMIZATION:
            return &bodyPartSelector;
        case BODY_PART_DETAIL:
            return &bodyPartEditor;
        case BACKGROUND_CUSTOMIZATION:
            return &backgroundCustomizer;
        case RESOLUTION_SETTINGS:
            return &mainMenu; // For now, use main menu for resolution settings
        default:
            return &mainMenu;
    }
}

void SettingsMenuRenderer::syncBodyPartSettings() {
    // Sync body part settings from main logic to rendering component
    bodyPartEditor.setBodyPartSettings(logic.getAllBodyPartSettings());
}

void SettingsMenuRenderer::syncBackgroundColors() {
    // Background colors are now managed by the logic component
    // No sync needed as rendering components get colors from logic
}

void SettingsMenuRenderer::syncLogicWithMenuComponents() {
    // Set the menu components to use the main logic components directly
    // This eliminates the need for synchronization by using shared state

    bodyPartEditor.setExternalLogic(logic.getBodyPartEditorLogic());
    backgroundCustomizer.setExternalLogic(logic.getBackgroundCustomizerLogic());

    // Sync initial settings to rendering components
    syncBodyPartSettings();
}

void SettingsMenuRenderer::updateButtonHover(MouseHandler& mouseHandler) {
    // Delegate button hover updates to the appropriate component
    switch (logic.getCurrentPage()) {
        case SETTINGS_MAIN:
            mainMenu.updateButtonHover(mouseHandler);
            break;
        case BODY_CUSTOMIZATION:
            bodyPartSelector.updateButtonHover(mouseHandler);
            break;
        case BODY_PART_DETAIL:
            bodyPartEditor.updateButtonHover(mouseHandler);
            break;
        case BACKGROUND_CUSTOMIZATION:
            backgroundCustomizer.updateButtonHover(mouseHandler);
            break;
        case RESOLUTION_SETTINGS:
            mainMenu.updateButtonHover(mouseHandler);
            break;
    }
}