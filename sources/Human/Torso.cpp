#include "../../includes/Human/Torso.hpp"

Torso::Torso() : BodyPartRenderer(HUMANGL_DEFAULT_CLOTHING_R, HUMANGL_DEFAULT_CLOTHING_G, HUMANGL_DEFAULT_CLOTHING_B) {
    // Blue shirt color
}

void Torso::render() {
    glPushMatrix();
    glScalef(HUMANGL_TORSO_SCALE_X * scaleX, HUMANGL_TORSO_SCALE_Y * scaleY, HUMANGL_TORSO_SCALE_Z * scaleZ);
    drawColoredCube(colorR, colorG, colorB);
    glPopMatrix();
}
