#include "../../includes/Human/Shoulder.hpp"

Shoulder::Shoulder(float x, float y, float z)
    : BodyPartRenderer(HUMANGL_DEFAULT_CLOTHING_R, HUMANGL_DEFAULT_CLOTHING_G, HUMANGL_DEFAULT_CLOTHING_B), positionX(x), positionY(y), positionZ(z) {
    // Blue shirt color for shoulders
}

void Shoulder::render() {
    glPushMatrix();
    glTranslatef(positionX, positionY, positionZ);
    glScalef(HUMANGL_SHOULDER_SCALE * scaleX, HUMANGL_SHOULDER_SCALE * scaleY, HUMANGL_SHOULDER_SCALE * scaleZ);
    drawColoredCube(colorR, colorG, colorB);
    glPopMatrix();
}

LeftShoulder::LeftShoulder() : Shoulder(HUMANGL_LEFT_ARM_X_POSITION, HUMANGL_ARM_Y_POSITION, HUMANGL_ARM_Z_POSITION) {
}

RightShoulder::RightShoulder() : Shoulder(HUMANGL_RIGHT_ARM_X_POSITION, HUMANGL_ARM_Y_POSITION, HUMANGL_ARM_Z_POSITION) {
}
