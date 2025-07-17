#include "../../includes/Input/KeyboardHandler.hpp"

KeyboardHandler::KeyboardHandler(DrawPerson& person)
    : keyboardState(SDL_GetKeyboardState(nullptr)), drawPerson(person), animationManager(nullptr),
      cameraRotationY(HUMANGL_CAMERA_DEFAULT_ROTATION_Y), cameraDistance(HUMANGL_CAMERA_DEFAULT_DISTANCE), cameraHeight(HUMANGL_CAMERA_DEFAULT_HEIGHT) {
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
            currentTorsoY -= HUMANGL_TORSO_ROTATION_SPEED;
            drawPerson.setTorsoRotation(currentTorsoY);
            rotationChanged = true;
        }
        if (keyboardState[SDL_SCANCODE_D]) {
            currentTorsoY += HUMANGL_TORSO_ROTATION_SPEED;
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

void KeyboardHandler::resetCameraPosition() {
    // Reset camera to default position
    cameraRotationY = 0.0f;
    cameraDistance = 8.0f;
    cameraHeight = 0.0f;
}
