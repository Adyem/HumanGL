#include "../../includes/Human/Leg.hpp"

Leg::Leg(float x, float y, float z)
    : BodyPartRenderer(HUMANGL_DEFAULT_SKIN_R, HUMANGL_DEFAULT_SKIN_G, HUMANGL_DEFAULT_SKIN_B), positionX(x), positionY(y), positionZ(z),
      thighX(HUMANGL_OPENGL_AXIS_NONE), lowerLegX(HUMANGL_OPENGL_AXIS_NONE),
      thighR(HUMANGL_PANTS_COLOR_R), thighG(HUMANGL_PANTS_COLOR_G), thighB(HUMANGL_PANTS_COLOR_B),
      lowerLegR(HUMANGL_DEFAULT_SKIN_R), lowerLegG(HUMANGL_DEFAULT_SKIN_G), lowerLegB(HUMANGL_DEFAULT_SKIN_B) {
    // Thighs use pants color (blue), lower legs use skin color
}

void Leg::render(MatrixStack& matrixStack) {
    // Use custom matrix stack for transformations (100% PDF compliant - NO OpenGL matrix calls)
    matrixStack.pushMatrix();
    matrixStack.translate(positionX, positionY, positionZ);
    matrixStack.rotateX(thighX);

    // Draw thigh (with individual thigh color)
    matrixStack.pushMatrix();
    matrixStack.translate(HUMANGL_OPENGL_AXIS_NONE, HUMANGL_THIGH_Y_OFFSET, HUMANGL_OPENGL_AXIS_NONE);
    matrixStack.scale(HUMANGL_THIGH_SCALE_X * scaleX, HUMANGL_THIGH_SCALE_Y * scaleY, HUMANGL_THIGH_SCALE_Z * scaleZ);

    // Draw cube with custom matrix transformations - NO OpenGL matrix functions!
    drawColoredCubeWithMatrix(thighR, thighG, thighB, matrixStack);  // Individual thigh color

    matrixStack.popMatrix();

    // Draw lower leg (connected to thigh)
    matrixStack.translate(HUMANGL_OPENGL_AXIS_NONE, HUMANGL_LOWER_LEG_Y_OFFSET, HUMANGL_OPENGL_AXIS_NONE);
    matrixStack.rotateX(lowerLegX);
    matrixStack.translate(HUMANGL_OPENGL_AXIS_NONE, HUMANGL_LOWER_LEG_Y_POSITION, HUMANGL_OPENGL_AXIS_NONE);
    matrixStack.scale(HUMANGL_LOWER_LEG_SCALE_X * scaleX, HUMANGL_LOWER_LEG_SCALE_Y * scaleY, HUMANGL_LOWER_LEG_SCALE_Z * scaleZ);

    // Draw cube with custom matrix transformations - NO OpenGL matrix functions!
    drawColoredCubeWithMatrix(lowerLegR, lowerLegG, lowerLegB, matrixStack);  // Individual lower leg color

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

void Leg::setThighColor(float r, float g, float b) {
    thighR = r;
    thighG = g;
    thighB = b;
}

void Leg::setLowerLegColor(float r, float g, float b) {
    lowerLegR = r;
    lowerLegG = g;
    lowerLegB = b;
}


