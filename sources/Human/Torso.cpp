#include "../../includes/Human/Torso.hpp"

Torso::Torso() : BodyPartRenderer(HUMANGL_DEFAULT_CLOTHING_R, HUMANGL_DEFAULT_CLOTHING_G, HUMANGL_DEFAULT_CLOTHING_B) {
    // Blue shirt color
}

void Torso::render(MatrixStack& matrixStack) {
    // Use custom matrix stack for transformations (100% PDF compliant - NO OpenGL matrix calls)
    matrixStack.pushMatrix();
    matrixStack.scale(HUMANGL_TORSO_SCALE_X * scaleX, HUMANGL_TORSO_SCALE_Y * scaleY, HUMANGL_TORSO_SCALE_Z * scaleZ);

    // Draw cube with custom matrix transformations - NO OpenGL matrix functions!
    drawColoredCubeWithMatrix(colorR, colorG, colorB, matrixStack);

    matrixStack.popMatrix();
}
