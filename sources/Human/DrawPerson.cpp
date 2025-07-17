#include "../../includes/Human/DrawPerson.hpp"

DrawPerson::DrawPerson() : torsoRotationY(HUMANGL_OPENGL_AXIS_NONE), jumpHeight(HUMANGL_OPENGL_AXIS_NONE) {
    // Initialize all body parts
    torso = std::make_unique<Torso>();
    neck = std::make_unique<Neck>();
    head = std::make_unique<Head>();
    eyes = std::make_unique<Eyes>();
    leftShoulder = std::make_unique<LeftShoulder>();
    rightShoulder = std::make_unique<RightShoulder>();
    leftArm = std::make_unique<LeftArm>();
    rightArm = std::make_unique<RightArm>();
    leftLeg = std::make_unique<LeftLeg>();
    rightLeg = std::make_unique<RightLeg>();
}

void DrawPerson::render() {
    // Enable face culling for better performance
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Apply global transformations
    glPushMatrix();

    // Apply jump height (affects entire body)
    glTranslatef(HUMANGL_OPENGL_AXIS_NONE, jumpHeight, HUMANGL_OPENGL_AXIS_NONE);

    // Apply torso rotation (this affects all body parts)
    glRotatef(torsoRotationY, HUMANGL_OPENGL_AXIS_NONE, HUMANGL_OPENGL_AXIS_Y, HUMANGL_OPENGL_AXIS_NONE);

    // Draw body parts in hierarchical order
    torso->render();           // Base of hierarchy
    neck->render();            // Connected to torso
    head->render();            // Connected to neck
    eyes->render();            // Eyes on the head (shows front direction)

    // Draw shoulder joints
    leftShoulder->render();    // Left shoulder joint
    rightShoulder->render();   // Right shoulder joint

    // Draw arms (connected to shoulders)
    leftArm->render();         // Left arm (upper arm + forearm connected)
    rightArm->render();        // Right arm (upper arm + forearm connected)

    // Draw legs (connected to torso)
    leftLeg->render();         // Left leg (thigh + lower leg connected)
    rightLeg->render();        // Right leg (thigh + lower leg connected)

    glPopMatrix();

    // Disable states we enabled
    glDisable(GL_CULL_FACE);
}

void DrawPerson::setTorsoRotation(float y) {
    torsoRotationY = y;
}

void DrawPerson::setJumpHeight(float height) {
    jumpHeight = height;
}

float DrawPerson::getTorsoRotation() const {
    return torsoRotationY;
}

void DrawPerson::setHeadRotation(float x, float y) {
    head->setHeadRotation(x, y);
    eyes->setHeadRotation(x, y);
}

void DrawPerson::setLeftArmRotation(float upperX, float upperZ, float forearmX) {
    leftArm->setUpperArmRotation(upperX, upperZ);
    leftArm->setForearmRotation(forearmX);
}

void DrawPerson::setRightArmRotation(float upperX, float upperZ, float forearmX) {
    rightArm->setUpperArmRotation(upperX, upperZ);
    rightArm->setForearmRotation(forearmX);
}

void DrawPerson::setLeftLegRotation(float thighX, float lowerLegX) {
    leftLeg->setThighRotation(thighX);
    leftLeg->setLowerLegRotation(lowerLegX);
}

void DrawPerson::setRightLegRotation(float thighX, float lowerLegX) {
    rightLeg->setThighRotation(thighX);
    rightLeg->setLowerLegRotation(lowerLegX);
}

void DrawPerson::getHeadRotation(float& x, float& y) const {
    head->getHeadRotation(x, y);
}

void DrawPerson::getLeftArmRotation(float& upperX, float& upperZ, float& forearmX) const {
    leftArm->getUpperArmRotation(upperX, upperZ);
    leftArm->getForearmRotation(forearmX);
}

void DrawPerson::getRightArmRotation(float& upperX, float& upperZ, float& forearmX) const {
    rightArm->getUpperArmRotation(upperX, upperZ);
    rightArm->getForearmRotation(forearmX);
}

void DrawPerson::getLeftLegRotation(float& thighX, float& lowerLegX) const {
    leftLeg->getThighRotation(thighX);
    leftLeg->getLowerLegRotation(lowerLegX);
}

void DrawPerson::getRightLegRotation(float& thighX, float& lowerLegX) const {
    rightLeg->getThighRotation(thighX);
    rightLeg->getLowerLegRotation(lowerLegX);
}
