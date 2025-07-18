#include "../../includes/Human/Arm.hpp"

Arm::Arm(float x, float y, float z)
    : BodyPartRenderer(HUMANGL_DEFAULT_SKIN_R, HUMANGL_DEFAULT_SKIN_G, HUMANGL_DEFAULT_SKIN_B), positionX(x), positionY(y), positionZ(z),
      upperArmX(HUMANGL_OPENGL_AXIS_NONE), upperArmZ(HUMANGL_OPENGL_AXIS_NONE), forearmX(HUMANGL_OPENGL_AXIS_NONE),
      upperArmR(HUMANGL_DEFAULT_CLOTHING_R), upperArmG(HUMANGL_DEFAULT_CLOTHING_G), upperArmB(HUMANGL_DEFAULT_CLOTHING_B),
      forearmR(HUMANGL_DEFAULT_SKIN_R), forearmG(HUMANGL_DEFAULT_SKIN_G), forearmB(HUMANGL_DEFAULT_SKIN_B) {
    // Upper arms use clothing color (blue), forearms use skin color
}

void Arm::render() {
    // Draw the entire arm as a connected hierarchy
    glPushMatrix();
    glTranslatef(positionX, positionY, positionZ);
    glRotatef(upperArmX, HUMANGL_OPENGL_AXIS_X, HUMANGL_OPENGL_AXIS_NONE, HUMANGL_OPENGL_AXIS_NONE);
    glRotatef(upperArmZ, HUMANGL_OPENGL_AXIS_NONE, HUMANGL_OPENGL_AXIS_NONE, HUMANGL_OPENGL_AXIS_Z);

    // Draw upper arm
    glPushMatrix();
    glTranslatef(HUMANGL_OPENGL_AXIS_NONE, HUMANGL_UPPER_ARM_Y_OFFSET, HUMANGL_OPENGL_AXIS_NONE);
    glScalef(HUMANGL_UPPER_ARM_SCALE_X * scaleX, HUMANGL_UPPER_ARM_SCALE_Y * scaleY, HUMANGL_UPPER_ARM_SCALE_Z * scaleZ);
    drawColoredCube(upperArmR, upperArmG, upperArmB);  // Individual upper arm color
    glPopMatrix();

    // Draw forearm (connected to upper arm)
    glTranslatef(HUMANGL_OPENGL_AXIS_NONE, HUMANGL_FOREARM_Y_OFFSET, HUMANGL_OPENGL_AXIS_NONE);
    glRotatef(forearmX, HUMANGL_OPENGL_AXIS_X, HUMANGL_OPENGL_AXIS_NONE, HUMANGL_OPENGL_AXIS_NONE);
    glTranslatef(HUMANGL_OPENGL_AXIS_NONE, HUMANGL_FOREARM_Y_POSITION, HUMANGL_OPENGL_AXIS_NONE);
    glScalef(HUMANGL_FOREARM_SCALE_X * scaleX, HUMANGL_FOREARM_SCALE_Y * scaleY, HUMANGL_FOREARM_SCALE_Z * scaleZ);
    drawColoredCube(forearmR, forearmG, forearmB);  // Individual forearm color

    glPopMatrix();
}

void Arm::setUpperArmRotation(float x, float z) {
    upperArmX = x;
    upperArmZ = z;
}

void Arm::setForearmRotation(float x) {
    forearmX = x;
}

void Arm::getUpperArmRotation(float& x, float& z) const {
    x = upperArmX;
    z = upperArmZ;
}

void Arm::getForearmRotation(float& x) const {
    x = forearmX;
}

void Arm::setUpperArmColor(float r, float g, float b) {
    upperArmR = r;
    upperArmG = g;
    upperArmB = b;
}

void Arm::setForearmColor(float r, float g, float b) {
    forearmR = r;
    forearmG = g;
    forearmB = b;
}

/* Left and Right Arm */
LeftArm::LeftArm() : Arm(HUMANGL_LEFT_ARM_X_POSITION, HUMANGL_ARM_Y_POSITION, HUMANGL_ARM_Z_POSITION) {
}

RightArm::RightArm() : Arm(HUMANGL_RIGHT_ARM_X_POSITION, HUMANGL_ARM_Y_POSITION, HUMANGL_ARM_Z_POSITION) {
}
