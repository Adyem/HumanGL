#include "../../includes/Human/Leg.hpp"

Leg::Leg(float x, float y, float z)
    : BodyPartRenderer(HUMANGL_DEFAULT_SKIN_R, HUMANGL_DEFAULT_SKIN_G, HUMANGL_DEFAULT_SKIN_B), positionX(x), positionY(y), positionZ(z),
      thighX(HUMANGL_OPENGL_AXIS_NONE), lowerLegX(HUMANGL_OPENGL_AXIS_NONE),
      thighR(HUMANGL_PANTS_COLOR_R), thighG(HUMANGL_PANTS_COLOR_G), thighB(HUMANGL_PANTS_COLOR_B),
      lowerLegR(HUMANGL_DEFAULT_SKIN_R), lowerLegG(HUMANGL_DEFAULT_SKIN_G), lowerLegB(HUMANGL_DEFAULT_SKIN_B) {
    // Thighs use pants color (blue), lower legs use skin color
}

void Leg::render() {
    // Draw the entire leg as a connected hierarchy
    glPushMatrix();
    glTranslatef(positionX, positionY, positionZ);
    glRotatef(thighX, HUMANGL_OPENGL_AXIS_X, HUMANGL_OPENGL_AXIS_NONE, HUMANGL_OPENGL_AXIS_NONE);

    // Draw thigh (with individual thigh color)
    glPushMatrix();
    glTranslatef(HUMANGL_OPENGL_AXIS_NONE, HUMANGL_THIGH_Y_OFFSET, HUMANGL_OPENGL_AXIS_NONE);
    glScalef(HUMANGL_THIGH_SCALE_X * scaleX, HUMANGL_THIGH_SCALE_Y * scaleY, HUMANGL_THIGH_SCALE_Z * scaleZ);
    drawColoredCube(thighR, thighG, thighB);  // Individual thigh color
    glPopMatrix();

    // Draw lower leg (connected to thigh)
    glTranslatef(HUMANGL_OPENGL_AXIS_NONE, HUMANGL_LOWER_LEG_Y_OFFSET, HUMANGL_OPENGL_AXIS_NONE);
    glRotatef(lowerLegX, HUMANGL_OPENGL_AXIS_X, HUMANGL_OPENGL_AXIS_NONE, HUMANGL_OPENGL_AXIS_NONE);
    glTranslatef(HUMANGL_OPENGL_AXIS_NONE, HUMANGL_LOWER_LEG_Y_POSITION, HUMANGL_OPENGL_AXIS_NONE);
    glScalef(HUMANGL_LOWER_LEG_SCALE_X * scaleX, HUMANGL_LOWER_LEG_SCALE_Y * scaleY, HUMANGL_LOWER_LEG_SCALE_Z * scaleZ);
    drawColoredCube(lowerLegR, lowerLegG, lowerLegB);  // Individual lower leg color

    glPopMatrix();
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


