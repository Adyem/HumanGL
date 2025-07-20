#include "../../includes/Matrix/MatrixStack.hpp"
#include <iostream>

MatrixStack::MatrixStack() {
    current.loadIdentity();
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
    } else {
        std::cerr << "Warning: MatrixStack::popMatrix() called on empty stack!" << std::endl;
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

void MatrixStack::multiply(const Matrix4& matrix) {
    current *= matrix;
}

void MatrixStack::applyToOpenGL() {
    glLoadIdentity();
    current.applyToOpenGL();
}

void MatrixStack::loadMatrix(const Matrix4& matrix) {
    current = matrix;
}

void MatrixStack::multMatrix(const Matrix4& matrix) {
    current *= matrix;
}

void MatrixStack::print() const {
    std::cout << "MatrixStack (size: " << stack.size() << "):" << std::endl;
    std::cout << "Current matrix:" << std::endl;
    current.print();
    
    if (!stack.empty()) {
        std::cout << "Stack contents:" << std::endl;
        for (size_t i = 0; i < stack.size(); i++) {
            std::cout << "Stack[" << i << "]:" << std::endl;
            stack[i].print();
        }
    }
}

void MatrixStack::reset() {
    stack.clear();
    current.loadIdentity();
}
