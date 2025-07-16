#include "../../includes/Human/Shoulder.hpp"

Shoulder::Shoulder(float x, float y, float z)
    : BodyPartRenderer(0.2f, 0.4f, 0.8f), positionX(x), positionY(y), positionZ(z) {
    // Blue shirt color for shoulders
}

void Shoulder::render() {
    glPushMatrix();
    glTranslatef(positionX, positionY, positionZ);
    glScalef(0.3f, 0.3f, 0.3f);
    drawColoredCube(colorR, colorG, colorB);
    glPopMatrix();
}

LeftShoulder::LeftShoulder() : Shoulder(-0.7f, 0.5f, 0.0f) {
}

RightShoulder::RightShoulder() : Shoulder(0.7f, 0.5f, 0.0f) {
}
