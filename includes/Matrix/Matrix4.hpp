#pragma once

#include "../humangl.hpp"

class Matrix4 {
private:
    float m[16];  // Column-major order (OpenGL standard)

public:
    // Constructor - initializes to identity matrix
    Matrix4();
    
    // Copy constructor
    Matrix4(const Matrix4& other);
    
    // Assignment operator
    Matrix4& operator=(const Matrix4& other);

    // Load identity matrix
    void loadIdentity();

    // Transformation methods
    void translate(float x, float y, float z);
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);
    void scale(float x, float y, float z);

    // Matrix multiplication operator
    Matrix4 operator*(const Matrix4& other) const;
    
    // Matrix multiplication assignment
    Matrix4& operator*=(const Matrix4& other);

    // Get raw matrix data (for OpenGL)
    const float* getData() const { return m; }
    float* getData() { return m; }
    
    // Element access
    float& operator()(int row, int col);
    const float& operator()(int row, int col) const;
    
    // Apply matrix to OpenGL (for compatibility)
    void applyToOpenGL() const;
    
    // Static factory methods for common transformations
    static Matrix4 createTranslation(float x, float y, float z);
    static Matrix4 createRotationX(float angle);
    static Matrix4 createRotationY(float angle);
    static Matrix4 createRotationZ(float angle);
    static Matrix4 createScale(float x, float y, float z);
    
    // Utility methods
    void print() const;  // For debugging
};
