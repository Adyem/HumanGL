#include "../../includes/Matrix/MatrixStack.hpp"

MatrixStack::MatrixStack() {
    current.loadIdentity();
    viewMatrix.loadIdentity();
}

void MatrixStack::loadIdentity() {
    current.loadIdentity();
}

void MatrixStack::pushMatrix() {
    stack.push_back(current);
}

void MatrixStack::popMatrix() {
    if (!stack.empty()) {
        current = stack.back();
        stack.pop_back();
    }
}

void MatrixStack::translate(float x, float y, float z) {
    current.translate(x, y, z);
}

void MatrixStack::rotateX(float angle) {
    current.rotateX(angle);
}

void MatrixStack::rotateY(float angle) {
    current.rotateY(angle);
}

void MatrixStack::rotateZ(float angle) {
    current.rotateZ(angle);
}

void MatrixStack::scale(float x, float y, float z) {
    current.scale(x, y, z);
}

void MatrixStack::applyToOpenGL() {
    Matrix4 combined = viewMatrix * current;
    glLoadMatrixf(combined.data());
}

void MatrixStack::setViewMatrix(const Matrix4& view) {
    viewMatrix = view;
}
