#include "../../includes/Human/Eyes.hpp"

Eyes::Eyes() : BodyPartRenderer(HUMANGL_OPENGL_AXIS_NONE, HUMANGL_OPENGL_AXIS_NONE, HUMANGL_OPENGL_AXIS_NONE), headRotationX(HUMANGL_OPENGL_AXIS_NONE), headRotationY(HUMANGL_OPENGL_AXIS_NONE) {
    // Black color for eyes
}

void Eyes::render(MatrixStack& matrixStack) {
    // Use custom matrix stack for transformations (100% PDF compliant - NO OpenGL matrix calls)
    matrixStack.pushMatrix();
    matrixStack.translate(HUMANGL_OPENGL_AXIS_NONE, HUMANGL_HEAD_Y_POSITION, HUMANGL_OPENGL_AXIS_NONE);
    matrixStack.rotateX(headRotationX);
    matrixStack.rotateY(headRotationY);

    // Left eye
    matrixStack.pushMatrix();
    matrixStack.translate(HUMANGL_LEFT_EYE_X_OFFSET, HUMANGL_EYE_Y_OFFSET, HUMANGL_EYE_Z_OFFSET);
    matrixStack.scale(HUMANGL_EYE_SCALE * scaleX, HUMANGL_EYE_SCALE * scaleY, HUMANGL_EYE_SCALE * scaleZ);

    // Draw cube with custom matrix transformations - NO OpenGL matrix functions!
    drawColoredCubeWithMatrix(colorR, colorG, colorB, matrixStack);

    matrixStack.popMatrix();

    // Right eye
    matrixStack.pushMatrix();
    matrixStack.translate(HUMANGL_RIGHT_EYE_X_OFFSET, HUMANGL_EYE_Y_OFFSET, HUMANGL_EYE_Z_OFFSET);
    matrixStack.scale(HUMANGL_EYE_SCALE * scaleX, HUMANGL_EYE_SCALE * scaleY, HUMANGL_EYE_SCALE * scaleZ);

    // Draw cube with custom matrix transformations - NO OpenGL matrix functions!
    drawColoredCubeWithMatrix(colorR, colorG, colorB, matrixStack);

    matrixStack.popMatrix();

    matrixStack.popMatrix();
}

void Eyes::setHeadRotation(float x, float y) {
    headRotationX = x;
    headRotationY = y;
}
