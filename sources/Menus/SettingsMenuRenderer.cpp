#include "../../includes/Menus/SettingsMenuRenderer.hpp"
#include "../../includes/Input/MouseHandler.hpp"

SettingsMenuRenderer::SettingsMenuRenderer(TextRenderer& textRenderer)
    : MenuRenderer(textRenderer), currentPage(SETTINGS_MAIN), selectedBodyPart(BODY_PART_HEAD),
      mainMenu(textRenderer), bodyPartSelector(textRenderer),
      bodyPartEditor(textRenderer), backgroundCustomizer(textRenderer) {
    initializeButtons();
}

void SettingsMenuRenderer::initializeButtons() {
    // Delegate button initialization to the appropriate component
    switch (currentPage) {
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
    switch (currentPage) {
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
    switch (currentPage) {
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
    MenuAction action = MENU_ACTION_NONE;

    switch (currentPage) {
        case SETTINGS_MAIN:
            action = mainMenu.handleButtonClick(buttonIndex);
            if (action == MENU_ACTION_BODY_CUSTOMIZATION) {
                setPage(BODY_CUSTOMIZATION);
                return MENU_ACTION_NONE;
            } else if (action == MENU_ACTION_BACKGROUND_CUSTOMIZATION) {
                setPage(BACKGROUND_CUSTOMIZATION);
                return MENU_ACTION_NONE;
            }
            break;

        case BODY_CUSTOMIZATION:
            action = bodyPartSelector.handleButtonClick(buttonIndex, selectedBodyPart);
            if (action == MENU_ACTION_BODY_PART_DETAIL) {
                bodyPartEditor.setSelectedBodyPart(selectedBodyPart);
                setPage(BODY_PART_DETAIL);
                return MENU_ACTION_NONE;
            } else if (action == MENU_ACTION_SETTINGS) {
                setPage(SETTINGS_MAIN);
                return MENU_ACTION_NONE;
            }
            break;

        case BODY_PART_DETAIL:
            action = bodyPartEditor.handleButtonClick(buttonIndex);
            if (action == MENU_ACTION_BODY_CUSTOMIZATION) {
                setPage(BODY_CUSTOMIZATION);
                return MENU_ACTION_NONE;
            } else if (action == MENU_ACTION_SETTINGS) {
                setPage(SETTINGS_MAIN);
                return MENU_ACTION_NONE;
            }
            break;

        case BACKGROUND_CUSTOMIZATION:
            action = backgroundCustomizer.handleButtonClick(buttonIndex);
            if (action == MENU_ACTION_SETTINGS) {
                setPage(SETTINGS_MAIN);
                return MENU_ACTION_NONE;
            }
            break;

        case RESOLUTION_SETTINGS:
            // For now, handle resolution settings like main menu
            action = mainMenu.handleButtonClick(buttonIndex);
            break;
    }

    return action;
}

// Page navigation
void SettingsMenuRenderer::setPage(SettingsPage page) {
    currentPage = page;
    initializeButtons();
}

void SettingsMenuRenderer::setSelectedBodyPart(BodyPart part) {
    selectedBodyPart = part;
    bodyPartEditor.setSelectedBodyPart(part);
}

SettingsPage SettingsMenuRenderer::getCurrentPage() const {
    return currentPage;
}

void SettingsMenuRenderer::resetToMainPage() {
    currentPage = SETTINGS_MAIN;
    selectedBodyPart = BODY_PART_HEAD;
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

// Body part customization (delegated to BodyPartEditor)
void SettingsMenuRenderer::cycleBodyPartColor() {
    bodyPartEditor.cycleBodyPartColor();
}

void SettingsMenuRenderer::adjustBodyPartScale(float scaleMultiplier) {
    bodyPartEditor.adjustBodyPartScale(scaleMultiplier);
}

void SettingsMenuRenderer::setBodyPartScale(float newScale) {
    bodyPartEditor.setBodyPartScale(newScale);
}

void SettingsMenuRenderer::resetBodyPartToDefault() {
    bodyPartEditor.resetBodyPartToDefault();
}

const BodyPartSettings& SettingsMenuRenderer::getBodyPartSettings(BodyPart part) const {
    return bodyPartEditor.getBodyPartSettings(part);
}

const std::map<BodyPart, BodyPartSettings>& SettingsMenuRenderer::getAllBodyPartSettings() const {
    return bodyPartEditor.getAllBodyPartSettings();
}

// Background color customization (delegated to BackgroundCustomizer)
void SettingsMenuRenderer::cycleMenuBackgroundColor() {
    backgroundCustomizer.cycleMenuBackgroundColor();
}

void SettingsMenuRenderer::cycleSimulationBackgroundColor() {
    backgroundCustomizer.cycleSimulationBackgroundColor();
}

void SettingsMenuRenderer::resetColorsToDefault() {
    backgroundCustomizer.resetColorsToDefault();
}

const Color& SettingsMenuRenderer::getMenuBackgroundColor() const {
    return backgroundCustomizer.getMenuBackgroundColor();
}

const Color& SettingsMenuRenderer::getSimulationBackgroundColor() const {
    return backgroundCustomizer.getSimulationBackgroundColor();
}

// Mouse interaction (delegated to appropriate component)
bool SettingsMenuRenderer::handleMouseClick(float mouseX, float mouseY) {
    switch (currentPage) {
        case BODY_PART_DETAIL:
            return bodyPartEditor.handleMouseClick(mouseX, mouseY);
        case BACKGROUND_CUSTOMIZATION:
            return backgroundCustomizer.handleMouseClick(mouseX, mouseY);
        default:
            return false;
    }
}

void SettingsMenuRenderer::updateHover(float mouseX, float mouseY) {
    switch (currentPage) {
        case BODY_PART_DETAIL:
            bodyPartEditor.updateHover(mouseX, mouseY);
            break;
        default:
            break;
    }
}

void SettingsMenuRenderer::handleMouseUp() {
    switch (currentPage) {
        case BODY_PART_DETAIL:
            bodyPartEditor.handleMouseUp();
            break;
        default:
            break;
    }
}

// Input handling (delegated to appropriate component)
void SettingsMenuRenderer::handleInput() {
    switch (currentPage) {
        case BODY_PART_DETAIL:
            bodyPartEditor.handleInput();
            break;
        case BACKGROUND_CUSTOMIZATION:
            backgroundCustomizer.handleInput();
            break;
        default:
            break;
    }
}

// Helper method to get the current menu renderer
MenuRenderer* SettingsMenuRenderer::getCurrentMenuRenderer() {
    switch (currentPage) {
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
    switch (currentPage) {
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
    // Sync body part settings between components if needed
    // For now, the BodyPartEditor manages its own settings
}

void SettingsMenuRenderer::syncBackgroundColors() {
    // Sync background colors between components if needed
    // For now, the BackgroundCustomizer manages its own colors
}

void SettingsMenuRenderer::updateButtonHover(MouseHandler& mouseHandler) {
    // Delegate button hover updates to the appropriate component
    switch (currentPage) {
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