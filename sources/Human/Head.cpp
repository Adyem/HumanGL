#include "../../includes/Human/Head.hpp"


Torso::Torso() : BodyPartRenderer(HUMANGL_DEFAULT_CLOTHING_R, HUMANGL_DEFAULT_CLOTHING_G, HUMANGL_DEFAULT_CLOTHING_B) {
    // Blue shirt color
}

void Torso::render() {
    glPushMatrix();
    glScalef(HUMANGL_TORSO_SCALE_X, HUMANGL_TORSO_SCALE_Y, HUMANGL_TORSO_SCALE_Z);
    drawColoredCube(colorR, colorG, colorB);
    glPopMatrix();
}

Neck::Neck() : BodyPartRenderer(HUMANGL_DEFAULT_SKIN_R, HUMANGL_DEFAULT_SKIN_G, HUMANGL_DEFAULT_SKIN_B) {
    // Skin color
}

void Neck::render() {
    glPushMatrix();
    glTranslatef(HUMANGL_OPENGL_AXIS_NONE, HUMANGL_NECK_Y_POSITION, HUMANGL_OPENGL_AXIS_NONE);
    glScalef(HUMANGL_NECK_SCALE, HUMANGL_NECK_SCALE, HUMANGL_NECK_SCALE);
    drawColoredCube(colorR, colorG, colorB);
    glPopMatrix();
}

Head::Head() : BodyPartRenderer(HUMANGL_DEFAULT_SKIN_R, HUMANGL_DEFAULT_SKIN_G, HUMANGL_DEFAULT_SKIN_B), headRotationX(HUMANGL_OPENGL_AXIS_NONE), headRotationY(HUMANGL_OPENGL_AXIS_NONE) {
    // Skin color
}

void Head::render() {
    glPushMatrix();
    glTranslatef(HUMANGL_OPENGL_AXIS_NONE, HUMANGL_HEAD_Y_POSITION, HUMANGL_OPENGL_AXIS_NONE);
    glRotatef(headRotationX, HUMANGL_OPENGL_AXIS_X, HUMANGL_OPENGL_AXIS_NONE, HUMANGL_OPENGL_AXIS_NONE);
    glRotatef(headRotationY, HUMANGL_OPENGL_AXIS_NONE, HUMANGL_OPENGL_AXIS_Y, HUMANGL_OPENGL_AXIS_NONE);
    glScalef(HUMANGL_HEAD_SCALE, HUMANGL_HEAD_SCALE, HUMANGL_HEAD_SCALE);
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
    glScalef(HUMANGL_EYE_SCALE, HUMANGL_EYE_SCALE, HUMANGL_EYE_SCALE);
    drawColoredCube(colorR, colorG, colorB);
    glPopMatrix();

    // Right eye
    glPushMatrix();
    glTranslatef(HUMANGL_RIGHT_EYE_X_OFFSET, HUMANGL_EYE_Y_OFFSET, HUMANGL_EYE_Z_OFFSET);
    glScalef(HUMANGL_EYE_SCALE, HUMANGL_EYE_SCALE, HUMANGL_EYE_SCALE);
    drawColoredCube(colorR, colorG, colorB);
    glPopMatrix();

    glPopMatrix();
}

void Eyes::setHeadRotation(float x, float y) {
    headRotationX = x;
    headRotationY = y;
}
