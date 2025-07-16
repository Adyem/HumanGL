#include "../../includes/Human/Arm.hpp"

Arm::Arm(float x, float y, float z)
    : BodyPartRenderer(0.8f, 0.6f, 0.4f), positionX(x), positionY(y), positionZ(z),
      upperArmX(0.0f), upperArmZ(0.0f), forearmX(0.0f) {
    // Skin color for arms
}

void Arm::render() {
    // Draw the entire arm as a connected hierarchy
    glPushMatrix();
    glTranslatef(positionX, positionY, positionZ);
    glRotatef(upperArmX, 1.0f, 0.0f, 0.0f);
    glRotatef(upperArmZ, 0.0f, 0.0f, 1.0f);

    // Draw upper arm
    glPushMatrix();
    glTranslatef(0.0f, -0.4f, 0.0f);
    glScalef(0.3f, 0.8f, 0.3f);
    drawColoredCube(colorR, colorG, colorB);  // Skin color for upper arms
    glPopMatrix();

    // Draw forearm (connected to upper arm)
    glTranslatef(0.0f, -0.8f, 0.0f);
    glRotatef(forearmX, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, -0.4f, 0.0f);
    glScalef(0.25f, 0.8f, 0.25f);
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
LeftArm::LeftArm() : Arm(-0.7f, 0.5f, 0.0f) {
}

RightArm::RightArm() : Arm(0.7f, 0.5f, 0.0f) {
}
