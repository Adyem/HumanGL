#include "../../includes/Human/Neck.hpp"

Neck::Neck() : BodyPartRenderer(HUMANGL_DEFAULT_SKIN_R, HUMANGL_DEFAULT_SKIN_G, HUMANGL_DEFAULT_SKIN_B) {
    // Skin color
}

void Neck::render(MatrixStack& matrixStack) {
    // Use custom matrix stack for transformations (100% PDF compliant - NO OpenGL matrix calls)
    matrixStack.pushMatrix();
    matrixStack.translate(HUMANGL_OPENGL_AXIS_NONE, HUMANGL_NECK_Y_POSITION, HUMANGL_OPENGL_AXIS_NONE);
    matrixStack.scale(HUMANGL_NECK_SCALE * scaleX, HUMANGL_NECK_SCALE * scaleY, HUMANGL_NECK_SCALE * scaleZ);

    // Draw cube with custom matrix transformations - NO OpenGL matrix functions!
    drawColoredCubeWithMatrix(colorR, colorG, colorB, matrixStack);

    matrixStack.popMatrix();
}
