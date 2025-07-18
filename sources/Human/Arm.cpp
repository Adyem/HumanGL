#include "../../includes/Human/Arm.hpp"

Arm::Arm(float x, float y, float z)
    : BodyPartRenderer(0.8f, 0.6f, 0.4f), positionX(x), positionY(y), positionZ(z),
      upperArmX(0.0f), upperArmZ(0.0f), forearmX(0.0f) {
    // Skin color for arms
}

void Arm::render(MatrixStack& matrixStack) {
    // Draw the entire arm as a connected hierarchy
    matrixStack.pushMatrix();

    matrixStack.translate(positionX, positionY, positionZ);

    // Debug marker to visualize the shoulder joint position
    matrixStack.pushMatrix();
    matrixStack.scale(0.05f, 0.05f, 0.05f);
    matrixStack.applyToOpenGL();
    drawColoredCube(1.0f, 0.0f, 0.0f); // bright red cube
    matrixStack.popMatrix();

    matrixStack.rotateX(upperArmX);
    matrixStack.rotateZ(upperArmZ);
    matrixStack.translate(positionX, positionY, positionZ);

    // Debug marker to visualize the shoulder joint position
    matrixStack.pushMatrix();
    matrixStack.scale(0.05f, 0.05f, 0.05f);
    matrixStack.applyToOpenGL();
    drawColoredCube(1.0f, 0.0f, 0.0f); // bright red cube
    matrixStack.popMatrix();

    // Draw upper arm
    matrixStack.pushMatrix();
    matrixStack.scale(0.3f, 0.8f, 0.3f);
    matrixStack.translate(0.0f, -0.4f, 0.0f);
    matrixStack.applyToOpenGL();
    drawColoredCube(colorR, colorG, colorB);  // Skin color for upper arms
    matrixStack.popMatrix();

    // Draw forearm (connected to upper arm)
    matrixStack.translate(0.0f, -0.8f, 0.0f);
    matrixStack.rotateX(forearmX);
    matrixStack.scale(0.25f, 0.8f, 0.25f);
    matrixStack.translate(0.0f, -0.4f, 0.0f);
    matrixStack.applyToOpenGL();
    drawColoredCube(colorR, colorG, colorB);  // Skin color for forearms

    matrixStack.popMatrix();
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

LeftArm::LeftArm() : Arm(-0.6f, 1.2f, 0.0f) {
}

RightArm::RightArm() : Arm(0.6f, 1.2f, 0.0f) {
}
