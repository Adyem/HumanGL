#include "../../includes/Matrix/Matrix4.hpp"
#include <cstring>
#include <cmath>
#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Matrix4::Matrix4() {
    loadIdentity();
}

Matrix4::Matrix4(const Matrix4& other) {
    std::memcpy(m, other.m, sizeof(m));
}

Matrix4& Matrix4::operator=(const Matrix4& other) {
    if (this != &other) {
        std::memcpy(m, other.m, sizeof(m));
    }
    return *this;
}

void Matrix4::loadIdentity() {
    std::memset(m, 0, sizeof(m));
    m[0] = m[5] = m[10] = m[15] = 1.0f;  // Diagonal elements
}

void Matrix4::translate(float x, float y, float z) {
    Matrix4 translation = createTranslation(x, y, z);
    *this *= translation;
}

void Matrix4::rotateX(float angle) {
    Matrix4 rotation = createRotationX(angle);
    *this *= rotation;
}

void Matrix4::rotateY(float angle) {
    Matrix4 rotation = createRotationY(angle);
    *this *= rotation;
}

void Matrix4::rotateZ(float angle) {
    Matrix4 rotation = createRotationZ(angle);
    *this *= rotation;
}

void Matrix4::scale(float x, float y, float z) {
    Matrix4 scaling = createScale(x, y, z);
    *this *= scaling;
}

Matrix4 Matrix4::operator*(const Matrix4& other) const {
    Matrix4 result;
    
    // Matrix multiplication (column-major order)
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            float sum = 0.0f;
            for (int k = 0; k < 4; k++) {
                sum += m[k * 4 + row] * other.m[col * 4 + k];
            }
            result.m[col * 4 + row] = sum;
        }
    }
    
    return result;
}

Matrix4& Matrix4::operator*=(const Matrix4& other) {
    *this = *this * other;
    return *this;
}

float& Matrix4::operator()(int row, int col) {
    return m[col * 4 + row];  // Column-major indexing
}

const float& Matrix4::operator()(int row, int col) const {
    return m[col * 4 + row];  // Column-major indexing
}

void Matrix4::applyToOpenGL() const {
    glMultMatrixf(m);
}

// Static factory methods
Matrix4 Matrix4::createTranslation(float x, float y, float z) {
    Matrix4 result;
    result.m[12] = x;  // Translation X
    result.m[13] = y;  // Translation Y
    result.m[14] = z;  // Translation Z
    return result;
}

Matrix4 Matrix4::createRotationX(float angle) {
    Matrix4 result;
    float rad = DEGREES_TO_RADIANS(angle);
    float c = cosf(rad);
    float s = sinf(rad);
    
    result.m[5] = c;   // [1][1]
    result.m[6] = s;   // [2][1]
    result.m[9] = -s;  // [1][2]
    result.m[10] = c;  // [2][2]
    
    return result;
}

Matrix4 Matrix4::createRotationY(float angle) {
    Matrix4 result;
    float rad = DEGREES_TO_RADIANS(angle);
    float c = cosf(rad);
    float s = sinf(rad);
    
    result.m[0] = c;   // [0][0]
    result.m[2] = -s;  // [2][0]
    result.m[8] = s;   // [0][2]
    result.m[10] = c;  // [2][2]
    
    return result;
}

Matrix4 Matrix4::createRotationZ(float angle) {
    Matrix4 result;
    float rad = DEGREES_TO_RADIANS(angle);
    float c = cosf(rad);
    float s = sinf(rad);
    
    result.m[0] = c;   // [0][0]
    result.m[1] = s;   // [1][0]
    result.m[4] = -s;  // [0][1]
    result.m[5] = c;   // [1][1]
    
    return result;
}

Matrix4 Matrix4::createScale(float x, float y, float z) {
    Matrix4 result;
    result.m[0] = x;   // Scale X
    result.m[5] = y;   // Scale Y
    result.m[10] = z;  // Scale Z
    return result;
}

void Matrix4::print() const {
    std::cout << "Matrix4:" << std::endl;
    for (int row = 0; row < 4; row++) {
        std::cout << "[ ";
        for (int col = 0; col < 4; col++) {
            std::cout << m[col * 4 + row] << " ";
        }
        std::cout << "]" << std::endl;
    }
}
