#pragma once

#include "../humangl.hpp"
#include "SettingsMainMenu.hpp"
#include "BodyPartSelectorMenu.hpp"
#include "BodyPartEditorMenu.hpp"
#include "GraphicsMenu.hpp"

class SettingsMenuLogic {
private:
    // Current state
    SettingsPage currentPage;
    BodyPart selectedBodyPart;
    
    // Logic components
    SettingsMainMenuLogic mainMenuLogic;
    BodyPartSelectorLogic bodyPartSelectorLogic;
    BodyPartEditorLogic bodyPartEditorLogic;
    BackgroundCustomizerLogic backgroundCustomizerLogic;

public:
    SettingsMenuLogic();
    virtual ~SettingsMenuLogic() = default;

    // Handle button clicks and navigation
    MenuAction handleButtonClick(int buttonIndex);

    // Page navigation
    void setPage(SettingsPage page);
    void setSelectedBodyPart(BodyPart part);
    SettingsPage getCurrentPage() const { return currentPage; }
    BodyPart getSelectedBodyPart() const { return selectedBodyPart; }
    void resetToMainPage();

    // Body part customization (delegated to BodyPartEditorLogic)
    void cycleBodyPartColor();
    void adjustBodyPartScale(float scaleMultiplier);
    void setBodyPartScale(float newScale);
    void resetBodyPartToDefault();

    const BodyPartSettings& getBodyPartSettings(BodyPart part) const;
    const std::map<BodyPart, BodyPartSettings>& getAllBodyPartSettings() const;

    // Background color customization (delegated to BackgroundCustomizerLogic)
    void cycleMenuBackgroundColor();
    void cycleSimulationBackgroundColor();
    void resetColorsToDefault();

    const Color& getMenuBackgroundColor() const;
    const Color& getSimulationBackgroundColor() const;

    // Mouse interaction (delegated to appropriate logic component)
    bool handleMouseClick(float mouseX, float mouseY, float sliderX, float sliderY, float sliderWidth, float sliderHeight,
                         float colorSelectorX, float colorSelectorY, float colorSelectorSize,
                         float menuColorSelectorX, float menuColorSelectorY, float menuColorSelectorSize,
                         float simColorSelectorX, float simColorSelectorY, float simColorSelectorSize);
    void updateHover(float mouseX, float mouseY, float sliderX, float sliderY, float sliderWidth, float sliderHeight);
    void handleMouseUp();

    // Input handling (delegated to appropriate logic component)
    void handleInput();

    // Get the appropriate logic component for current page
    SettingsMainMenuLogic& getMainMenuLogic() { return mainMenuLogic; }
    BodyPartSelectorLogic& getBodyPartSelectorLogic() { return bodyPartSelectorLogic; }
    BodyPartEditorLogic& getBodyPartEditorLogic() { return bodyPartEditorLogic; }
    BackgroundCustomizerLogic& getBackgroundCustomizerLogic() { return backgroundCustomizerLogic; }

private:
    // Helper method to sync settings between components
    void syncBodyPartSettings();
};
