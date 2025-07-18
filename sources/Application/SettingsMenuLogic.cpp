#include "../../includes/Application/SettingsMenuLogic.hpp"

SettingsMenuLogic::SettingsMenuLogic()
    : currentPage(SETTINGS_MAIN), selectedBodyPart(BODY_PART_HEAD) {
    // Initialize with default settings
    syncBodyPartSettings();
}

MenuAction SettingsMenuLogic::handleButtonClick(int buttonIndex) {
    MenuAction action = MENU_ACTION_NONE;
    
    switch (currentPage) {
        case SETTINGS_MAIN:
            action = mainMenuLogic.handleButtonClick(buttonIndex);
            if (action == MENU_ACTION_BODY_CUSTOMIZATION) {
                setPage(BODY_CUSTOMIZATION);
                return MENU_ACTION_NONE;
            } else if (action == MENU_ACTION_BACKGROUND_CUSTOMIZATION) {
                setPage(BACKGROUND_CUSTOMIZATION);
                return MENU_ACTION_NONE;
            }
            break;
            
        case BODY_CUSTOMIZATION:
            action = bodyPartSelectorLogic.handleButtonClick(buttonIndex, selectedBodyPart);
            if (action == MENU_ACTION_BODY_PART_DETAIL) {
                bodyPartEditorLogic.setSelectedBodyPart(selectedBodyPart);
                bodyPartEditorLogic.setBodyPartSettings(bodyPartEditorLogic.getAllBodyPartSettings());
                setPage(BODY_PART_DETAIL);
                return MENU_ACTION_NONE;
            } else if (action == MENU_ACTION_SETTINGS) {
                setPage(SETTINGS_MAIN);
                return MENU_ACTION_NONE;
            }
            break;
            
        case BODY_PART_DETAIL:
            action = bodyPartEditorLogic.handleButtonClick(buttonIndex);
            if (action == MENU_ACTION_BODY_CUSTOMIZATION) {
                setPage(BODY_CUSTOMIZATION);
                return MENU_ACTION_NONE;
            } else if (action == MENU_ACTION_SETTINGS) {
                setPage(SETTINGS_MAIN);
                return MENU_ACTION_NONE;
            }
            break;
            
        case BACKGROUND_CUSTOMIZATION:
            action = backgroundCustomizerLogic.handleButtonClick(buttonIndex);
            if (action == MENU_ACTION_SETTINGS) {
                setPage(SETTINGS_MAIN);
                return MENU_ACTION_NONE;
            }
            break;
            
        case RESOLUTION_SETTINGS:
            // For now, handle resolution settings like main menu
            action = mainMenuLogic.handleButtonClick(buttonIndex);
            break;
    }
    
    return action;
}

// Page navigation
void SettingsMenuLogic::setPage(SettingsPage page) {
    currentPage = page;
}

void SettingsMenuLogic::setSelectedBodyPart(BodyPart part) {
    selectedBodyPart = part;
    bodyPartEditorLogic.setSelectedBodyPart(part);
    // Sync the current settings to the body part editor
    bodyPartEditorLogic.setBodyPartSettings(bodyPartEditorLogic.getAllBodyPartSettings());
}

void SettingsMenuLogic::resetToMainPage() {
    currentPage = SETTINGS_MAIN;
    selectedBodyPart = BODY_PART_HEAD;
}

// Body part customization (delegated to BodyPartEditorLogic)
void SettingsMenuLogic::cycleBodyPartColor() {
    bodyPartEditorLogic.cycleBodyPartColor();
}

void SettingsMenuLogic::adjustBodyPartScale(float scaleMultiplier) {
    bodyPartEditorLogic.adjustBodyPartScale(scaleMultiplier);
}

void SettingsMenuLogic::setBodyPartScale(float newScale) {
    bodyPartEditorLogic.setBodyPartScale(newScale);
}

void SettingsMenuLogic::resetBodyPartToDefault() {
    bodyPartEditorLogic.resetBodyPartToDefault();
}

const BodyPartSettings& SettingsMenuLogic::getBodyPartSettings(BodyPart part) const {
    return bodyPartEditorLogic.getBodyPartSettings(part);
}

const std::map<BodyPart, BodyPartSettings>& SettingsMenuLogic::getAllBodyPartSettings() const {
    return bodyPartEditorLogic.getAllBodyPartSettings();
}

// Background color customization (delegated to BackgroundCustomizerLogic)
void SettingsMenuLogic::cycleMenuBackgroundColor() {
    backgroundCustomizerLogic.cycleMenuBackgroundColor();
}

void SettingsMenuLogic::cycleSimulationBackgroundColor() {
    backgroundCustomizerLogic.cycleSimulationBackgroundColor();
}

void SettingsMenuLogic::resetColorsToDefault() {
    backgroundCustomizerLogic.resetColorsToDefault();
}

const Color& SettingsMenuLogic::getMenuBackgroundColor() const {
    return backgroundCustomizerLogic.getMenuBackgroundColor();
}

const Color& SettingsMenuLogic::getSimulationBackgroundColor() const {
    return backgroundCustomizerLogic.getSimulationBackgroundColor();
}

// Mouse interaction (delegated to appropriate logic component)
bool SettingsMenuLogic::handleMouseClick(float mouseX, float mouseY, float sliderX, float sliderY,
                                        float sliderWidth, float sliderHeight, float colorSelectorX,
                                        float colorSelectorY, float colorSelectorSize,
                                        float menuColorSelectorX, float menuColorSelectorY, float menuColorSelectorSize,
                                        float simColorSelectorX, float simColorSelectorY, float simColorSelectorSize) {
    switch (currentPage) {
        case BODY_PART_DETAIL:
            return bodyPartEditorLogic.handleMouseClick(mouseX, mouseY, sliderX, sliderY, sliderWidth, sliderHeight,
                                                       colorSelectorX, colorSelectorY, colorSelectorSize);
        case BACKGROUND_CUSTOMIZATION:
            return backgroundCustomizerLogic.handleMouseClick(mouseX, mouseY, menuColorSelectorX, menuColorSelectorY, menuColorSelectorSize,
                                                             simColorSelectorX, simColorSelectorY, simColorSelectorSize);
        default:
            return false;
    }
}

void SettingsMenuLogic::updateHover(float mouseX, float mouseY, float sliderX, float sliderY,
                                   float sliderWidth, float sliderHeight) {
    switch (currentPage) {
        case BODY_PART_DETAIL:
            bodyPartEditorLogic.updateHover(mouseX, mouseY, sliderX, sliderY, sliderWidth, sliderHeight);
            break;
        default:
            break;
    }
}

void SettingsMenuLogic::handleMouseUp() {
    switch (currentPage) {
        case BODY_PART_DETAIL:
            bodyPartEditorLogic.handleMouseUp();
            break;
        default:
            break;
    }
}

// Input handling (delegated to appropriate logic component)
void SettingsMenuLogic::handleInput() {
    switch (currentPage) {
        case BODY_PART_DETAIL:
            bodyPartEditorLogic.handleInput();
            break;
        case BACKGROUND_CUSTOMIZATION:
            backgroundCustomizerLogic.handleInput();
            break;
        default:
            break;
    }
}

void SettingsMenuLogic::syncBodyPartSettings() {
    // Sync body part settings between components if needed
    // For now, the BodyPartEditorLogic manages its own settings
}
