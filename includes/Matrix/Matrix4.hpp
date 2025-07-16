#pragma once


#include "../humangl.hpp"

class Matrix4 {
private:
    float m[16];

public:
    // Constructor - initializes to identity matrix
    Matrix4();

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

    // Apply matrix to OpenGL
    void applyToOpenGL() const;
};
