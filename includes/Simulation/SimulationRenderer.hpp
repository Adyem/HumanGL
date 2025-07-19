#pragma once

#include "../humangl.hpp"
#include "../Matrix/MatrixStack.hpp"
#include "../Human/DrawPerson.hpp"
#include "../Input/KeyboardHandler.hpp"

// Forward declaration
class SettingsMenuRenderer;

class SimulationRenderer {
private:
    MatrixStack matrixStack;
    DrawPerson& drawPerson;
    KeyboardHandler& keyboardHandler;
    SettingsMenuRenderer* settingsRenderer;

    // Rendering settings
    float nearPlane;
    float farPlane;
    float fov;
    int windowWidth;
    int windowHeight;

public:
    SimulationRenderer(DrawPerson& person, KeyboardHandler& kbHandler, int winWidth, int winHeight);
    ~SimulationRenderer() = default;

    // Main rendering method
    void render();
    
    // Setup methods
    void setupPerspective();
    void setupLighting();
    void setupScene();
    
    // Update window dimensions
    void updateWindowSize(int width, int height);

    // Set settings renderer for color access
    void setSettingsRenderer(SettingsMenuRenderer* renderer);

    // Apply body part customizations
    void applyBodyPartCustomizations();
};

