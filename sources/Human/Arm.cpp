#include "../../includes/Human/Arm.hpp"

Arm::Arm(float x, float y, float z)
    : BodyPartRenderer(HUMANGL_DEFAULT_SKIN_R, HUMANGL_DEFAULT_SKIN_G, HUMANGL_DEFAULT_SKIN_B), positionX(x), positionY(y), positionZ(z),
      upperArmX(HUMANGL_OPENGL_AXIS_NONE), upperArmZ(HUMANGL_OPENGL_AXIS_NONE), forearmX(HUMANGL_OPENGL_AXIS_NONE),
      upperArmR(HUMANGL_DEFAULT_CLOTHING_R), upperArmG(HUMANGL_DEFAULT_CLOTHING_G), upperArmB(HUMANGL_DEFAULT_CLOTHING_B),
      forearmR(HUMANGL_DEFAULT_SKIN_R), forearmG(HUMANGL_DEFAULT_SKIN_G), forearmB(HUMANGL_DEFAULT_SKIN_B) {
    // Upper arms use clothing color (blue), forearms use skin color
}

void Arm::render(MatrixStack& matrixStack) {
    // Use custom matrix stack for transformations (100% PDF compliant - NO OpenGL matrix calls)
    matrixStack.pushMatrix();
    matrixStack.translate(positionX, positionY, positionZ);
    matrixStack.rotateX(upperArmX);
    matrixStack.rotateZ(upperArmZ);

    // Draw upper arm
    matrixStack.pushMatrix();
    matrixStack.translate(HUMANGL_OPENGL_AXIS_NONE, HUMANGL_UPPER_ARM_Y_OFFSET, HUMANGL_OPENGL_AXIS_NONE);
    matrixStack.scale(HUMANGL_UPPER_ARM_SCALE_X * scaleX, HUMANGL_UPPER_ARM_SCALE_Y * scaleY, HUMANGL_UPPER_ARM_SCALE_Z * scaleZ);

    // Draw cube with custom matrix transformations - NO OpenGL matrix functions!
    drawColoredCubeWithMatrix(upperArmR, upperArmG, upperArmB, matrixStack);  // Individual upper arm color

    matrixStack.popMatrix();

    // Draw forearm (connected to upper arm)
    matrixStack.translate(HUMANGL_OPENGL_AXIS_NONE, HUMANGL_FOREARM_Y_OFFSET, HUMANGL_OPENGL_AXIS_NONE);
    matrixStack.rotateX(forearmX);
    matrixStack.translate(HUMANGL_OPENGL_AXIS_NONE, HUMANGL_FOREARM_Y_POSITION, HUMANGL_OPENGL_AXIS_NONE);
    matrixStack.scale(HUMANGL_FOREARM_SCALE_X * scaleX, HUMANGL_FOREARM_SCALE_Y * scaleY, HUMANGL_FOREARM_SCALE_Z * scaleZ);

    // Draw cube with custom matrix transformations - NO OpenGL matrix functions!
    drawColoredCubeWithMatrix(forearmR, forearmG, forearmB, matrixStack);  // Individual forearm color

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

void Arm::setUpperArmColor(float r, float g, float b) {
    upperArmR = r;
    upperArmG = g;
    upperArmB = b;
}

void Arm::setForearmColor(float r, float g, float b) {
    forearmR = r;
    forearmG = g;
    forearmB = b;
}


