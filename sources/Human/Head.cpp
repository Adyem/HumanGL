#include "../../includes/Human/Head.hpp"


Torso::Torso() : BodyPartRenderer(0.2f, 0.4f, 0.8f) {
    // Blue shirt color
}

void Torso::render() {
    glPushMatrix();
    glScalef(1.0f, 1.5f, 0.5f);
    drawColoredCube(colorR, colorG, colorB);
    glPopMatrix();
}

Neck::Neck() : BodyPartRenderer(0.8f, 0.6f, 0.4f) {
    // Skin color
}

void Neck::render() {
    glPushMatrix();
    glTranslatef(0.0f, 0.9f, 0.0f);
    glScalef(0.3f, 0.3f, 0.3f);
    drawColoredCube(colorR, colorG, colorB);
    glPopMatrix();
}

Head::Head() : BodyPartRenderer(0.8f, 0.6f, 0.4f), headRotationX(0.0f), headRotationY(0.0f) {
    // Skin color
}

void Head::render() {
    glPushMatrix();
    glTranslatef(0.0f, 1.4f, 0.0f);
    glRotatef(headRotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(headRotationY, 0.0f, 1.0f, 0.0f);
    glScalef(0.6f, 0.6f, 0.6f);
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

Eyes::Eyes() : BodyPartRenderer(0.0f, 0.0f, 0.0f), headRotationX(0.0f), headRotationY(0.0f) {
    // Black color for eyes
}

void Eyes::render() {
    glPushMatrix();
    glTranslatef(0.0f, 1.4f, 0.0f);
    glRotatef(headRotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(headRotationY, 0.0f, 1.0f, 0.0f);

    // Left eye
    glPushMatrix();
    glTranslatef(-0.15f, 0.1f, 0.31f);
    glScalef(0.1f, 0.1f, 0.1f);
    drawColoredCube(colorR, colorG, colorB);
    glPopMatrix();

    // Right eye
    glPushMatrix();
    glTranslatef(0.15f, 0.1f, 0.31f);
    glScalef(0.1f, 0.1f, 0.1f);
    drawColoredCube(colorR, colorG, colorB);
    glPopMatrix();

    glPopMatrix();
}

void Eyes::setHeadRotation(float x, float y) {
    headRotationX = x;
    headRotationY = y;
}
