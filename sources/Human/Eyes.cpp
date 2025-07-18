#include "../../includes/Human/Eyes.hpp"

Eyes::Eyes() : BodyPartRenderer(HUMANGL_OPENGL_AXIS_NONE, HUMANGL_OPENGL_AXIS_NONE, HUMANGL_OPENGL_AXIS_NONE), headRotationX(HUMANGL_OPENGL_AXIS_NONE), headRotationY(HUMANGL_OPENGL_AXIS_NONE) {
    // Black color for eyes
}

void Eyes::render() {
    glPushMatrix();
    glTranslatef(HUMANGL_OPENGL_AXIS_NONE, HUMANGL_HEAD_Y_POSITION, HUMANGL_OPENGL_AXIS_NONE);
    glRotatef(headRotationX, HUMANGL_OPENGL_AXIS_X, HUMANGL_OPENGL_AXIS_NONE, HUMANGL_OPENGL_AXIS_NONE);
    glRotatef(headRotationY, HUMANGL_OPENGL_AXIS_NONE, HUMANGL_OPENGL_AXIS_Y, HUMANGL_OPENGL_AXIS_NONE);

    // Left eye
    glPushMatrix();
    glTranslatef(HUMANGL_LEFT_EYE_X_OFFSET, HUMANGL_EYE_Y_OFFSET, HUMANGL_EYE_Z_OFFSET);
    glScalef(HUMANGL_EYE_SCALE * scaleX, HUMANGL_EYE_SCALE * scaleY, HUMANGL_EYE_SCALE * scaleZ);
    drawColoredCube(colorR, colorG, colorB);
    glPopMatrix();

    // Right eye
    glPushMatrix();
    glTranslatef(HUMANGL_RIGHT_EYE_X_OFFSET, HUMANGL_EYE_Y_OFFSET, HUMANGL_EYE_Z_OFFSET);
    glScalef(HUMANGL_EYE_SCALE * scaleX, HUMANGL_EYE_SCALE * scaleY, HUMANGL_EYE_SCALE * scaleZ);
    drawColoredCube(colorR, colorG, colorB);
    glPopMatrix();

    glPopMatrix();
}

void Eyes::setHeadRotation(float x, float y) {
    headRotationX = x;
    headRotationY = y;
}
