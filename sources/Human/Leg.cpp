#include "../../includes/Human/Leg.hpp"

Leg::Leg(float x, float y, float z)
    : BodyPartRenderer(0.8f, 0.6f, 0.4f), positionX(x), positionY(y), positionZ(z),
      thighX(0.0f), lowerLegX(0.0f) {
    // Skin color for legs (will be overridden for thighs with pants color)
}

void Leg::render() {
    // Draw the entire leg as a connected hierarchy
    glPushMatrix();
    glTranslatef(positionX, positionY, positionZ);
    glRotatef(thighX, 1.0f, 0.0f, 0.0f);

    // Draw thigh (with pants color)
    glPushMatrix();
    glTranslatef(0.0f, -0.4f, 0.0f);
    glScalef(0.3f, 0.8f, 0.3f);
    drawColoredCube(0.1f, 0.2f, 0.6f);  // Dark blue pants color for thighs
    glPopMatrix();

    // Draw lower leg (connected to thigh)
    glTranslatef(0.0f, -0.8f, 0.0f);
    glRotatef(lowerLegX, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, -0.4f, 0.0f);
    glScalef(0.25f, 0.8f, 0.25f);
    drawColoredCube(colorR, colorG, colorB);  // Skin color for lower legs

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

LeftLeg::LeftLeg() : Leg(-0.3f, -0.75f, 0.0f) {
}

RightLeg::RightLeg() : Leg(0.3f, -0.75f, 0.0f) {
}
