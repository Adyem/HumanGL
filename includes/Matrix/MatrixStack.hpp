#pragma once

#include "../humangl.hpp"
#include "Matrix4.hpp"
#include <vector>

class MatrixStack {
private:
    std::vector<Matrix4> stack;
    Matrix4 current;

public:
    // Constructor - initializes with identity matrix
    MatrixStack();
    
    // Destructor
    ~MatrixStack() = default;

    // Load identity matrix
    void loadIdentity();

    // Stack operations (replaces glPushMatrix/glPopMatrix)
    void pushMatrix();
    void popMatrix();

    // Transformation methods (applied to current matrix)
    void translate(float x, float y, float z);
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);
    void scale(float x, float y, float z);
    
    // Direct matrix multiplication
    void multiply(const Matrix4& matrix);

    // Get current matrix
    const Matrix4& getCurrentMatrix() const { return current; }
    Matrix4& getCurrentMatrix() { return current; }
    
    // Get raw matrix data (for OpenGL)
    const float* getCurrentMatrixData() const { return current.getData(); }

    // Apply current matrix to OpenGL (for compatibility with existing code)
    void applyToOpenGL();
    
    // Replace OpenGL matrix calls
    void loadMatrix(const Matrix4& matrix);
    void multMatrix(const Matrix4& matrix);
    
    // Stack info
    size_t getStackSize() const { return stack.size(); }
    bool isEmpty() const { return stack.empty(); }
    
    // Utility methods
    void print() const;  // For debugging
    void reset();        // Clear stack and load identity
};
