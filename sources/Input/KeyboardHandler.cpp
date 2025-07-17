#include "../../includes/Input/KeyboardHandler.hpp"

KeyboardHandler::KeyboardHandler(DrawPerson& person)
    : keyboardState(SDL_GetKeyboardState(nullptr)), drawPerson(person), animationManager(nullptr),
      cameraRotationY(0.0f), cameraDistance(8.0f), cameraHeight(0.0f) {
}

void KeyboardHandler::handleInput() {
    // Update keyboard state
    keyboardState = SDL_GetKeyboardState(nullptr);

    // Handle different types of input
    handleBodyPartControls();
    handleCameraControls();
}

void KeyboardHandler::handleBodyPartControls() {
    // Check if we have an animation manager and if animations are running
    bool isAnimating = animationManager && animationManager->isAnimating();

    // Allow torso rotation during all animations, but restrict other controls during animations
    bool allowTorsoRotation = true; // Always allow character rotation
    bool allowOtherControls = !isAnimating;

    // Torso rotation using DrawPerson (allowed during all animations)
    if (allowTorsoRotation) {
        float currentTorsoY = drawPerson.getTorsoRotation();
        bool rotationChanged = false;

        if (keyboardState[SDL_SCANCODE_A]) {
            currentTorsoY -= 2.0f;
            drawPerson.setTorsoRotation(currentTorsoY);
            rotationChanged = true;
        }
        if (keyboardState[SDL_SCANCODE_D]) {
            currentTorsoY += 2.0f;
            drawPerson.setTorsoRotation(currentTorsoY);
            rotationChanged = true;
        }

        // Update the animation manager's base rotation if user changed it
        if (rotationChanged && animationManager) {
            animationManager->updateBaseTorsoRotation();
        }
    }

    // Head rotation using DrawPerson (only when no animation)
    if (allowOtherControls) {
        float currentHeadX, currentHeadY;
        drawPerson.getHeadRotation(currentHeadX, currentHeadY);
        if (keyboardState[SDL_SCANCODE_W]) {
            currentHeadX = fmaxf(currentHeadX - 2.0f, -45.0f);
            drawPerson.setHeadRotation(currentHeadX, currentHeadY);
        }
        if (keyboardState[SDL_SCANCODE_S]) {
            currentHeadX = fminf(currentHeadX + 2.0f, 45.0f);
            drawPerson.setHeadRotation(currentHeadX, currentHeadY);
        }
        if (keyboardState[SDL_SCANCODE_Q]) {
            currentHeadY = fmaxf(currentHeadY - 2.0f, -60.0f);
            drawPerson.setHeadRotation(currentHeadX, currentHeadY);
        }
        if (keyboardState[SDL_SCANCODE_E]) {
            currentHeadY = fminf(currentHeadY + 2.0f, 60.0f);
            drawPerson.setHeadRotation(currentHeadX, currentHeadY);
        }
    }

    // Left arm controls (1, 2, 3) using DrawPerson (only when no animation)
    if (allowOtherControls) {
        float leftUpperX, leftUpperZ, leftForearmX;
        drawPerson.getLeftArmRotation(leftUpperX, leftUpperZ, leftForearmX);
        if (keyboardState[SDL_SCANCODE_1]) {
            leftUpperX = fmaxf(leftUpperX - 2.0f, -180.0f);
            drawPerson.setLeftArmRotation(leftUpperX, leftUpperZ, leftForearmX);
        }
        if (keyboardState[SDL_SCANCODE_2]) {
            leftUpperZ = fmaxf(leftUpperZ - 2.0f, -90.0f);
            drawPerson.setLeftArmRotation(leftUpperX, leftUpperZ, leftForearmX);
        }
        if (keyboardState[SDL_SCANCODE_3]) {
            leftForearmX = fmaxf(leftForearmX - 2.0f, -135.0f);
            drawPerson.setLeftArmRotation(leftUpperX, leftUpperZ, leftForearmX);
        }
    }

    // Right arm controls (4, 5, 6) using DrawPerson (only when no animation)
    if (allowOtherControls) {
        float rightUpperX, rightUpperZ, rightForearmX;
        drawPerson.getRightArmRotation(rightUpperX, rightUpperZ, rightForearmX);
        if (keyboardState[SDL_SCANCODE_4]) {
            rightUpperX = fmaxf(rightUpperX - 2.0f, -180.0f);
            drawPerson.setRightArmRotation(rightUpperX, rightUpperZ, rightForearmX);
        }
        if (keyboardState[SDL_SCANCODE_5]) {
            rightUpperZ = fminf(rightUpperZ + 2.0f, 90.0f);
            drawPerson.setRightArmRotation(rightUpperX, rightUpperZ, rightForearmX);
        }
        if (keyboardState[SDL_SCANCODE_6]) {
            rightForearmX = fmaxf(rightForearmX - 2.0f, -135.0f);
            drawPerson.setRightArmRotation(rightUpperX, rightUpperZ, rightForearmX);
        }
    }

    // Left leg controls (7, 8) using DrawPerson (only when no animation)
    if (allowOtherControls) {
        float leftThighX, leftLowerLegX;
        drawPerson.getLeftLegRotation(leftThighX, leftLowerLegX);
        if (keyboardState[SDL_SCANCODE_7]) {
            leftThighX = fmaxf(leftThighX - 2.0f, -90.0f);
            drawPerson.setLeftLegRotation(leftThighX, leftLowerLegX);
        }
        if (keyboardState[SDL_SCANCODE_8]) {
            leftLowerLegX = fmaxf(leftLowerLegX - 2.0f, -135.0f);
            drawPerson.setLeftLegRotation(leftThighX, leftLowerLegX);
        }

        // Right leg controls (9, 0) using DrawPerson
        float rightThighX, rightLowerLegX;
        drawPerson.getRightLegRotation(rightThighX, rightLowerLegX);
        if (keyboardState[SDL_SCANCODE_9]) {
            rightThighX = fmaxf(rightThighX - 2.0f, -90.0f);
            drawPerson.setRightLegRotation(rightThighX, rightLowerLegX);
        }
        if (keyboardState[SDL_SCANCODE_0]) {
            rightLowerLegX = fmaxf(rightLowerLegX - 2.0f, -135.0f);
            drawPerson.setRightLegRotation(rightThighX, rightLowerLegX);
        }
    }
}

