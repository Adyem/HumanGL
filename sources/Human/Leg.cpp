#include "../../includes/Human/Leg.hpp"

Leg::Leg(float x, float y, float z)
    : BodyPartRenderer(0.8f, 0.6f, 0.4f), positionX(x), positionY(y), positionZ(z),
      thighX(0.0f), lowerLegX(0.0f) {
    // Skin color for legs (will be overridden for thighs with pants color)
}

void Leg::render(MatrixStack& matrixStack) {
    // Draw the entire leg as a connected hierarchy
    matrixStack.pushMatrix();
    // Apply rotation before translating to hip position
    matrixStack.rotateX(thighX);
    matrixStack.translate(positionX, positionY, positionZ);

    // Debug marker to visualize the hip joint position
    matrixStack.pushMatrix();
    matrixStack.scale(0.05f, 0.05f, 0.05f);
    matrixStack.applyToOpenGL();
    drawColoredCube(1.0f, 0.0f, 0.0f); // bright red cube
    matrixStack.popMatrix();

    // Draw thigh (with pants color)
    matrixStack.pushMatrix();
    matrixStack.scale(0.3f, 0.8f, 0.3f);
    matrixStack.translate(0.0f, -0.4f, 0.0f);
    matrixStack.applyToOpenGL();
    drawColoredCube(0.1f, 0.2f, 0.6f);  // Dark blue pants color for thighs
    matrixStack.popMatrix();

    // Draw lower leg (connected to thigh)
    matrixStack.translate(0.0f, -0.8f, 0.0f);
    matrixStack.rotateX(lowerLegX);
    matrixStack.scale(0.25f, 0.8f, 0.25f);
    matrixStack.translate(0.0f, -0.4f, 0.0f);
    matrixStack.applyToOpenGL();
    drawColoredCube(colorR, colorG, colorB);  // Skin color for lower legs

    matrixStack.popMatrix();
}

void Leg::setThighRotation(float x) {
    thighX = x;
}

void Leg::setLowerLegRotation(float x) {
    lowerLegX = x;
}

void Leg::getThighRotation(float& x) const {
    x = thighX;
}

void Leg::getLowerLegRotation(float& x) const {
    x = lowerLegX;
}

LeftLeg::LeftLeg() : Leg(-0.3f, -0.75f, 0.0f) {
}

RightLeg::RightLeg() : Leg(0.3f, -0.75f, 0.0f) {
}
