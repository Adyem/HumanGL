#include "../../includes/Human/Shoulder.hpp"

Shoulder::Shoulder(float x, float y, float z)
    : BodyPartRenderer(0.2f, 0.4f, 0.8f), positionX(x), positionY(y), positionZ(z) {
    // Blue shirt color for shoulders
}

void Shoulder::render(MatrixStack& matrixStack) {
    matrixStack.pushMatrix();
    matrixStack.scale(0.3f, 0.3f, 0.3f);
    matrixStack.translate(positionX, positionY, positionZ);
    matrixStack.applyToOpenGL();
    drawColoredCube(colorR, colorG, colorB);
    matrixStack.popMatrix();
}

LeftShoulder::LeftShoulder() : Shoulder(-0.65f, 0.75f, 0.0f) {
}

RightShoulder::RightShoulder() : Shoulder(0.65f, 0.75f, 0.0f) {
}
