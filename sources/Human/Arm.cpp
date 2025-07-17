#include "../../includes/Human/Arm.hpp"

Arm::Arm(float x, float y, float z)
    : BodyPartRenderer(HUMANGL_DEFAULT_SKIN_R, HUMANGL_DEFAULT_SKIN_G, HUMANGL_DEFAULT_SKIN_B), positionX(x), positionY(y), positionZ(z),
      upperArmX(HUMANGL_OPENGL_AXIS_NONE), upperArmZ(HUMANGL_OPENGL_AXIS_NONE), forearmX(HUMANGL_OPENGL_AXIS_NONE) {
    // Skin color for arms
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
    glScalef(HUMANGL_UPPER_ARM_SCALE_X, HUMANGL_UPPER_ARM_SCALE_Y, HUMANGL_UPPER_ARM_SCALE_Z);
    drawColoredCube(colorR, colorG, colorB);  // Skin color for upper arms
    glPopMatrix();

    // Draw forearm (connected to upper arm)
    glTranslatef(HUMANGL_OPENGL_AXIS_NONE, HUMANGL_FOREARM_Y_OFFSET, HUMANGL_OPENGL_AXIS_NONE);
    glRotatef(forearmX, HUMANGL_OPENGL_AXIS_X, HUMANGL_OPENGL_AXIS_NONE, HUMANGL_OPENGL_AXIS_NONE);
    glTranslatef(HUMANGL_OPENGL_AXIS_NONE, HUMANGL_FOREARM_Y_POSITION, HUMANGL_OPENGL_AXIS_NONE);
    glScalef(HUMANGL_FOREARM_SCALE_X, HUMANGL_FOREARM_SCALE_Y, HUMANGL_FOREARM_SCALE_Z);
    drawColoredCube(colorR, colorG, colorB);  // Skin color for forearms

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

/* Left and Right Arm */
LeftArm::LeftArm() : Arm(HUMANGL_LEFT_ARM_X_POSITION, HUMANGL_ARM_Y_POSITION, HUMANGL_ARM_Z_POSITION) {
}

RightArm::RightArm() : Arm(HUMANGL_RIGHT_ARM_X_POSITION, HUMANGL_ARM_Y_POSITION, HUMANGL_ARM_Z_POSITION) {
}
