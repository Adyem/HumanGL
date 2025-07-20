#include "../../includes/Human/Head.hpp"


Torso::Torso() : BodyPartRenderer(0.2f, 0.4f, 0.8f) {
    // Blue shirt color
}

void Torso::render(MatrixStack& matrixStack) {
    matrixStack.pushMatrix();
    matrixStack.scale(1.0f, 1.5f, 0.5f);
    matrixStack.applyToOpenGL();
    drawColoredCube(colorR, colorG, colorB);
    matrixStack.popMatrix();
}

Neck::Neck() : BodyPartRenderer(0.8f, 0.6f, 0.4f) {
    // Skin color
}

void Neck::render(MatrixStack& matrixStack) {
    matrixStack.pushMatrix();
    // Move the neck to its position on top of the torso first so any scaling
    // does not alter the translation distance.
    matrixStack.translate(0.0f, 0.9f, 0.0f);
    matrixStack.scale(0.3f, 0.3f, 0.3f);
    matrixStack.applyToOpenGL();
    drawColoredCube(colorR, colorG, colorB);
    matrixStack.popMatrix();
}

Head::Head() : BodyPartRenderer(0.8f, 0.6f, 0.4f), headRotationX(0.0f), headRotationY(0.0f) {
    // Skin color
}

void Head::render(MatrixStack& matrixStack) {
    matrixStack.pushMatrix();
    // Position the head relative to the neck before applying rotations so that
    // it pivots around the neck joint rather than the world origin.
    matrixStack.translate(0.0f, 1.4f, 0.0f);
    matrixStack.rotateX(headRotationX);
    matrixStack.rotateY(headRotationY);
    matrixStack.scale(0.6f, 0.6f, 0.6f);
    matrixStack.applyToOpenGL();
    drawColoredCube(colorR, colorG, colorB);
    matrixStack.popMatrix();
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

void Eyes::render(MatrixStack& matrixStack) {
    matrixStack.pushMatrix();
    // Translate to the head position before applying rotation so the eyes
    // follow the head movement correctly.
    matrixStack.translate(0.0f, 1.4f, 0.0f);
    matrixStack.rotateX(headRotationX);
    matrixStack.rotateY(headRotationY);

    // Left eye
    matrixStack.pushMatrix();
    matrixStack.scale(0.1f, 0.1f, 0.1f);
    matrixStack.translate(-0.15f, 0.1f, 0.31f);
    matrixStack.applyToOpenGL();
    drawColoredCube(colorR, colorG, colorB);
    matrixStack.popMatrix();

    // Right eye
    matrixStack.pushMatrix();
    matrixStack.scale(0.1f, 0.1f, 0.1f);
    matrixStack.translate(0.15f, 0.1f, 0.31f);
    matrixStack.applyToOpenGL();
    drawColoredCube(colorR, colorG, colorB);
    matrixStack.popMatrix();

    matrixStack.popMatrix();
}

void Eyes::setHeadRotation(float x, float y) {
    headRotationX = x;
    headRotationY = y;
}
