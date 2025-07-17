#pragma once

#include "../humangl.hpp"
#include "../Human/DrawPerson.hpp"
#include "../Input/KeyboardHandler.hpp"
#include "../Matrix/MatrixStack.hpp"

class SimulationRenderer {
private:
    MatrixStack& matrixStack;
    DrawPerson& drawPerson;
    KeyboardHandler& keyboardHandler;
    
    // Rendering settings
    float nearPlane;
    float farPlane;
    float fov;
    int windowWidth;
    int windowHeight;

public:
    SimulationRenderer(MatrixStack& stack, DrawPerson& person, KeyboardHandler& kbHandler, int winWidth, int winHeight);
    ~SimulationRenderer() = default;

    // Main rendering method
    void render();
    
    // Setup methods
    void setupPerspective();
    void setupLighting();
    void setupScene();
    
    // Update window dimensions
    void updateWindowSize(int width, int height);
    
    // Getters
    float getNearPlane() const { return nearPlane; }
    float getFarPlane() const { return farPlane; }
    float getFOV() const { return fov; }
};

