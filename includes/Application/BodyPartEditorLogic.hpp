#pragma once

#include "../humangl.hpp"
#include <map>
#include <vector>

class BodyPartEditorLogic {
private:
    BodyPart selectedBodyPart;
    std::map<BodyPart, BodyPartSettings> bodyPartSettings;
    int currentColorIndex;
    std::vector<Color> availableColors;
    bool isDraggingSlider;
    
    // Input handling state
    const Uint8* keyboardState;
    bool plusKeyPressed;
    bool minusKeyPressed;
    bool cKeyPressed;

public:
    BodyPartEditorLogic();
    virtual ~BodyPartEditorLogic() = default;

    // Set the body part to edit
    void setSelectedBodyPart(BodyPart part);
    void setBodyPartSettings(const std::map<BodyPart, BodyPartSettings>& settings);

    // Handle button clicks
    MenuAction handleButtonClick(int buttonIndex);

    // Mouse interaction logic
    bool handleMouseClick(float mouseX, float mouseY, float sliderX, float sliderY, float sliderWidth, float sliderHeight,
                         float colorSelectorX, float colorSelectorY, float colorSelectorSize);
    void updateHover(float mouseX, float mouseY, float sliderX, float sliderY, float sliderWidth, float sliderHeight);
    void handleMouseUp();

    // Input handling
    void handleInput();

    // Body part customization
    void cycleBodyPartColor();
    void adjustBodyPartScale(float scaleMultiplier);
    void setBodyPartScale(float newScale);
    void resetBodyPartToDefault();

    // Get current settings
    const BodyPartSettings& getBodyPartSettings(BodyPart part) const;
    const std::map<BodyPart, BodyPartSettings>& getAllBodyPartSettings() const;
    BodyPart getSelectedBodyPart() const { return selectedBodyPart; }
    const std::vector<Color>& getAvailableColors() const { return availableColors; }
    int getCurrentColorIndex() const { return currentColorIndex; }
    bool getIsDraggingSlider() const { return isDraggingSlider; }

    // Get body part name as string
    std::string getBodyPartName(BodyPart part) const;

private:
    // Helper methods
    void initializeAvailableColors();
    BodyPartSettings getDefaultBodyPartSettings(BodyPart part) const;
    void handleCustomizationInput();
};