void KeyboardHandler::handleCameraControls() {
    // Camera rotation around the person (Left/Right arrows)
    if (keyboardState[SDL_SCANCODE_LEFT]) {
        cameraRotationY -= 2.0f;
    }
    if (keyboardState[SDL_SCANCODE_RIGHT]) {
        cameraRotationY += 2.0f;
    }
    
    // Camera distance (Up/Down arrows)
    if (keyboardState[SDL_SCANCODE_UP]) {
        cameraDistance = fmaxf(cameraDistance - 0.2f, 3.0f);
    }
    if (keyboardState[SDL_SCANCODE_DOWN]) {
        cameraDistance = fminf(cameraDistance + 0.2f, 15.0f);
    }
    
    // Camera height (Page Up/Page Down)
    if (keyboardState[SDL_SCANCODE_PAGEUP]) {
        cameraHeight += 0.1f;
    }
    if (keyboardState[SDL_SCANCODE_PAGEDOWN]) {
        cameraHeight -= 0.1f;
    }
}

void KeyboardHandler::applyCameraTransform() {
    // Apply camera transformations
    glTranslatef(0.0f, cameraHeight, -cameraDistance);
    glRotatef(cameraRotationY, 0.0f, 1.0f, 0.0f);
}

Matrix4 KeyboardHandler::getViewMatrix() const {
    Matrix4 view;
    view.translate(0.0f, cameraHeight, -cameraDistance);
    view.rotateY(cameraRotationY);
    return view;
}

void KeyboardHandler::resetCameraPosition() {
    // Reset camera to default position
    cameraRotationY = 0.0f;
    cameraDistance = 8.0f;
    cameraHeight = 0.0f;
}
