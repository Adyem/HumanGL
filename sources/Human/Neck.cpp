#include "../../includes/Human/Neck.hpp"

Neck::Neck() : BodyPartRenderer(HUMANGL_DEFAULT_SKIN_R, HUMANGL_DEFAULT_SKIN_G, HUMANGL_DEFAULT_SKIN_B) {
    // Skin color
}

void Neck::render() {
    glPushMatrix();
    glTranslatef(HUMANGL_OPENGL_AXIS_NONE, HUMANGL_NECK_Y_POSITION, HUMANGL_OPENGL_AXIS_NONE);
    glScalef(HUMANGL_NECK_SCALE * scaleX, HUMANGL_NECK_SCALE * scaleY, HUMANGL_NECK_SCALE * scaleZ);
    drawColoredCube(colorR, colorG, colorB);
    glPopMatrix();
}
