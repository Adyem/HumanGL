#include "../../includes/Human/Head.hpp"

Head::Head() : BodyPartRenderer(HUMANGL_DEFAULT_SKIN_R, HUMANGL_DEFAULT_SKIN_G, HUMANGL_DEFAULT_SKIN_B), headRotationX(HUMANGL_OPENGL_AXIS_NONE), headRotationY(HUMANGL_OPENGL_AXIS_NONE) {
    // Skin color
}

void Head::render() {
    glPushMatrix();
    glTranslatef(HUMANGL_OPENGL_AXIS_NONE, HUMANGL_HEAD_Y_POSITION, HUMANGL_OPENGL_AXIS_NONE);
    glRotatef(headRotationX, HUMANGL_OPENGL_AXIS_X, HUMANGL_OPENGL_AXIS_NONE, HUMANGL_OPENGL_AXIS_NONE);
    glRotatef(headRotationY, HUMANGL_OPENGL_AXIS_NONE, HUMANGL_OPENGL_AXIS_Y, HUMANGL_OPENGL_AXIS_NONE);
    glScalef(HUMANGL_HEAD_SCALE * scaleX, HUMANGL_HEAD_SCALE * scaleY, HUMANGL_HEAD_SCALE * scaleZ);
    drawColoredCube(colorR, colorG, colorB);
    glPopMatrix();
}

void Head::setHeadRotation(float x, float y) {
    headRotationX = x;
    headRotationY = y;
}

void Head::getHeadRotation(float& x, float& y) const {
    x = headRotationX;
    y = headRotationY;
}
