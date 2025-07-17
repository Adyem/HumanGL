#pragma once

#include "../Human/DrawPerson.hpp"
#include "../humangl.hpp"
#include "../Simulation/AnimationManager.hpp"
#include "../Matrix/Matrix4.hpp"

class KeyboardHandler {
private:
    const Uint8* keyboardState;
    DrawPerson& drawPerson;
    AnimationManager* animationManager;
    
    // Camera rotation (for fixing the rotation around person issue)
    float cameraRotationY;
    float cameraDistance;
    float cameraHeight;

public:
    KeyboardHandler(DrawPerson& person);
    ~KeyboardHandler() = default;

    // Set animation manager (called after construction)
    void setAnimationManager(AnimationManager* animMgr) { animationManager = animMgr; }

    // Main input handling method
    void handleInput();

    // Manual body part control methods
    void handleBodyPartControls();
    
    // Camera control methods
    void handleCameraControls();
    void applyCameraTransform();

    // Build view matrix from camera parameters
    Matrix4 getViewMatrix() const;
    
    // Camera getters
    float getCameraRotationY() const { return cameraRotationY; }
    float getCameraDistance() const { return cameraDistance; }
    float getCameraHeight() const { return cameraHeight; }

    // Reset methods
    void resetCameraPosition();
    
    // Camera setters
    void setCameraRotation(float rotY) { cameraRotationY = rotY; }
    void setCameraDistance(float distance) { cameraDistance = distance; }
    void setCameraHeight(float height) { cameraHeight = height; }
};
