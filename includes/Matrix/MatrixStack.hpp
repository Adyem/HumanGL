#pragma once

#include "../humangl.hpp"
#include "Matrix4.hpp"

class MatrixStack {
private:
    std::vector<Matrix4> stack;
    Matrix4 current;

public:
    // Constructor - initializes with identity matrix
    MatrixStack();

    // Load identity matrix
    void loadIdentity();

    // Stack operations
    void pushMatrix();
    void popMatrix();

    // Transformation methods (applied to current matrix)
    void translate(float x, float y, float z);
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);
    void scale(float x, float y, float z);

    // Apply current matrix to OpenGL
    void applyToOpenGL();
};
