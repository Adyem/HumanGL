#include "../../includes/Human/Shoulder.hpp"

Shoulder::Shoulder(float x, float y, float z)
    : BodyPartRenderer(HUMANGL_DEFAULT_CLOTHING_R, HUMANGL_DEFAULT_CLOTHING_G, HUMANGL_DEFAULT_CLOTHING_B), positionX(x), positionY(y), positionZ(z) {
    // Blue shirt color for shoulders
}

void Shoulder::render(MatrixStack& matrixStack) {
    // Use custom matrix stack for transformations (100% PDF compliant - NO OpenGL matrix calls)
    matrixStack.pushMatrix();
    matrixStack.translate(positionX, positionY, positionZ);
    matrixStack.scale(HUMANGL_SHOULDER_SCALE * scaleX, HUMANGL_SHOULDER_SCALE * scaleY, HUMANGL_SHOULDER_SCALE * scaleZ);

    // Draw cube with custom matrix transformations - NO OpenGL matrix functions!
    drawColoredCubeWithMatrix(colorR, colorG, colorB, matrixStack);

    matrixStack.popMatrix();
}


