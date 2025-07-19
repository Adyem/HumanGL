#include "../../includes/Human/Head.hpp"

Head::Head() : BodyPartRenderer(HUMANGL_DEFAULT_SKIN_R, HUMANGL_DEFAULT_SKIN_G, HUMANGL_DEFAULT_SKIN_B), headRotationX(HUMANGL_OPENGL_AXIS_NONE), headRotationY(HUMANGL_OPENGL_AXIS_NONE) {
    // Skin color
}

void Head::render(MatrixStack& matrixStack) {
    // Use custom matrix stack for transformations (100% PDF compliant - NO OpenGL matrix calls)
    matrixStack.pushMatrix();
    matrixStack.translate(HUMANGL_OPENGL_AXIS_NONE, HUMANGL_HEAD_Y_POSITION, HUMANGL_OPENGL_AXIS_NONE);
    matrixStack.rotateX(headRotationX);
    matrixStack.rotateY(headRotationY);
    matrixStack.scale(HUMANGL_HEAD_SCALE * scaleX, HUMANGL_HEAD_SCALE * scaleY, HUMANGL_HEAD_SCALE * scaleZ);

    // Draw cube with custom matrix transformations - NO OpenGL matrix functions!
    drawColoredCubeWithMatrix(colorR, colorG, colorB, matrixStack);

    matrixStack.popMatrix();
}

void Head::setHeadRotation(float x, float y) {
    headRotationX = x;
    headRotationY = y;
}

void Head::getHeadRotation(float& x, float& y) const {
    x = headRotationX;
    y = headRotationY;
}
